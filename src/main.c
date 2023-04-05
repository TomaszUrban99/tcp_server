
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
#include "file_tool.h"

#define CONFIGURATION_FILE "./configuration_file.txt"
#define WIFI_CREDENTIALS_FILE "./wifi_credentials.txt"

int main(int argc, char *argv[])
{
    struct clients_list clients;

    clients.head = NULL;
    clients.tail = NULL;

    /* Read web server configuration */
    struct configuration newConfiguration;
    getConfiguration(&newConfiguration, CONFIGURATION_FILE);

    /* Copy strings with configuration. (Trying to avoid memory leakage)*/
    char ipAdress[25];
    strcpy(ipAdress, newConfiguration.ip_address);
    char wifiCredentials[25];
    strcpy(wifiCredentials, newConfiguration.wifi_credentials);
    char httpResponse[25];
    strcpy(httpResponse, newConfiguration.http_response);

    /* Free memory allocated by reading the configuration file */
    freeConfiguration(&newConfiguration);

    /*
        Structure that specifies criteria
        for selecting the socket address
    */
    struct sockaddr_in hints;

    /* Set field values to 0 */
    memset(&hints, 0, sizeof(hints));

    /* Specify criteria for selecting socket address */
    hints.sin_family = AF_INET;
    hints.sin_port = htons(newConfiguration.port_number);
    inet_aton(ipAdress, &hints.sin_addr);

    /*
        Get a socket descriptor
        int domain- AF_INET, ipv4 protocol
        SOCK_STREAM- TCP Protocol
        0- protocol is chosen automatically
    */
    int socket_descriptor = socket(AF_INET,
                                   SOCK_STREAM, 0);

    if (socket_descriptor < 0)
    {
        fprintf(stderr, "Failed to create socket");
        return -1;
    }

    /* bind socket to local address */
    if (bind(socket_descriptor, (struct sockaddr *)&hints,
             sizeof(hints)))
    {
        fprintf(stderr, "Failed to bind the socket");
        return -1;
    };

    /* Listen */
    printf("Listening...\n");
    if (listen(socket_descriptor, 10) < 0)
    {
        fprintf(stderr, "Failed to listen");
        return -1;
    }

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_descriptor, &master);
    int max_socket = socket_descriptor;

    while (1)
    {
        /*
            Remember to make a copy of master!
            Select modifies the structure the
            given fd_set structure!
        */
        fd_set reads;
        reads = master;

        if (select(max_socket + 1, &reads, 0, 0, 0) < 0)
        {
            fprintf(stderr, "Select failed");
            return -1;
        }

        int socket_number;

        for (socket_number = 1; socket_number <= max_socket; ++socket_number)
        {
            if (FD_ISSET(socket_number, &reads))
            {
                /*
                    If socket descriptor equals socket number,
                    the new client is ready to establish a connection
                */
                if (socket_descriptor == socket_number)
                {
                    struct sockaddr_storage client_address;
                    socklen_t address_length = sizeof(client_address);
                    int socket_client = accept(socket_descriptor,
                                               (struct sockaddr *)&client_address,
                                               &address_length);

                    if (socket_client < 1)
                    {
                        fprintf(stderr, "Failed to create socket\n");
                        return -1;
                    }

                    FD_SET(socket_client, &master);
                    if (socket_client > max_socket)
                        max_socket = socket_client;

                    char address_buffer[50];

                    getnameinfo((struct sockaddr *)&client_address,
                                address_length, address_buffer, sizeof(address_buffer),
                                0, 0, 0);

                    printf("%s%s\n", "New connection from: ", address_buffer);
                }
                else
                {
                    /* Read message incoming to web server */
                    char read[1024];
                    int received_bytes = recv(socket_number, read, sizeof(read), 0);
                    printf("%s%s\n", "Received message: ", read);

                    struct http_request newHttp;
                    receiveRequest(&newHttp, read);
                    if (!strcmp(newHttp.requestedPath, wifiCredentials))
                    {
                        struct wifi_credentials wifi;
                        getWifiCredentials(&wifi, read);
                        safeWifiCredentials(&wifi, WIFI_CREDENTIALS_FILE);
                    }

                    /* Create HTTP Response */
                    createHTTPResopnse(&newHttp, httpResponse);
                    /* Allocate memory for array to store response */
                    char *responseArray = (char *)calloc(getFileSize(httpResponse), sizeof(char));
                    /*
                        Put HTTP response to sent to an array.
                        Variable int bytes_to_send- stores the size of file with
                        HTTP response.
                    */
                    int bytes_to_send = responseToArray(&newHttp, httpResponse, responseArray);
                    /* int sent_bytes- variable for storing number of sent bytes */
                    int sent_bytes = 0;

                    /*
                        Repeat the loop until the number of sent bytes is equal
                        to the number of bytes that should be sent.
                    */
                    while (sent_bytes < bytes_to_send)
                    {
                        int sentones = send(socket_number, responseArray + sent_bytes, bytes_to_send - sent_bytes, 0);
                        /* If sentones is lower than print an error */
                        if (sentones < 0)
                        {
                            fprintf(stderr, "%s\n", "Failed to send()");
                        }
                        /* Add number of recently sent bytes to the total number of sent bytes */
                        sent_bytes = sent_bytes + sentones;
                    }

                    /* Free allocated memory. Avoiding memory leakage. */
                    free(newHttp.requestedPath);
                    free(responseArray);
                }
            }
        }
    }
    return 0;
}