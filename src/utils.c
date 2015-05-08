/*
 * Text Adventure, Copyright Alexis Bauchu 2014
 */

#include <string.h>
#include <stdlib.h>

#include "utils.h"

void say(const char * message, int insert_newline)
{
    if (insert_newline) {
        puts(message);
    }
    else {
        fputs(message, stdout);
    }
}

char * string_copy(const char * str)
{
    if (str == NULL) return NULL;

    size_t length = strlen(str);
    char * new_str = (char*)malloc(sizeof(char) * length + 1);
    strcpy(new_str, str);

    return new_str;
}

