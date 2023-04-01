#ifndef FILE_TOOL_H
#define FILE_TOOL_H

#include <stdio.h>
#include <errno.h>

/*!
    \brief Function to determine the size of the file

    \param char *filename- pointer to char array with the name of file
    of which the size should be determined

    \retval long fileSize- the size of the given file
*/
long getFileSize(char *filename);

#endif