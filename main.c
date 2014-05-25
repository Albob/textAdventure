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
    printf("Ref: %u, Content:%s\n", ref1, str_getCString(ref1));
    StringRef ref2 = str_createWithCString("buenos dias");
    printf("Ref: %u, Content:%s\n", ref2, str_getCString(ref2));

    // exit
    return 0;
}

