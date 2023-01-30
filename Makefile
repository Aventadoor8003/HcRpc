TARGETS = build/server.exe build/client.exe
COMM_DEP = source/serialized_buffer.cc source/serialized_message.cc utils/*
SERVER_DEP = $(COMM_DEP) drivers/server_driver.cc source/serialization_server.cc
CLIENT_DEP = $(COMM_DEP) drivers/client_driver.cc source/serialization_client.cc

INC_DIR = include

all:
	make $(TARGETS)

build/server.exe:
	g++ $(SERVER_DEP) -I $(INC_DIR) -o $@

build/client.exe:
	g++ $(CLIENT_DEP) -I $(INC_DIR) -o $@

clean:
	rm build/*.exe
	