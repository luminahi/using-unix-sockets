#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"

#define FILEPATH "/tmp/custom.sock"
#define BUFFER_SIZE 128

void publish(char* filepath, int buffer_size, char* message) {
    int socket_fd;
    struct sockaddr_un addr;
    int addr_len;
    char buffer[buffer_size];
    
    strncpy(buffer, message, strlen(message));

    socket_fd = assert_socket(FILEPATH, SOCK_DGRAM, &addr);
    send_message_dgram(socket_fd, buffer, &addr);
}

int main(int argc, char* argv[]) {
    publish(FILEPATH, BUFFER_SIZE, argv[1] ? argv[1] : "no message");

    return 0;
}
