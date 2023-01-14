#include "serializable_buffer.hh"
#include "MultiTypeObject.hpp"

using namespace std;

int main() {

    SerializableBuffer buffer;
    
    //int a = 4;
    //buffer.AddData(&a, sizeof(a));
    //buffer.PrintDetails();

    MultiTypeObject obj;
    obj.SetInt(22);
    const char* name = "Good";
    obj.SetName(name, sizeof(name));
    //obj.PrintContent();
    //cout << "Data size: " << obj.GetDataSize() << endl;
    obj.Serialize(buffer);
    cout << "Finished serialization" << endl;
    buffer.PrintDetails();
    buffer.SkipBackward(34);

    cout << "----Trying to print obj2" << endl;
    MultiTypeObject obj2;
    obj2.Deserialize(buffer);
    obj2.PrintContent();
    buffer.PrintDetails();

    return 0;
}