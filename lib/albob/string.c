/* Copyright Alexis Bauchu 2014 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

#define kStringPoolSize 500

enum {
    kAllocated,
    kFree
};

typedef struct
{
    const char * cstr;
    uint refCount;
} String;

static String * g_stringPool = NULL;
static int    * g_stringFreeList = NULL;

void
initString(String * str)
{
    str->cstr = NULL;
    str->refCount = 0;
}

void
initStringPool()
{
    if (g_stringPool == NULL)
    {
        g_stringPool = malloc(sizeof(String) * kStringPoolSize);
        g_stringFreeList = malloc(sizeof(int) * kStringPoolSize);

        for (uint i = 0; i < kStringPoolSize; ++i)
        {
            initString(&g_stringPool[i]);
            g_stringFreeList[i] = kFree;
        }
    }
}

void
checkValidRef(StringRef ref)
{
    if (ref > kBadStringRef && ref > kStringPoolSize)
    {
        printf("[Error] StringRef %u doesn't exist.\n", ref);
        exit(1025);
    }
}

StringRef
allocRef()
{
    initStringPool();

    for (uint i = 0; i < kStringPoolSize; i++) {
        if (g_stringFreeList[i] == kFree) {
            g_stringFreeList[i] = kAllocated;
            initString(&g_stringPool[i]);
            return i;
        }
    }

    return kBadStringRef;
}

void
freeRef(StringRef ref)
{
    checkValidRef(ref);

    g_stringFreeList[ref] = kFree;
    free((void*)g_stringPool[ref].cstr);
    g_stringPool[ref].cstr = NULL;
}

StringRef
strMake(const char * c_string)
{
    if (c_string == NULL)
        return 0;

    StringRef ref = allocRef();
    size_t length = strlen(c_string);
    char * new_str = malloc(sizeof(char) * (length + 1));
    memcpy(new_str, c_string, sizeof(char) * length);
    new_str[length] = '\0';
    g_stringPool[ref].cstr = new_str;
    return ref;
}

StringRef
strCopy(StringRef other_ref)
{
    checkValidRef(other_ref);

    StringRef ref = allocRef();
    g_stringPool[ref].cstr = g_stringPool[other_ref].cstr;
    return ref;
}

const char *
str_getCString(StringRef ref)
{
    return g_stringPool[ref].cstr;
}

