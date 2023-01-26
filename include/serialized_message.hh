#ifndef __SERIALIZED_MESSAGE_HH__
#define __SERIALIZED_MESSAGE_HH__

//#define MESSEAGE_LEN 1024

#include "common.hh"
#include "serialized_buffer.hh"

/// Message:
/// | content | request id | data len |  data 
/// |  bytes  |      4     |     4    |   all rest

/**
 * Marshalling:
 * need arguments: a message buffer, length of message buffer, request id
 * Write a constructor to marshal
 * Then copy all information into a data stream
 * 
 * Unmarshalling:
 * need argument: simply a bytestream source
 * Set up arguments
 * Then construct a message buffer
 */
class SerializedMessage {

public:

    SerializedMessage();
    /// @brief Unmarshal: stream -> messageObject
    /// MIGHT BE DEPRICATED
    SerializedMessage(ByteStream srouce);
    /// @brief Marshal: object -> messageObject
    SerializedMessage(int request_id, SerializedBuffer& buffer);

    //SerializedMessage(int socket);
    ~SerializedMessage();

    /// @brief marshal
    /// @return success: bytes copied to message buffer. failed: -1
    int CopyMessageToStream(ByteStream message_buffer);
    //int SendToSocket(int socket);

    int CopyDataToStream(ByteStream stream);

    int GetRequestId();

    /// @brief Get length of data
    int GetDataLength();

    int GetMessageLength();

    /// @brief Unmarshal: Copy data to dest 
    /// @return success: 0. fail: -1
    SerializedBuffer ConstructBuffer();


//private:
    int request_id_;
    char* data_buffer_;
    int data_len_;

};


#endif /*__SERIALIZED_MESSAGE_HH__*/