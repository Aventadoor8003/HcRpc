#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>

#include "serialization_client.hh"
#include "loguru.hpp"

using namespace std;

int SerializationClient::Run() {
    //-TODO: Refactor using the new ConnectToServer in sock utils
    if(ConnectToServer() == -1) {
        LOG_F(ERROR, "Client stop (Failed to connect to server)");
        return -1;
    }
    
    //1. Read in a string
    cout << "Please enter a string" << endl;
    string input;
    cin >> input;

    //2. Pack it as a serialized object
    //-TODO: Write a serialized string
    SerializedBuffer buffer;
    buffer.AddData((void*)input.c_str(), input.size());
    SerializedMessage message(ECHO_REQUST, buffer);

    //3. Send it to server
    DoWrite(message);

    //4. Receive the packet from server
    ByteStream stream;
    DoRead(stream);
    SerializedMessage received_message(stream);    

    char tmp_str[1024];
    int len = received_message.CopyDataToStream(tmp_str);
    tmp_str[len] = '\0';
    
    //5. Print string
    cout << "Received [" << tmp_str << "]" << endl;
    
    close(server_socket_);
    return 0;
}

int SerializationClient::ConnectToServer() {
    if(server_socket_ != -1) {
        return 0;
    }

    server_socket_ = socket(PF_INET, SOCK_STREAM, 0);
    if(server_socket_ < 0) {
        LOG_F(ERROR, "Cannot open socket. (%s)", strerror(errno));
        return -1;
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port_);
    inet_pton(AF_INET, server_addr_, &(servaddr.sin_addr));

    if(connect(server_socket_, (sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        LOG_F(ERROR, "Cannot connect to %s:%d", server_addr_, server_port_);
        return -1;
    }
    
    return 0;
}

int SerializationClient::DoRead(ByteStream buffer) {
    // 1. Read first 8 bytes to get size
    int request_id, data_len;
    Read(&request_id, sizeof(int));
    Read(&data_len, sizeof(int));

    // 2. read proper size of data according to size parameter
    char* start = buffer;
    memcpy(start, &request_id, sizeof(int));
    start += sizeof(int);
    memcpy(start, &data_len, sizeof(int));
    start += sizeof(int);
    Read(start, data_len);
    return 0;
}

int SerializationClient::Read(void *data_ptr, int size) {
    int received_len = 0;
    while(received_len < size) {
        int received = read(server_socket_, data_ptr + received_len, size - received_len);
        if(received < 0) {
            LOG_F(ERROR, "Failed to read from socket [%d]", server_socket_);
            LOG_F(ERROR, "Error: %s", strerror(errno));
            return -1;
        }
        received_len += received;
    }
    return received_len;
}

/*int SerializationClient::DoWrite(SerializedMessage &message) {
    //TODO: USE SOCKET UTILS
    //Directly send message to socket
    return 0;
}*/
