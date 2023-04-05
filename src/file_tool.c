#include "file_tool.h"

/* Function for determining the file size */
long getFileSize(char *filename)
{
    FILE *filePtr = fopen(filename, "r");

    /* If open failed return -1 */
    if (filePtr == NULL)
    {
        fprintf(stderr, "Value of error: %d\n", errno);
        perror("Error printed by error");
        return -1;
    }

    /* If fseek failed, close the stream and return -1 */
    if (fseek(filePtr, 0, SEEK_END) < 0)
    {
        fclose(filePtr);
        return -1;
    }

    /* Measure the fileSize */
    long fileSize = ftell(filePtr);
    /* Close file */

    fseek(filePtr, 0, SEEK_SET);
    fclose(filePtr);

    return fileSize;
}

int getConfiguration(struct configuration *configServer,
                     char *filename)
{
    FILE *filePtr = fopen(filename, "r");

    if (filePtr == NULL)
    {
        fprintf(stderr, "%s\n", "Failed to open configuration file.");
        return -1;
    }

    char readLine[128];
    char tmpArray[28];

    while (fgets(readLine, sizeof(readLine), filePtr) != NULL)
    {
        int i = 0;
        char *tmpPtr;
        switch (readLine[0])
        {
        case '1':
            tmpPtr = strstr(readLine, "\"");
            tmpPtr = tmpPtr + 1;

            while (*(tmpPtr + i) != '\"')
            {
                i++;
            }

            configServer->ip_address = (char *)calloc(i, sizeof(char));
            memcpy(configServer->ip_address, tmpPtr, i);

            printf("%s\n", configServer->ip_address);
            break;

        case '2':
            tmpPtr = strstr(readLine, "\"");
            tmpPtr = tmpPtr + 1;

            while (*(tmpPtr + i) != '\"')
            {
                i++;
            }

            char *PortNumberArray = (char *)calloc(i, sizeof(char));
            memcpy(PortNumberArray, tmpPtr, i);

            sscanf(PortNumberArray, "%d", &configServer->port_number);
            printf("%s%d\n", "Numer portu: ", configServer->port_number);

            free(PortNumberArray);

            break;

        case '3':
            tmpPtr = strstr(readLine, "\"");
            tmpPtr = tmpPtr + 1;

            while (*(tmpPtr + i) != '\"')
            {
                i++;
            }

            configServer->wifi_credentials = (char *)calloc(i, sizeof(char));
            memcpy(configServer->wifi_credentials, tmpPtr, i);

            printf("%s\n", configServer->wifi_credentials);
            break;

        case '4':
            tmpPtr = strstr(readLine, "\"");
            tmpPtr = tmpPtr + 1;

            while (*(tmpPtr + i) != '\"')
            {
                i++;
            }

            configServer->http_response = (char *)calloc(i, sizeof(char));
            memcpy(configServer->http_response, tmpPtr, i);

            printf("%s\n", configServer->http_response);
            break;
        }
    }

    return 0;
}

void freeConfiguration(struct configuration *configServer)
{
    free(configServer->ip_address);
    free(configServer->wifi_credentials);
    free(configServer->http_response);
}