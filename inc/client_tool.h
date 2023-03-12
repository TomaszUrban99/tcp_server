#ifndef CLIENT_TOOL_HH
#define CLIENT_TOOL_HH

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_REQUEST_SIZE 2048

struct client_info
{
    socklen_t addres_length;
    struct sockaddr_storage address;
    int socket;
    char request[MAX_REQUEST_SIZE];
};

struct clients_list_node
{
    struct client_info client;
    struct clients_list_node *next;
};

struct clients_list
{
    struct clients_list_node *head;
    struct clients_list_node *tail;
};

struct clients_list *add_client_to_list(int socket,
                                        struct clients_list *clients);

#endif