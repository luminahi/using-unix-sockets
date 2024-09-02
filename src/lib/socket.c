#include <sys/un.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "socket.h"

int assert_socket(char* filepath, int type, struct sockaddr_un* address) {
    int socket_fd;
    
    socket_fd = socket(AF_UNIX, type, 0);
    if (socket_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(address, 0, sizeof(struct sockaddr_un));
    address->sun_family = AF_UNIX;
    strncpy(address->sun_path, filepath, sizeof(address->sun_path) - 1);

    return socket_fd;
}

void connect_socket(int socket_fd, struct sockaddr_un* address) {
    if (connect(socket_fd, (struct sockaddr*)address, sizeof(struct sockaddr_un)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
}

void bind_socket(int socket_fd, struct sockaddr_un* address) {
    if (bind(socket_fd, (struct sockaddr*)address, sizeof(struct sockaddr_un)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
}

void listen_socket(int socket_fd) {
    if (listen(socket_fd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

int accept_connection(int server_socket_fd) {
    int client_socket_fd = accept(server_socket_fd, NULL, NULL);
    if (client_socket_fd == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    return client_socket_fd;
}

int receive_message_stream(int socket_fd, char* buffer, int buffer_length) {
    int num_bytes = recv(socket_fd, buffer, buffer_length, 0);
    if (num_bytes == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    return num_bytes;
}

int receive_message_dgram(int socket_fd, char* buffer, int buffer_size, struct sockaddr_un* addr, int* addr_len) {
    int num_bytes = recvfrom(socket_fd, buffer, buffer_size, 0, (struct sockaddr*)addr, (socklen_t*)addr_len);
    if (num_bytes == -1) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }

    return num_bytes;
}

void send_message_stream(int socket_fd, char* message, int message_length) {    
    if (send(socket_fd, message, message_length, 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }
}

void send_message_dgram(int socket_fd, char* message, struct sockaddr_un* addr) {
    if (sendto(socket_fd, message, strlen(message), 0, (struct sockaddr*)addr, sizeof(struct sockaddr_un)) == -1) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
}
