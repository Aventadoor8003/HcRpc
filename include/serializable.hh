#ifndef __SERIALIZABLE_HH__
#define __SERIALIZABLE_HH__

#include "serialized_buffer.hh"
/// @brief Serializable interface. Each serializable object can be serialized into a serializable buffer
class Serializable {
public:

    Serializable() {}

    ~Serializable() {};

    /// @brief Construct an object using a buffer
    /// @return Success: 0, otherwise status code
    virtual int Deserialize(SerializedBuffer& buffer)=0;

    /// @brief Serializa an object into a buffer 
    /// @return Success: 0. Otherwis status code
    virtual int Serialize(SerializedBuffer& buffer)=0;

    virtual void PrintContent()=0;

    virtual int GetDataSize()=0;

};

#endif /*__SERIALIZABLE_HH__*/

/**
 * TODO:
 *  
 * 
 * 
 * 
 * 
 */