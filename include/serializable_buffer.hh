#ifndef __SERIALIZABLE_BUFFER_HH__
#define __SERIALIZABLE_BUFFER_HH__

namespace serializablebuffer {

const int kDefaultBufferSize = 64;
const int kMaxBufferSize = 1024;

}

class SerializableBuffer {
public:
    
    SerializableBuffer() {
        //TODO: Move char buffer to heap
        //this->buffer_ptr_[serializablebuffer::kDefaultBufferSize];
        this->capacity_ = 0;
        this->next_ = 0;
    }

    //SerializableBuffer(int buffer_size);

    ~SerializableBuffer();

    /**----------------------------------------------------------------
     *                        Functionalities
     * --------------------------------------------------------------*/

    /// @brief Read data into buffer. Attention: data should be a single element: an integer, a char array, likewise
    /// @return Successful: 0. Otherwise status code
    int AddData(char* data, int data_size);

    /// @brief Move forward(to the end of buffer)
    /// @param skip_size must be smaller than zero
    /// @return Successful: 0. Otherwise status code
    int SkipForward(int skip_size);

    /// @brief Move backward(to the end of buffer)
    /// @param skip_size must be smaller than zero
    /// @return Successful: 0. Otherwise status code
    int SkipBackward(int skip_size);

    /// @brief Truncate extra bytes
    /// @return new size if successfull. Otherwise -1
    int Truncate();

    bool IsEmpty();
    //bool isFull();
    int GetCapacity();
    int GetLength();

    char* GetCharArray();
    int GetCurrentPtrOffest();
    char* GetCurrentPtr();    

    

private:

    char* buffer_ptr_;

    int capacity_;

    int next_;

    /// @brief Move forward(to the end of buffer)
    /// @param skip_size must be larger than zero
    /// @return Successful: 0. Otherwise status code
    int Skip(int skip_size);

    /// @brief Change to new size 
    /// @return new size if successfull. Otherwise -1
    int Resize(int size);

};

#endif /*__SERIALIZABLE_BUFFER_HH__*/