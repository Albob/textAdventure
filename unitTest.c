/*
*
* Copyright Alexis Bauchu 2014
* 
* This is the unit test set. The program exits successfully
* if all the tests ran as expected.
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
    // do stuff
    StringRef ref1 = str_createWithCString("bonjour");
    debug(ref1);
    StringRef ref2 = str_createWithCString("buenos dias");
    debug(ref2);

    // exit
    return 0;
}

