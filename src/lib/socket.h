#ifndef _SOCKET_H
#define _SOCKET_H

int assert_socket(char*, int, struct sockaddr_un*);

void connect_socket(int, struct sockaddr_un*);

void bind_socket(int, struct sockaddr_un*);

void listen_socket(int);

int accept_connection(int);

int receive_message_stream(int, char*, int);

int receive_message_dgram(int, char*, int, struct sockaddr_un*, int*);

void send_message_stream(int, char*, int);

void send_message_dgram(int, char*, struct sockaddr_un*);

#endif
