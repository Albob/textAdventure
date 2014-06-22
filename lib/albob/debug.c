/*
*
* libalbob, debug.h 
* Copyright Alexis Bauchu 2014
* 
* These are utility functions used to help debug
*
*/

#include <stdio.h>
#include "debug.h"

void debugLog(StringRef ref)
{
    printf("%s\n", str_getCString(ref));
}

void debugLogLn(StringRef ref)
{
    printf(str_getCString(ref));
}

