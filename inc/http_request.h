#ifndef HTTP_REQUEST_HH
#define HTTP_REQUEST_HH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_tool.h"

#define SSID "ssid="
#define SSID_NUMBER 5
#define PASSWORD "password="
#define PASSWORD_NUMBER 9

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

struct wifi_credentials
{
    char *ssid;
    char *password;
};

struct http_request *receiveRequest(struct http_request *newRequest,
                                    char *incomingRequest);

void createHTTPResopnse(struct http_request *newRequest, char *httpResponse);

char *receiveRequestPath(char *incomingRequest, char *path);

void getWifiCredentials(struct wifi_credentials *wifi, char *incomingResponse);

#endif