#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "socket.h"

#define FILEPATH "/tmp/custom.sock"
#define BUFFER_SIZE 128

int file_exists(const char* file_path) {
    struct stat file_stat;
    return (stat(file_path, &file_stat) == 0);
}

void start_server(char* filepath, int buffer_size) {
    int socket_fd;
    int num_bytes;
    struct sockaddr_un addr;
    int addr_len;
    char buffer[buffer_size];

    if (file_exists(filepath)) {
        unlink(filepath);
    }

    printf("waiting for a message...\n");

    socket_fd = assert_socket(filepath, SOCK_DGRAM, &addr);
    bind_socket(socket_fd, &addr);
    num_bytes = receive_message_dgram(socket_fd, buffer, buffer_size, &addr, &addr_len);

    buffer[num_bytes] = '\0';
    printf("%s\n", buffer);
}

int main(int argc, char* argv[]) {
    start_server(FILEPATH, BUFFER_SIZE);

    return 0;
}