#include "socket_tool.h"

int create_socket(const char *host, const char *port)
{
    /* Configure local address */
    struct addrinfo server_address;
    memset(&server_address, 0, sizeof(server_address));
    /* IPv4- define addressing version */
    server_address.ai_family = AF_INET;
    /* Protocol type SOCK_STREAM- TCP */
    server_address.ai_socktype = SOCK_STREAM;
    /* */
    server_address.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(host, port, &server_address, &bind_address);

    /* Initialization of int socket_listen- socket descriptor */
    int socket_listen;
    /*!
        Create new socket, input arguments (parameters):
            \arg ai_family- version of IP
            \arg ai_socktype- protocol type
            \arg ai_protocol-
    */
    socket_listen = socket(bind_address->ai_family,
                           bind_address->ai_socktype, bind_address->ai_protocol);

    /* Check the validation of recently created socket */
    if (socket_listen < 1)
    {
        fprintf(stderr, "socket() failed");
        exit(1);
    }

    /* Bind the socket to local address */
    if (bind(socket_listen,
             bind_address->ai_addr, bind_address->ai_addrlen))
    {
        fprintf(stderr, "bind() failed");
        exit(1);
    }

    freeaddrinfo(bind_address);

    if (listen(socket_listen, NO_OF_REPEAT) < 0)
    {
        fprintf(stderr, "listen() failed");
        exit(1);
    }

    return socket_listen;
}