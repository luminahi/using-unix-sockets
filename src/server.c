#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include "socket.h"

#define FILEPATH "/tmp/custom.sock"
#define BUFFER_SIZE 128

int file_exists(const char* file_path) {
    struct stat file_stat;
    return (stat(file_path, &file_stat) == 0);
}

void handle_sigint(int sig) {
    printf("\ncleaning up...\n");
    unlink(FILEPATH);
    exit(EXIT_SUCCESS);
}

void start_server(char* file_path, int buffer_size) {
    char client_buffer[buffer_size];
    char server_buffer[buffer_size];
    
    int server_socket_fd;
    int client_socket_fd;
    struct sockaddr_un address;

    if (file_exists(file_path)) unlink(file_path);

    create_socket(&server_socket_fd, &address, file_path);
    bind_socket(server_socket_fd, &address);
    listen_socket(server_socket_fd);

    printf("server bound to %s\nwaiting for connections...\n", file_path);
    
    char server_message[] = "message received";
    int message_length = sizeof(server_message);

    signal(SIGINT, handle_sigint);

    while (1) {
        client_socket_fd = accept_connection(server_socket_fd);
        receive_message(client_socket_fd, client_buffer, buffer_size);

        printf("Client message: %s\n", client_buffer);
        memset(client_buffer, 0, BUFFER_SIZE);
        
        send_message(client_socket_fd, server_buffer, server_message, message_length);
        close(client_socket_fd);
    }
    
    close(server_socket_fd);
    unlink(file_path);
}

int main(int argc, char* argv[]) {
    start_server(FILEPATH, BUFFER_SIZE);

    return 0;
}
