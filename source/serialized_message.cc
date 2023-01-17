#include "serialized_message.hh"
#include <string.h>

SerializedMessage::SerializedMessage() {
    data_buffer_ = nullptr;
}

SerializedMessage::SerializedMessage(char *srouce, int message_size) {
    data_buffer_ = new char[message_size - sizeof(int)]();
    memcpy(&request_id_, data_buffer_, sizeof(int));
    memcpy(data_buffer_, data_buffer_ + sizeof(int), message_size - sizeof(int));
}

SerializedMessage::~SerializedMessage() {
    if(data_buffer_) {
        delete[] data_buffer_;
    }
}

int SerializedMessage::GenerateSerializedMessage(int request_id, SerializedBuffer &buffer) {
    int total_size = sizeof(int) + buffer.GetLength();
    data_buffer_ = new char[total_size]();
    memcpy(data_buffer_, &request_id, sizeof(request_id));
    buffer.CopyAllData(data_buffer_ + sizeof(int));
    return 0;
}

int SerializedMessage::CopyMessageToStream(char *message_buffer) {
    return 0;
}

int SerializedMessage::CopyData(SerializedBuffer &buffer) {
    return 0;
}
