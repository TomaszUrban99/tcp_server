
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
#include "content_type.h"
#include "socket_tool.h"
#include "client_tool.h"
#include "http_request.h"

#define IP_LENGTH 50
#define PORT_NUMBER "8080"

int main(int argc, char *argv[])
{
    char address[100];
    struct clients_list clients;
    struct client_info *tmpClient;
    struct http_request incomingRequest;
    clients.head = NULL;
    clients.tail = NULL;

    const char *content_type = get_content_type(argv[1]);

    receiveRequest(&incomingRequest, argv[2]);

    printf("%s%d\n", "Request type: ", incomingRequest.requestType);

    printf("%s", content_type);
    printf("\n");

    int socket_listen = 0;
    socket_listen = socket(AF_INET, SOCK_STREAM, 0);

    add_client_to_list(socket_listen, &clients);
    printf("%s%d", "Head1: ", clients.head->client.socket);

    add_client_to_list(socket_listen + 1, &clients);
    printf("%s%d\n", "Head2: ", clients.head->client.socket);
    add_client_to_list(socket_listen + 2, &clients);
    printf("%s%d\n", "Head3: ", clients.head->client.socket);

    /*get_client(socket_listen, &clients);*/

    print_clients_list(&clients);

    printf("%d\n", clients.head->client.socket);

    drop_client(4, &clients);

    add_client_to_list(socket_listen + 3, &clients);

    printf("%s", "Lista klientow: ");
    print_clients_list(&clients);

    printf("%s", "Lista klientow: ");
    print_clients_list(&clients);
    free_clients(&clients);

    return 0;
}