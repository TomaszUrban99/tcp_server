#include "http_request.h"

struct http_request *receiveRequest(struct http_request *newRequest, char *incomingRequest)
{
    if (strstr(incomingRequest, "GET") != NULL)
    {
        newRequest->requestType = GET;
    }

    if (strstr(incomingRequest, "POST") != NULL)
    {
        newRequest->requestType = POST;
    }

    return newRequest;
}