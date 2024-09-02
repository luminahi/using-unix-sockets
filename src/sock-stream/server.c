#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include "socket.h"

#define FILEPATH "/tmp/custom.sock"
#define BUFFER_SIZE 128

int file_exists(const char* filepath) {
    struct stat file_stat;
    return (stat(filepath, &file_stat) == 0);
}

void handle_sigint(int sig) {
    printf("\ncleaning up...\n");
    unlink(FILEPATH);
    exit(EXIT_SUCCESS);
}

void start_server(char* filepath, int buffer_size) {
    char buffer[buffer_size];
    
    int server_socket_fd;
    int client_socket_fd;
    struct sockaddr_un address;

    if (file_exists(filepath)) unlink(filepath);
    
    server_socket_fd = assert_socket(filepath, SOCK_STREAM, &address);
    bind_socket(server_socket_fd, &address);
    listen_socket(server_socket_fd);

    printf("server bound to %s\nwaiting for connections...\n", filepath);
    
    char server_message[] = "message received";
    int message_length = sizeof(server_message);

    signal(SIGINT, handle_sigint);

    while (true) {
        client_socket_fd = accept_connection(server_socket_fd);
        int num_bytes = receive_message_stream(client_socket_fd, buffer, buffer_size);

        buffer[num_bytes] = '\0';
        printf("Client message: %s\n", buffer);
        
        send_message_stream(client_socket_fd, server_message, message_length);
        close(client_socket_fd);
    }
}

int main(int argc, char* argv[]) {
    start_server(FILEPATH, BUFFER_SIZE);

    return 0;
}
