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

void createHTTPResopnse(struct http_request *newRequest, char *httpResponse)
{
    FILE *filePointer = fopen(httpResponse, "w");

    if (newRequest->requestType == GET)
    {
        fputs("HTTP/1.1 200 OK\n", filePointer);
    }

    newRequest->responseFileSize = getFileSize(newRequest->requestedPath);

    fputs("Content-Length: ", filePointer);
    fprintf(filePointer, "%d\n", newRequest->responseFileSize);
    fputs("Content-Type: text/html\r\n", filePointer);
    fputs("Connection: keep-alive\r\n\r\n", filePointer);

    FILE *content = fopen(newRequest->requestedPath, "r");

    char c = fgetc(content);
    while (c != EOF)
    {
        fputc(c, filePointer);
        c = fgetc(content);
    }

    fclose(filePointer);
    fclose(content);
}

int responseToArray(struct http_request *newRequest,
                    char *httpResponseFilename, char *sendResponse)
{
    int responseFileSize = getFileSize(httpResponseFilename);

    FILE *filePtr = fopen(httpResponseFilename, "r");

    if (filePtr == NULL)
    {
        fprintf(stderr, "%s\n", "Failed to open response file");
        perror("Failed to open file");
    }
    /* Allocate memory for array with answers */

    if (sendResponse == NULL)
        printf("%s\n", "Tusk");

    int i = 0;
    char c = fgetc(filePtr);
    while (c != EOF)
    {
        sendResponse[i] = c;
        c = fgetc(filePtr);
        i++;
    }

    return strlen(sendResponse);
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

    while (*tmpChar != ' ' && *tmpChar != '?')
    {
        tmpChar++;
        size++;
    }

    tmpChar = tmpChar - size;
    path = (char *)calloc(size + 2, sizeof(char));
    memcpy(path + 1, tmpChar, size);
    *path = '.';

    printf("%s\n", path);
    return path;
}

void getWifiCredentials(struct wifi_credentials *wifi, char *incomingRequests)
{
    char *tmpChar = strstr(incomingRequests, SSID);

    if (tmpChar == NULL)
    {
        fprintf(stderr, "%s\n", "Missing SSID");
    }
    else
    {
        tmpChar = tmpChar + SSID_NUMBER;
        int size = 0;

        while (*tmpChar != '&')
        {
            tmpChar++;
            size++;
        }

        tmpChar = tmpChar - size;

        if (size > 0)
        {
            wifi->ssid = (char *)calloc(size + 1, sizeof(char));
            memcpy(wifi->ssid, tmpChar, size);

            printf("%s%s\n", "SSID: ", wifi->ssid);
        }

        tmpChar = strstr(tmpChar, PASSWORD);

        if (tmpChar == NULL)
        {
            fprintf(stderr, "%s\n", "Missing PASSWORD");
        }
        else
        {
            tmpChar = tmpChar + PASSWORD_NUMBER;
            size = 0;
            while (*tmpChar != ' ')
            {
                tmpChar++;
                size++;
            }
            tmpChar = tmpChar - size;
            if (size > 0)
            {
                wifi->password = (char *)calloc(size + 1, sizeof(char));
                memcpy(wifi->password, tmpChar, size);

                printf("%s%s\n", "Password: ", wifi->password);
            }
        }
    }
}