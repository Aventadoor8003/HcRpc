#ifndef __SOCKET_UTIL__HH__
#define __SOCKET_UTIL__HH__

#include <string>

/// @brief Set up connection socket
/// @return the socket. if error happens, return -1
int ConnectToServer(std::string server_addr);

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
 * Test read write functions in a new file
 * 
 * 
 */