#include "http_request.h"

struct http_request *receiveRequest(struct http_request *newRequest,
                                    char *incomingRequest)
{
    char *tmpChar = incomingRequest;
    char *path;

    /* Get the type of http request */
    if (strstr(incomingRequest, "GET") != NULL)
        newRequest->requestType = GET;
    else
    {
        if (strstr(incomingRequest, "POST") != NULL)
            newRequest->requestType = POST;
        else
        {
            fprintf(stderr, "%s", "HTTP request has not been recognized\n");
            return NULL;
        }
    }

    path = receiveRequestPath(tmpChar, path);

    if (path == NULL)
    {
        fprintf(stderr, "%s", "Path has not been recognized\n");
        free(path);
        return NULL;
    }

    newRequest->requestedPath = path;

    printf("%s%s\n", "Path: ", newRequest->requestedPath);

    return newRequest;
}

char *receiveRequestPath(char *incomingRequest, char *path)
{
    int size = 0;
    char *tmpChar = strstr(incomingRequest, "/");

    if (tmpChar == NULL)
    {
        fprintf(stderr, "%s\n", "Path request has not been found\n");
        return NULL;
    }

    while (*tmpChar != ' ')
    {
        tmpChar++;
        size++;
    }

    tmpChar = tmpChar - size;
    path = (char *)calloc(size + 1, sizeof(char));
    memcpy(path, tmpChar, size);

    printf("%s\n", path);
    return path;
}