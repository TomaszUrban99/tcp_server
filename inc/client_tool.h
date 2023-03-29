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

/*!
    struct clients_list_node- structure modelling
    the node of the list

    \field1 struct client_info client- field with
    client_info structure for storing information
    about client

    \field2 struct clients_list_node *next- pointer
    to the next node of the list
*/
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

struct client_info *get_client(int socket,
                               struct clients_list *clients);

/*!
    void drop_client()- for given socket, function removes
    the client from the list of clients

    \arg int socket- socket descriptor
    \arg struct clients_list *clients- reference to the list
    of clients
*/
void drop_client(int socket,
                 struct clients_list *clients);

void print_clients_list(struct clients_list *clients);

/*!
    void free_clients(struct client_list *clients)- function for
    freeing the memory allocated for lists node of the list

    \arg struct clients_list *clients- reference to the list of the clients

    \retval void- functio does not return any value
*/
void free_clients(struct clients_list *clients);

#endif