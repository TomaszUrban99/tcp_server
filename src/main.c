
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

#define IP_LENGTH 50
#define PORT_NUMBER "8080"

int main(int argc, char *argv[])
{
    const char *content_type = get_content_type(argv[1]);

    printf("%s", content_type);
    printf("\n");

    int socket_listen = 0;
    socket_listen = create_socket("127.0.0.1", PORT_NUMBER);

    if (socket_listen < 1)
        printf("Kaczafi\n");
    else
    {
        printf("Tusk\n");
    };

    return 0;
}