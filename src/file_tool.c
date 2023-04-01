#include "file_tool.h"

/* Function for determining the file size */
long getFileSize(char *filename)
{
    FILE *filePtr = fopen(filename, "r");

    FILE *filePtr2 = fopen("plik1.txt", "r");
    if (filePtr2 == NULL)
    {
        printf("%s\n", "Tuuuuuuuuuuuuuuuuusk");
    }
    FILE *filePtr3 = fopen("plik2.html", "r");
    if (filePtr3 == NULL)
    {
        printf("%s\n", "Taaaaaaaaaaaaaaaask");
    }

    printf("%s%s\n", "File to determ: ", filename);

    /* If open failed return -1 */
    if (filePtr == NULL)
    {
        fprintf(stderr, "Value of error: %d\n", errno);
        perror("Error printed by error");
        printf("%s\n", "Tusk, tusk, tusk");
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
    fclose(filePtr);

    return fileSize;
}