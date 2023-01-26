#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>

#include "common.hh"
#include "socket_utils.hh"
#include "StringOperations.hh"

using namespace std;

int ConnectToServer(std::string server_addr) {
    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(server_socket < 0) {
        LOG_F(ERROR, "Cannot open socket. (%s)", strerror(errno));
        return -1;
    }

    const char* server_ip = getIpAddr(server_addr).c_str();
    int server_port = getPort(server_addr);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &(servaddr.sin_addr));

    if(connect(server_socket, (sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        LOG_F(ERROR, "Cannot connect to %s:%d", server_addr, server_port);
        return -1;
    }
    
    return server_socket;
}

int DoRead(int fd, void *dest, int size) {
    int received_len = 0;
    while(received_len < size) {
        int received = read(fd, dest + received_len, size - received_len);
        if(received < 0) {
            LOG_F(ERROR, "Failed to read from descriptor [%d]", fd);
            LOG_F(ERROR, "Error: %s", strerror(errno));
            return -1;
        }
        received_len += received;
    }
    return received_len;
}

int DoWrite(int fd, void *content, int size) {
    int total_sent = 0;
    while(total_sent < size) {
        int sent = write(fd, content + total_sent, size - total_sent);
        if(sent < 0) {
            LOG_F(ERROR, "Failed to send to descriptor [%d]", fd);
            LOG_F(ERROR, "Error: %s", strerror(errno));
        }
        total_sent += sent;
    }
    return total_sent;
}
