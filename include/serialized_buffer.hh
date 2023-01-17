#ifndef __SERIALIZABLE_BUFFER_HH__
#define __SERIALIZABLE_BUFFER_HH__

namespace serializedbuffer {

const int kDefaultBufferSize = 64;
const int kMaxBufferSize = 1024;

}

/// @brief A buffer represented in a char array to send and retrieve data
class SerializedBuffer {
public:
    
    SerializedBuffer();

    SerializedBuffer(int buffer_size);

    SerializedBuffer(char* external_buffer, int external_size);

    ~SerializedBuffer();

    /**----------------------------------------------------------------
     *                        Functionalities
     * --------------------------------------------------------------*/

    /// @brief Read data into buffer. Attention: data should be a single element: an integer, a char array, likewise
    /// @return Successful: 0. Otherwise status code
    int AddData(void* data, int data_size);

    /// @return Successful: 0. Otherwise status code
    int SkipForward(int skip_size);

    /// @return Successful: 0. Otherwise status code
    int SkipBackward(int skip_size);

    /// @brief Set next pointer to the start of buffer
    /// @return 0: success. -1: error 
    int Rewind();

    /// @brief Truncate extra bytes to minimize the size of char array
    /// @return new size if successfull. Otherwise -1
    int Truncate();

    bool IsEmpty();
    //bool isFull();
    int GetCapacity();

    /// @brief Get current data length
    //PROBLEM: What does length mean? position of next pointer, or size data read in
    int GetLength();

    /// @brief Copy a new char array to dest
    /// @return Success: the length copied. Failed: -1
    int CopyAllData(char* dest) const;
    int GetCurrentPtrOffest();
    int CopyToDest(void* dest, int size);    

    void PrintDetails() const;

private: 
//Keep public during development

    char* buffer_ptr_;
    int capacity_;
    /// @brief pointer to the first avaliable byte
    int next_;

    /// @brief Move forward(to the end of buffer)
    /// @param skip_size must be larger than zero
    /// @return Successful: 0. Otherwise status code
    int Skip(int skip_size);

    /// @brief Change to new size 
    /// @return new size if successfull. Otherwise -1
    //int Resize(int size);

    char* GetCurrentPtr();    

};

#endif /*__SERIALIZABLE_BUFFER_HH__*/

/**
 * TODO:
 * Test buffer(length after adding data, erasing data) with google test
 * 
 * 
 * TESTS:
 *  -Constructer with external buffer
 *  -AddData
 *  -SkipForword
 *  -SkipBackword
 *  -Rewind
 *  -Truncate
 *  -CopyToCharArray
 */