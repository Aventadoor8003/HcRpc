#ifndef __SERIALIZED_MESSAGE_HH__
#define __SERIALIZED_MESSAGE_HH__

#include "common.hh"
#include "serialized_buffer.hh"

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

    /// @return 
    int CopyMessageToStream(ByteStream message_buffer);

    int GetRequestId();

    /// @brief Unmarshal: Copy data to dest 
    /// @return success: 0. fail: -1
    int CopyData(SerializedBuffer& buffer);


//private:
    int request_id_;
    char* data_buffer_;

};


#endif /*__SERIALIZED_MESSAGE_HH__*/