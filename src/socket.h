#ifndef _SOCKET_H
#define _SOCKET_H

void create_socket(int*, struct sockaddr_un*, char*);

void connect_socket(int, struct sockaddr_un*);

void bind_socket(int, struct sockaddr_un*);

void listen_socket(int);

int accept_connection(int);

void receive_message(int, char*);

void send_message(int, char*, char*);

#endif
