#ifndef __SERIALIZATION_SERVER_HH__
#define __SERIALIZATION_SERVER_HH__

#define MAX_CLIENTS 100

#include <unordered_set>
#include <string>
#include <thread>
#include <mutex>

#include "socket_utils.hh"
#include "serialized_message.hh"

//If there is a need to solve new problems, add a new solver class into this class

class SerializationServer {
public:
    SerializationServer();
    ~SerializationServer();

    int Run();
    int Stop();

//private:
//Keep public during development


    std::string listen_addr_ = "127.0.0.1:2333";
    int vflag_;
    int listen_socket_;
    
    std::unordered_set<int> socket_set_;
    std::mutex sockets_mutex_;

    virtual void Worker(void* param);

    //Listen is intergrated into socket utils.

    int AddNewConnection(int new_socket);
    int RemoveConnection(int socket);
    
    int ReadFromSocket(int socket, ByteStream buffer);
    int WriteToSocket(int socket, SerializedMessage& message);
};

#endif /*__SERIALIZATION_SERVER_HH__*/

//TODO: Write workers