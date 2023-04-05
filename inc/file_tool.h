#ifndef FILE_TOOL_H
#define FILE_TOOL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/*!
    \brief Structure for storing information necessary
    for proper server functioning.
*/
struct configuration
{
    char *ip_address;
    char *port_number;
    char *wifi_credentials;
    char *http_response;
};

/*!
    \brief Function to determine the size of the file

    \param char *filename- pointer to char array with the name of file
    of which the size should be determined

    \retval long fileSize- the size of the given file
*/
long getFileSize(char *filename);

int getConfiguration(struct configuration *configServer,
                     char *filename);

#endif