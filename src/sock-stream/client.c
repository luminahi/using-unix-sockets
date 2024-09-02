#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include "socket.h"

#define FILEPATH "/tmp/custom.sock"
#define BUFFER_SIZE 128

void publish(char* filepath, int buffer_size, char* message) {
    char buffer[buffer_size];
    int socket_fd;
    struct sockaddr_un address;

    socket_fd = assert_socket(filepath, SOCK_STREAM, &address);
    connect_socket(socket_fd, &address);

    send_message_stream(socket_fd, message, strlen(message));
    receive_message_stream(socket_fd, buffer, buffer_size);

    printf("Server message: %s\n", buffer);
    close(socket_fd);
}

int main(int argc, char* argv[]) {
    publish(FILEPATH, BUFFER_SIZE, argv[1] ? argv[1] : "no message");

    return 0;
}
