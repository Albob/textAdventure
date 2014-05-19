/* Copyright Alexis Bauchu 2014 */
#include <stdio.h>
#include "string.h"

StringRef
str_createWithCString(const char * c_string)
{
    printf("%s", c_string);
    printf("\n");
    return 1;
}

