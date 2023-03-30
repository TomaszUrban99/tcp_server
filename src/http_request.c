#include "http_request.h"

struct http_request *receiveRequest(struct http_request *newRequest,
                                    char *incomingRequest)
{
    char *tmpChar = incomingRequest;

    /* Get the type of http request */
    if (strstr(incomingRequest, "GET") != NULL)
        newRequest->requestType = GET;

    if (strstr(incomingRequest, "POST") != NULL)
        newRequest->requestType = POST;
    else
    {
        fprintf(stderr, "%s", "HTTP request has not been recognized\n");
        return NULL;
    }

    printf("%s%s\n", "PATH: ", receiveRequestPath(tmpChar));

    return newRequest;
}

char *receiveRequestPath(char *incomingRequest)
{
    int size = 0;
    char *tmpChar = strstr(incomingRequest, "/");

    if (tmpChar == NULL)
    {
        fprintf(stderr, "%s\n", "Path request has not been found\n");
        return NULL;
    }

    incomingRequest = tmpChar;

    while (*incomingRequest != ' ')
    {
        incomingRequest++;
        size++;
    }

    return strncpy(incomingRequest - size, tmpChar, size);
}