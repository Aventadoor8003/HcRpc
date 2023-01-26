#include <fcntl.h>
#include <cstring>
#include <iostream>

#include "socket_utils.hh"
#include "catch_amalgamated.hpp"

using namespace std;

TEST_CASE() {
    SECTION("Read hello test") {
        int fd = open("testfile.txt", O_RDONLY);
        char buffer[1024];
        DoRead(fd, buffer, 12);
        buffer[11] = '\0';
        //cout << buffer;
        const char* pole = "Hello there";
        REQUIRE(strcmp(pole, buffer) == 0);
    }
}

/**TEST
 * -1. Test read size using an exsiting file
 * -2. Test write size using an empty file
 * -3. Test read using the previously created file
 */