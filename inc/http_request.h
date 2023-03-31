#ifndef HTTP_REQUEST_HH
#define HTTP_REQUEST_HH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Enumeration type for different types of requests */
enum requestTypes
{
    NOT_RECOGNIZED,
    GET,
    POST
};

struct http_request
{
    enum requestTypes requestType;
    char *requestedPath;
};

struct http_request *receiveRequest(struct http_request *newRequest,
                                    char *incomingRequest);

char *receiveRequestPath(char *incomingRequest, char *path);
#endif