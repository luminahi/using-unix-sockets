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
    int server_socket_fd;
    int client_socket_fd;
    struct sockaddr_un address;

    create_socket(&server_socket_fd, &address, "/tmp/mysocket");
    bind_socket(server_socket_fd, &address);
    
    listen_socket(server_socket_fd);
    client_socket_fd = accept_connection(server_socket_fd);

    receive_message(client_socket_fd, buffer, sizeof(buffer));
    
    printf("Client message: %s\n", buffer);
    
    send_message(client_socket_fd, buffer, "server message");

    close(client_socket_fd);
    close(server_socket_fd);
    unlink("/tmp/mysocket");

    return 0;
}
