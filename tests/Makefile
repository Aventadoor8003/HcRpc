INC_DIR = ../include/
BUF_DEP = ../source/serialized_buffer.cc
LOG_DEP = ../utils/loguru.cpp
TEST_DEP = src/catch_amalgamated.cpp

buffertest.exe:
	g++ -g buffertest.cc -g $(BUF_DEP) $(LOG_DEP) $(TEST_DEP)  -I$(INC_DIR) -I headers -o $@

clean:
	rm *.exe
