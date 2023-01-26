#ifndef __SERIALIZABLE_HH__
#define __SERIALIZABLE_HH__

#include "serialized_buffer.hh"


/**
 * ------------------------------
 *         EXTRA ATTENTION
 * ------------------------------
 * If there is a string in a serializable object, pay extra attention to the '\0' at the end
 * The '\0' won't be contained in a serialized message
 * but when unmarshaling a serialized message, we need to append this byte
 */
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

    //DEBUG USAGE
    virtual void PrintContent() {};

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