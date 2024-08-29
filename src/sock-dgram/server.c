#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int socket_fd;
    struct sockaddr_un addr;
    int addr_len;
    char buffer[255];

    unlink("msg.sock");

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "msg.sock", sizeof(addr.sun_path) - 1);

    socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    bind(socket_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un));
    perror("bind");

    int num_bytes = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, (socklen_t*)&addr_len);
    perror("recvfrom");

    buffer[num_bytes] = '\0';
    printf("%s\n", buffer);

    return 0;
}