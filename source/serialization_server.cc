#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>

#include "socket_utils.hh"
#include "serialization_server.hh"
#include "loguru.hpp"

using namespace std;

SerializationServer::SerializationServer() { }

SerializationServer::~SerializationServer() { }

int SerializationServer::Run() {
    if(ListenToAddress(listen_addr_)) {
        LOG_F(ERROR, "[Server] Failed to listen to %s", listen_addr_.c_str());
        return -1;
    }

    while(true) {
        sockaddr client_inet;
        socklen_t client_addr_len = sizeof(client_inet);
        int comm_fd = accept(listen_socket_, (sockaddr*) &client_inet, &client_addr_len);
        if(comm_fd == -1) {
            LOG_F(WARNING, "[Server] Failed to accept connection from %d", comm_fd);
            LOG_F(WARNING, "Error: %s", strerror(errno));
            continue;
        }

        AddNewConnection(comm_fd);
        thread worker_thread([&] {Worker(&comm_fd); });
        worker_thread.detach();
    }
    return 0;
}

int SerializationServer::Stop() {
    //TODO: 1. Remove all connections
    close(listen_socket_);
    return 0;
}

void SerializationServer::Worker(void *param) {
    int comm_fd = *(int*) param;
}

int SerializationServer::AddNewConnection(int new_socket)
{
    if(socket_set_.size() == MAX_CLIENTS) {
        //TODO: log, reached max connections
        return -1;
    }

    sockets_mutex_.lock();
    socket_set_.emplace(new_socket);
    sockets_mutex_.unlock();
    return 0;
}

//Socket is already closed in worker
int SerializationServer::RemoveConnection(int socket) {
    if(!socket_set_.count(socket)) {
        //TODO: log: Cannot find connection
        return -1;
    }

    sockets_mutex_.lock();
    socket_set_.erase(socket);
    sockets_mutex_.unlock();
}

int SerializationServer::ReadFromSocket(int socket, ByteStream buffer) {
    int reqest_id, data_len = -1;
    DoRead(socket, &reqest_id, sizeof(int));
    DoRead(socket, &data_len, sizeof(int));

    char* start = buffer;
    memcpy(start, &reqest_id, sizeof(int));
    start += sizeof(int);
    memcpy(start, &data_len, sizeof(int));
    start += sizeof(int);
    DoRead(socket, start, data_len);
    return 0;
}

int SerializationServer::WriteToSocket(int socket, SerializedMessage &message) {
    int msg_len = message.GetMessageLength();
    ByteStream msg_buffer = new char[msg_len]();
    message.CopyMessageToStream(msg_buffer);
    DoWrite(socket, msg_buffer, msg_len);
    return 0;
}
