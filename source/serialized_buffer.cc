#include <iostream>
#include <string.h>

#include "serialized_buffer.hh"
#include "loguru.hpp"

using namespace std;

//SerializableBuffer::SerializableBuffer(){ }

SerializedBuffer::SerializedBuffer() {
    this->buffer_ptr_ = new char[serializedbuffer::kMaxBufferSize]();
    this->capacity_ = serializedbuffer::kMaxBufferSize;
    this->next_ = 0;
}

SerializedBuffer::SerializedBuffer(int buffer_size) {
    this->buffer_ptr_ = new char[buffer_size]();
    this->capacity_ = buffer_size;
    this->next_ = 0;
}

SerializedBuffer::SerializedBuffer(char *external_buffer, int external_size) {
    this->buffer_ptr_ = new char[external_size]();
    for(int i = 0; i < external_size; i++) {
        buffer_ptr_[i] = external_buffer[i];
    }
    this->capacity_ = external_size;
    this->next_ = external_size;
}

SerializedBuffer::~SerializedBuffer() {
    //cout << "Destructing" << endl;
    delete[] this->buffer_ptr_;
}

int SerializedBuffer::AddData(void *data, int data_size) {
    if(this->buffer_ptr_ == nullptr) {
        return -1;
    } 

    bool need_resize = 0;
    while(this->capacity_ - this->next_ < data_size) {
        this->capacity_ *= 2;
        need_resize = 1;
    }

    if(need_resize) {
        LOG_F(INFO, "Buffer resized to %d", capacity_);
        char* new_buffer = new char[this->capacity_];
        memcpy(new_buffer, this->buffer_ptr_, this->next_);
        delete[] this->buffer_ptr_;
        this->buffer_ptr_ = new_buffer;
    }
    
    memcpy(buffer_ptr_ + next_, data, data_size);
    next_ += data_size;

    return 0;
}

int SerializedBuffer::SkipForward(int skip_size) {
    if(capacity_ - next_ < skip_size) {
        //Print a message
        return -1;
    }
    Skip(skip_size);
    return 0;
}

int SerializedBuffer::SkipBackward(int skip_size) {
    if(skip_size > next_) {
        //Print a message
        return -1;
    }
    Skip(-1 * skip_size);
    return 0;
}

int SerializedBuffer::Rewind() {
    next_ = 0;
    return 0;
}

int SerializedBuffer::Skip(int skip_size) {
    next_ += skip_size;
    return 0;
}

char *SerializedBuffer::GetCurrentPtr() {
    return buffer_ptr_ + next_;
}


int SerializedBuffer::GetLength() {
    return next_;
}

int SerializedBuffer::CopyAllData(char *dest) const {
    
    /*for(int i = 0; i < next_; i++) {
        dest[i] = buffer_ptr_[i];
    }*/
    memcpy(buffer_ptr_, dest, next_);
    return next_;
}

int SerializedBuffer::CopyToDest(void *dest, int size) {
    memcpy(dest, GetCurrentPtr(), size);
    next_ += size;
    return 0;
}

void SerializedBuffer::PrintDetails() const {
    cout << "size: " << capacity_ << endl;
    cout << "length: " << next_ << endl;
}