#ifndef CONTENT_TYPE
#define CONTENT_TYPE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
    const char *get_content_type(const char *path) - function
    returning the type of the content based on it's path

    \arg const char *path - characters pointed by path pointer, which
    shows the file's path on the web server

    \retval const char -constant value of characters describing the type
    of the content

*/
const char *get_content_type(const char *path);

#endif