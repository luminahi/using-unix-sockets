# Variables
CC = gcc
CFLAGS = -c
OBJ = ./src/socket.o
CLIENT_SRC = ./src/client.c
SERVER_SRC = ./src/server.c
SOCKET_SRC = ./src/socket.c
CLIENT_BIN = client
SERVER_BIN = server

# Default target
all: $(CLIENT_BIN) $(SERVER_BIN)

# Build socket.o
$(OBJ): $(SOCKET_SRC)
	$(CC) $(CFLAGS) $< -o $@

# Build client executable
$(CLIENT_BIN): $(CLIENT_SRC) $(OBJ)
	$(CC) $^ -o $@

# Build server executable
$(SERVER_BIN): $(SERVER_SRC) $(OBJ)
	$(CC) $^ -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJ) $(CLIENT_BIN) $(SERVER_BIN)
