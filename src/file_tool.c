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
    char ip_adress[28];

    while (fgets(readLine, sizeof(readLine), filePtr) != NULL)
    {
        int i = 0;
        char *tmpPtr;
        switch (readLine[0])
        {
        case '1':
            tmpPtr = strstr(readLine, "\"");
            tmpPtr = tmpPtr + 1;

            while (tmpPtr[i] != '\"')
            {
                ip_adress[i] = *(tmpPtr + i);
                i++;
            }

            configServer->ip_address = (char *)calloc(i, sizeof(char));
            memcpy(configServer->ip_address, ip_adress, i);

            printf("%s\n", configServer->ip_address);
            free(configServer->ip_address);
            break;
        case '2':
            tmpPtr = strstr(readLine, "\"");
            tmpPtr = tmpPtr + 1;

            while (tmpPtr[i] != '\"')
            {
                ip_adress[i] = *(tmpPtr + i);
                i++;
            }

            configServer->ip_address = (char *)calloc(i, sizeof(char));
            memcpy(configServer->ip_address, ip_adress, i);

            printf("%s\n", configServer->ip_address);
            free(configServer->ip_address);
            break;

        case '3':
            tmpPtr = strstr(readLine, "\"");
            tmpPtr = tmpPtr + 1;

            while (tmpPtr[i] != '\"')
            {
                ip_adress[i] = *(tmpPtr + i);
                i++;
            }

            configServer->ip_address = (char *)calloc(i, sizeof(char));
            memcpy(configServer->ip_address, ip_adress, i);

            printf("%s\n", configServer->ip_address);
            free(configServer->ip_address);
            break;

        case '4':
            tmpPtr = strstr(readLine, "\"");
            tmpPtr = tmpPtr + 1;

            while (tmpPtr[i] != '\"')
            {
                ip_adress[i] = *(tmpPtr + i);
                i++;
            }

            configServer->ip_address = (char *)calloc(i, sizeof(char));
            memcpy(configServer->ip_address, ip_adress, i);

            printf("%s\n", configServer->ip_address);
            free(configServer->ip_address);
            break;
        }
    }

    return 0;
}