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
    // exit
    return 0;
}

