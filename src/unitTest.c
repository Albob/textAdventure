/*
*
* Copyright Alexis Bauchu 2014
* 
* This is the unit test set. The program exits successfully
* if all the tests ran as expected.
*
*/

#include <albob/array.h>
#include <albob/string.h>
#include <albob/debug.h>
#include <stdio.h>

void debug(StringRef ref)
{
    // debugLog("Ref: %u, Content: \"%s\"\n", ref, strCStr(ref));
    debugLogLn(ref);
}

int main(int arg_number, char * arguments[])
{
    // do stuff
    StringRef ref1 = strMake("bonjour");
    debug(ref1);
    StringRef ref2 = strMake("buenos dias");
    debug(ref2);

    char * test_carray[] = {"salut", "les", "petits", "coco", NULL};
    array_iterator_t it;
    array_iterator_init(&it, (void*)test_carray);
    char * s = array_next(&it);
    while (s != NULL)
    {
        printf("%s ", s);
        s = array_next(&it);
    }
    printf("\n");

    // exit
    return 0;
}

