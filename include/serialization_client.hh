#ifndef __SERIALIZATION_CLIENT_HH__
#define __SERIALIZATION_CLIENT_HH__

#include "serializable.hh"
#include "serialized_message.hh"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 2333

class SerializationClient {
public:
    SerializationClient();
    ~SerializationClient();

    int Run();
    int Stop();

//private:
//Keep public while developping

    int vflag_ = 1;
    int server_socket_ = -1;
    const char* server_addr_ = SERVER_ADDR;
    int server_port_ = SERVER_PORT;

    /// @brief Set up connection socket
    /// @return the socket. if error happens, return -1
    int ConnectToServer();

    ///----------------------------------------------
    ///              Helper methods
    ///----------------------------------------------
    
    /// @brief Read data into bytestream from server socket
    /// @return successful: bytes of data read. fail: -1 
    int DoRead(ByteStream buffer);

    //TODO: Depricate this method
    /// @brief Read in assigned size
    /// @return Suc: actual bytes. Fail: -1
    int Read(void* data_ptr, int size);

    /// @brief Send a serialized message to server
    /// @return suc: bytes sent. failed: -1
    int DoWrite(SerializedMessage& message);

};

/**
 * WARNING: Inheritence is not recommonded here. Use a request handler to handle different requests 
 * TODO:
 * -Move read write and connect function to a seperate file
 * 
 * Message transportation:
 * 1. read in a ByteStream buffer
 * 2. Construct a Serializable object/primitive
 * 3. Then do things
 * 
 * TEST:
 * -Read write methods should be tested using echo server
*/

#endif