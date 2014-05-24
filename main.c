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
    // init engine
    initStringPool();

    // do stuff
    StringRef ref = str_createWithCString("bonjour");
    printf("File ref: %u\n", ref);

    // exit
    return 0;
}

