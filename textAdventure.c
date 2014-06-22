/*
*
* Copyright Alexis Bauchu 2014
*
*
*/

#include <albob/string.h>
#include <stdio.h>

void debug(StringRef ref)
{
    printf("Ref: %u, Content: \"%s\"\n", ref, str_getCString(ref));
}

int main(int arg_number, char * arguments[])
{
    // init engine
    initStringPool();

    // do stuff
    StringRef ref1 = str_createWithCString("bonjour");
    debug(ref1);
    StringRef ref2 = str_createWithCString("buenos dias");
    debug(ref2);

    // exit
    return 0;
}

