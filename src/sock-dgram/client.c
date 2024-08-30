#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#define FILEPATH "/tmp/custom.sock"
#define BUFFER_SIZE 128

int main(int argc, char* argv[]) {
    int socket_fd;
    struct sockaddr_un addr;
    int addr_len;
    char buffer[BUFFER_SIZE];

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, FILEPATH, sizeof(addr.sun_path) - 1);

    const char* message = "cool message";
    strncpy(buffer, message, strlen(message));

    socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    perror("socket");

    sendto
    (
        socket_fd, 
        buffer, 
        strlen(buffer), 
        0, 
        (struct sockaddr*)&addr, 
        sizeof(addr)
    );
    perror("sendto");

    return 0;
}