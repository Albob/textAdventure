/* Copyright Alexis Bauchu 2014 */
#include <stdio.h>
#include "string.h"

#define kStringPoolSize 500

static StringRef g_stringPool[ kStringPoolSize ] = {0};

void
initStringPool()
{
    for (unsigned int i = 0; i < kStringPoolSize; ++i) {
        g_stringPool[i] = 0;
    }
}

StringRef
str_createWithCString(const char * c_string)
{
    printf("%s", c_string);
    printf("\n");
    return 1;
}

void
str_initWithCString(StringRef ref, const char * c_string)
{
    
}

