#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"

#define BUFFER_SIZE 128

int file_exists(const char* file_path) {
    struct stat file_stat;
    return (stat(file_path, &file_stat) == 0);
}

int main(int argc, char* argv[]) {
    char* file_path = "/tmp/mysocket";
    char client_buffer[BUFFER_SIZE];
    char server_buffer[BUFFER_SIZE];
    
    int server_socket_fd;
    int client_socket_fd;
    struct sockaddr_un address;

    if (file_exists(file_path)) unlink(file_path);

    create_socket(&server_socket_fd, &address, file_path);
    bind_socket(server_socket_fd, &address);
    listen_socket(server_socket_fd);

    printf("server running...\n");
    
    char server_message[] =  "message received";
    int message_length = sizeof(server_message);

    while (1) {
        client_socket_fd = accept_connection(server_socket_fd);
        receive_message(client_socket_fd, client_buffer, BUFFER_SIZE);

        printf("Client message: %s\n", client_buffer);
        memset(client_buffer, 0, BUFFER_SIZE);
        
        send_message(client_socket_fd, server_buffer, server_message, message_length);
        close(client_socket_fd);
    }
    
    close(server_socket_fd);
    unlink(file_path);

    return 0;
}
