#ifndef HTTP_REQUEST_HH
#define HTTP_REQUEST_HH

#include <string.h>

/* Enumeration type for different types of requests */
enum requestTypes
{
    GET,
    POST
};

struct http_request
{
    enum requestTypes requestType;
    char *requestedPath;
    double httpVersion;
};

struct http_request *receiveRequest(struct http_request *newRequest, char *incomingRequest);

#endif