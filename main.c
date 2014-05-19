/*
*
* Copyright Alexis Bauchu
*
*
*/

#include <albob/string.h>
#include <stdio.h>

int main(int arg_number, char * arguments[])
{
    StringRef ref = str_createWithCString("bonjour");
    printf("File ref: %u\n", ref);
    return 0;
}

