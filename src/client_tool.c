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

/*
    struct client_info *get_client()- get the client_info
    structure for the socket with given number
*/
struct client_info *get_client(int socket,
                               struct clients_list *clients)
{
    struct clients_list_node *tmp2 = clients->head;
    struct clients_list_node *tmpNode = clients->head;

    while (tmpNode != NULL)
    {
        if (tmpNode->client.socket == socket)
        {
            clients->head = tmp2;
            return &(tmpNode->client);
        }
        tmpNode = tmpNode->next;
    }

    if (!add_client_to_list(socket, clients))
        return NULL;

    return &(clients->head->client);
}

void drop_client(int socket,
                 struct clients_list *clients)
{
    struct clients_list_node *tmpNode = clients->head;
    struct clients_list_node *tmpNodeSecond;

    while (tmpNode != NULL)
    {

        if (tmpNode->client.socket == socket)
        {
            tmpNodeSecond->next = tmpNode->next;
            free(tmpNode);
            return;
        }

        tmpNodeSecond = tmpNode;
        tmpNode = tmpNode->next;
    }
}

void print_clients_list(struct clients_list *clients)
{
    struct clients_list_node *tmpNode;

    while (tmpNode != NULL)
    {
        printf("%s%d\n", "Clients socket: ", tmpNode->client.socket);
        tmpNode = tmpNode->next;
    }
}
/*
    void free_clients(struct client_list *clients)- function for
    freeing the memory allocated for lists node of the list
*/
void free_clients(struct clients_list *clients)
{
    int i = 0;
    struct clients_list_node *tmpNode;
    while (clients->head != NULL)
    {
        i++;
        tmpNode = clients->head;
        clients->head = clients->head->next;
        free(tmpNode);
        printf("%d\n", i);
    }
}
