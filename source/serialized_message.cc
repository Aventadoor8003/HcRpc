#include "serialized_message.hh"
#include "loguru.hpp"
#include <string.h>

SerializedMessage::SerializedMessage() {
    this->data_buffer_ = new char[1000]();
    this->data_len_ = 0;
    this->request_id_ = -1;
}
//-TEST
// -Check request id
// -Check data length
SerializedMessage::SerializedMessage(ByteStream srouce_stream) {
    //TODO: Unmarshalling
    //1. Read in request id and message size
    char* start = srouce_stream;
    memcpy(&request_id_, start, sizeof(int));
    start += sizeof(int);
    memcpy(&data_len_, start, sizeof(int));
    start += sizeof(int);
    
    //2. Read in message content
    data_buffer_ = new char[data_len_]();
    memcpy(data_buffer_, start, data_len_);
}

//-TEST
// -Check length
// -CHeck data content
SerializedMessage::SerializedMessage(int request_id, SerializedBuffer &buffer) {
    request_id_ = request_id;
    data_len_ = buffer.GetLength();
    data_buffer_ = new char[data_len_]();

    buffer.CopyAllData(data_buffer_);
}

SerializedMessage::~SerializedMessage() {
    delete[] data_buffer_;
}

int SerializedMessage::CopyMessageToStream(ByteStream message_buffer) {
    char* start = message_buffer;
    memcpy(start, &request_id_, sizeof(int));
    start += sizeof(int);
    memcpy(start, &data_len_, sizeof(int));
    start += sizeof(int);
    memcpy(start, data_buffer_, data_len_);
    return 0;
}

int SerializedMessage::GetRequestId() {
    return request_id_;
}

int SerializedMessage::GetLength() {
    return data_len_;
}

SerializedBuffer SerializedMessage::ConstructBuffer() {
    return SerializedBuffer(data_buffer_, data_len_);
}
