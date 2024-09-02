# Variables
CC = gcc
CFLAGS = -c
OBJ = socket.o
CLIENT_SRC = ./src/sock-stream/client.c
SERVER_SRC = ./src/sock-stream/server.c
SOCKET_SRC = ./src/lib/socket.c
SOCKET_MOD = ./src/lib
CLIENT_BIN = client
SERVER_BIN = server

# Default target
all: $(CLIENT_BIN) $(SERVER_BIN)

# Build socket.o
$(OBJ): $(SOCKET_SRC)
	$(CC) $(CFLAGS) $< -o $@

# Build client executable
$(CLIENT_BIN): $(CLIENT_SRC) $(OBJ)
	$(CC) $^ -o $@ -I $(SOCKET_MOD)

# Build server executable
$(SERVER_BIN): $(SERVER_SRC) $(OBJ)
	$(CC) $^ -o $@ -I $(SOCKET_MOD)

# Clean target to remove generated files
clean:
	rm -f $(OBJ) $(CLIENT_BIN) $(SERVER_BIN)
