#include "client_tool.h"

struct clients_list *add_client_to_list(int socket,
                                        struct clients_list *clients)
{
    struct clients_list_node *tmpNode =
        (struct clients_list_node *)calloc(1, sizeof(struct clients_list_node));

    if (!tmpNode)
    {
        fprintf(stderr, "Out of memory!");
        exit(1);
    }

    tmpNode->client.addres_length =
        sizeof(tmpNode->client.address);
    tmpNode->client.socket = socket;

    tmpNode->next = clients->head;
    clients->head = tmpNode;

    return clients;
}