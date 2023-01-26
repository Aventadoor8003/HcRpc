INC_DIR = ../include/

BUF_DEP = ../source/serialized_buffer.cc
MSG_DEP = ../source/serialized_message.cc ../source/serialized_buffer.cc
LOG_DEP = ../utils/loguru.cpp
IO_DEP = ../utils/socket_utils.cc ../utils/StringOperations.cc

TEST_DEP = src/catch_amalgamated.cpp

buffertest.exe:
	g++ -g buffertest.cc -g $(BUF_DEP) $(LOG_DEP) $(TEST_DEP)  -I$(INC_DIR) -I headers -o $@

messagetest.exe:
	g++ -g messagetest.cc -g $(MSG_DEP) $(LOG_DEP) $(TEST_DEP)  -I$(INC_DIR) -I headers -o $@

iotest.exe:
	g++ -g iotest.cc -g $(IO_DEP) $(LOG_DEP) $(TEST_DEP)  -I$(INC_DIR) -I headers -o $@

clean:
	rm *.exe
