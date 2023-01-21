#ifndef __SERIALIZED_MESSAGE_HH__
#define __SERIALIZED_MESSAGE_HH__

#include "common.hh"
#include "serialized_buffer.hh"

/// TODO: Rewrite this part. size field should be at first for performance reasons
/// Message:
/// | content | request id | data len |  data 
/// |  bytes  |      4     |     4    |   all rest
class SerializedMessage {

public:

    SerializedMessage();
    /// @brief Unmarshal 
    SerializedMessage(ByteStream srouce, int message_size);
    ~SerializedMessage();

    /// @brief Marshal and send message 
    /// @return success: 0. fail: -1
    /// TODO: Thinking about make this method private and realize the same functinoality in constructor
    int GenerateSerializedMessage(int request_id, SerializedBuffer& buffer);

    /// @return success: bytes copied to message buffer. failed: -1
    int CopyMessageToStream(ByteStream message_buffer);

    int GetRequestId();

    /// @brief Unmarshal: Copy data to dest 
    /// @return success: 0. fail: -1
    int CopyData(SerializedBuffer& buffer);


//private:
    int request_id_;
    char* data_buffer_;
    int data_len_;

};


#endif /*__SERIALIZED_MESSAGE_HH__*/