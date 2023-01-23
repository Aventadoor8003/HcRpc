#include "catch_amalgamated.hpp"
#include "serialized_message.hh"

TEST_CASE() {
    char stream[121];
    int rid = 1;
    int len = 13;
    char* start = stream;
    memcpy(start, &rid, sizeof(int));
    start += sizeof(int);
    memcpy(start, &len, sizeof(int));
    start += sizeof(int);
    memcpy(start, "Hello1234567", 13);
    SerializedMessage message(stream);
    REQUIRE(message.GetLength() == 13);
    REQUIRE(message.data_len_ == 13);
    REQUIRE(strcmp(message.data_buffer_, "Hello1234567") == 0);
    REQUIRE(message.GetRequestId() == 1);

    char dest[1234];
    message.CopyMessageToStream(dest);
    REQUIRE(strcmp(dest, stream) == 0);
    
    SerializedBuffer buffer = message.ConstructBuffer();
    REQUIRE(buffer.capacity_ == 13);
    REQUIRE(buffer.next_ == 0);
    REQUIRE(strcmp(buffer.buffer_ptr_, "Hello1234567") == 0);
}