/*
*
* Copyright Alexis Bauchu 2014
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
    StringRef ref1 = str_createWithCString("bonjour");
    printf("Bonjour ref: %u\n", ref1);
    StringRef ref2 = str_createWithCString("buenos dias");
    printf("buenos dias ref: %u\n", ref2);

    // exit
    return 0;
}

