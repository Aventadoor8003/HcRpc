INC_DIR = ../include/

buffertest.exe:
	g++ -g buffertest.cc ../source/serializable_buffer.cc ../utils/loguru.cpp -I $(INC_DIR) -o $@

clean:
	rm *.exe