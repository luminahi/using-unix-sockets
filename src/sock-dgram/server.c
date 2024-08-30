#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define FILEPATH "/tmp/custom.sock"
#define BUFFER_SIZE 128

int file_exists(const char* file_path) {
    struct stat file_stat;
    return (stat(file_path, &file_stat) == 0);
}

int assert_socket(char* filepath, struct sockaddr_un* addr) {
    int socket_fd;
    
    memset(addr, 0, sizeof(struct sockaddr_un));
    addr->sun_family = AF_UNIX;
    strncpy(addr->sun_path, filepath, sizeof(addr->sun_path) - 1);

    socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (socket_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socket_fd, (struct sockaddr*)addr, sizeof(struct sockaddr_un)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    
    return socket_fd;
}

int receive_message(int socket_fd, char* buffer, struct sockaddr_un* addr, int* addr_len) {
    int num_bytes = recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)addr, (socklen_t*)addr_len);
    if (num_bytes == -1) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }

    return num_bytes;
}

int main(int argc, char* argv[]) {
    int socket_fd;
    int num_bytes;
    struct sockaddr_un addr;
    int addr_len;
    char buffer[BUFFER_SIZE];

    if (file_exists(FILEPATH)) {
        unlink(FILEPATH);
    }

    socket_fd = assert_socket(FILEPATH, &addr);
    num_bytes = receive_message(socket_fd, buffer, &addr, &addr_len);

    buffer[num_bytes] = '\0';
    printf("%s\n", buffer);

    return 0;
}