#include "catch_amalgamated.hpp"
#include "serialized_buffer.hh"
#include "MultiTypeObject.hpp"

using namespace std;

TEST_CASE() {

    SerializedBuffer buffer;


    SECTION("Test new buffer") {
        REQUIRE(buffer.next_ == 0);
    }

    SECTION("AddData test") {
        int integer = 5;
        buffer.AddData(&integer, sizeof(integer));
        REQUIRE(buffer.next_ == 4);
        char string_of_30[30];
        strcpy(string_of_30, "Hello");
        buffer.AddData(string_of_30, sizeof(string_of_30));
        //TEST next and content
        REQUIRE(buffer.next_ == 34);
        buffer.SkipBackward(30);
        char newStr[30];
        strcpy(newStr, buffer.buffer_ptr_ + buffer.next_);
        REQUIRE(strcmp(newStr, "Hello") == 0);

        integer = -1;
        REQUIRE(buffer.Rewind() == 0);
        buffer.CopyToDest(&integer, sizeof(int));
        REQUIRE(integer == 5);
        REQUIRE(buffer.next_ == 4);

        strcpy(newStr, "Good");
        buffer.CopyToDest(newStr, sizeof(string_of_30));
        REQUIRE(strcmp(newStr, "Hello") == 0);
    }

    SECTION("Add string test") {
        const char* test = "Test";
        buffer.AddData((void*)test, sizeof(test));
        REQUIRE(buffer.GetLength() == 8);
        buffer.Rewind();

        char str_bff[30];
        buffer.CopyToDest(str_bff, sizeof(test));
        REQUIRE(strcmp(str_bff, test) == 0);
    }

    SECTION("Add data for compex objects") {
        struct s1 {
            int i1;
            int i2;
            int i3;
        };
        int size1 = sizeof(s1);
        REQUIRE(size1 == 12);

        MultiTypeObject test2;
        int size2 = test2.GetDataSize();
        REQUIRE(size2 == 34);

        s1 test1 = {1, 2, 3};
        buffer.AddData(&test1, size1);
        REQUIRE(buffer.GetLength() == 12);
        
        buffer.Rewind();
        test2.Serialize(buffer);
        REQUIRE(buffer.GetLength() == size2);
        
    }

    
}

 /** TESTS:
 *  -Constructer with external buffer
 *  -AddData
 *  -CopyToDest
 *  -SkipForword
 *  -SkipBackword
 *  -Rewind
 *  -Truncate
 *  -CopyToCharArray
 */

/*
int main() {

    SerializableBuffer buffer;

    MultiTypeObject obj;
    obj.SetInt(22);
    const char* name = "Good";
    obj.SetName(name, sizeof(name));
    //obj.PrintContent();
    //cout << "Data size: " << obj.GetDataSize() << endl;
    obj.Serialize(buffer);
    printf("%s\n", buffer.buffer_ptr_);
    //cout << "Finished serialization" << endl;
    //buffer.PrintDetails();
    //buffer.SkipBackward(34);
    buffer.Rewind();

    cout << "----Trying to print obj2" << endl;
    MultiTypeObject obj2;
    obj2.Deserialize(buffer);
    obj2.PrintContent();
    //buffer.PrintDetails();

    return 0;
}*/