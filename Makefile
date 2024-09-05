# Variables
CC = gcc
CFLAGS = -c
OBJ = socket.o
SOCKET_SRC = ./src/lib/socket.c
SOCKET_MOD = ./src/lib

CLIENT_SRC_STREAM = ./src/sock-stream/client.c
SERVER_SRC_STREAM = ./src/sock-stream/server.c
CLIENT_BIN_STREAM = stream-client
SERVER_BIN_STREAM = stream-server

CLIENT_SRC_DGRAM = ./src/sock-dgram/client.c
SERVER_SRC_DGRAM = ./src/sock-dgram/server.c
CLIENT_BIN_DGRAM = dgram-client
SERVER_BIN_DGRAM = dgram-server

# Default target
stream: $(OBJ) $(CLIENT_BIN_STREAM) $(SERVER_BIN_STREAM) $(CLIENT_BIN_DGRAM) $(SERVER_BIN_DGRAM)

# Build socket.o
$(OBJ): $(SOCKET_SRC)
	$(CC) $(CFLAGS) $< -o $@

# Build stream client executable
$(CLIENT_BIN_STREAM): $(CLIENT_SRC_STREAM) $(OBJ)
	$(CC) $^ -o $@ -I $(SOCKET_MOD)

# Build stream server executable
$(SERVER_BIN_STREAM): $(SERVER_SRC_STREAM) $(OBJ)
	$(CC) $^ -o $@ -I $(SOCKET_MOD)

# Build datagram client executable
$(CLIENT_BIN_DGRAM): $(CLIENT_SRC_DGRAM) $(OBJ)
	$(CC) $^ -o $@ -I $(SOCKET_MOD)

# Build datagram server executable
$(SERVER_BIN_DGRAM): $(SERVER_SRC_DGRAM) $(OBJ)
	$(CC) $^ -o $@ -I $(SOCKET_MOD)

# Clean target to remove generated files
clean:
	rm -f $(OBJ) $(CLIENT_BIN_STREAM) $(SERVER_BIN_STREAM) $(CLIENT_BIN_DGRAM) $(SERVER_BIN_DGRAM)
