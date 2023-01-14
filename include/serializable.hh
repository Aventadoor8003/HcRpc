#ifndef __SERIALIZABLE_HH__
#define __SERIALIZABLE_HH__

#include "serializable_buffer.hh"

/// @brief Serializable interface
class Serializable {
public:

    Serializable() {}

    ~Serializable() {};

    /// @brief Construct an object using a buffer
    /// @return Success: 0, otherwise status code
    virtual int Deserialize(SerializableBuffer& buffer)=0;

    /// @brief Serializa an object into a buffer 
    /// @return Success: 0. Otherwis status code
    virtual int Serizalize(SerializableBuffer& buffer)=0;

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