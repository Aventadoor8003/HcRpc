#ifndef __SOCKET_UTIL__HH__
#define __SOCKET_UTIL__HH__

#include <string>

/// @brief Set up connection socket
/// @return the socket. if error happens, return -1
int ConnectToServer(std::string server_addr);

/// @brief Listen to an address
/// @return the socket. if fails, return -1
int ListenToAddress(std::string address_string);

/// @brief Read data into bytestream from a file descriptor
/// @return successful: bytes of data read. fail: -1 
int DoRead(int fd, void* dest, int size);

/// @brief Send a serialized message to a file descriptor
/// @return suc: bytes sent. failed: -1
int DoWrite(int fd, void* content, int size);

#endif

/**
 * TODO:
 * Add necessary server utils inside this header
 * TEST:
 * If error happens in serialization server, use a simple echo server 
 *  which just receives echo commands to test read write functions
 * 
 * 
 */