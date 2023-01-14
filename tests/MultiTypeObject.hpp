#include <string.h>
#include <iostream>
#include "serializable.hh"

#define LEN 30

using namespace std;

class MultiTypeObject : public Serializable {
public:

    void SetInt(int num) {
        test_int_ = num;
    }

    void SetName(const char* name, int len) {
        memcpy(test_str_, name, len);
    }

    virtual int Deserialize(SerializableBuffer& buffer) override {
        buffer.CopyToDest(&test_int_, sizeof(int));
        buffer.CopyToDest(&test_str_, sizeof(test_str_));
        return 0;
    }

    /// @brief Serializa an object into a buffer 
    /// @return Success: 0. Otherwis status code
    virtual int Serialize(SerializableBuffer& buffer) override {
        buffer.AddData(&test_int_, sizeof(test_int_));
        buffer.AddData(test_str_, sizeof(test_str_));
        return 0;
    }

    virtual void PrintContent() override {
        cout << "Test int: " << test_int_ << endl;
        cout << "Size of test str "  << strlen(test_str_) << endl;
        cout << "Test str: " << test_str_ << endl;
    }

    virtual int GetDataSize() override {
        return sizeof(test_str_) + sizeof(test_int_);
    }

//private:
    int test_int_;
    char test_str_[LEN];
};