#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"

int main(int argc, char* argv[]) {

    char buffer[128];
    int socket_fd;
    struct sockaddr_un address;

    create_socket(&socket_fd, &address, "/tmp/mysocket");
    connect_socket(socket_fd, &address);

    send_message(socket_fd, buffer, "client message");
    receive_message(socket_fd, buffer, sizeof(buffer));

    printf("Server message: %s\n", buffer);
    close(socket_fd);

    return 0;
}