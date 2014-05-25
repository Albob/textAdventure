/* Copyright Alexis Bauchu 2014 */
#include <stdio.h>
#include <stdlib.h>
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

static String g_stringPool[ kStringPoolSize ];
static int g_stringFreeList[ kStringPoolSize ];

void
initString(String * str)
{
    str->cstr = NULL;
    str->refCount = 0;
}

void
initStringPool()
{
    for (uint i = 0; i < kStringPoolSize; ++i)
    {
        initString(&g_stringPool[i]);
        g_stringFreeList[i] = kFree;
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
    for (uint i = kStringPoolSize; i > 0; --i) {
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
    g_stringPool[ref].cstr = NULL;
}

StringRef
str_createWithCString(const char * c_string)
{
    StringRef ref = allocRef();
    g_stringPool[ref].cstr = c_string;
    return ref;
}

StringRef
str_createWithStringRef(StringRef other_ref)
{
    checkValidRef(other_ref);

    StringRef ref = allocRef();
    g_stringPool[ref].cstr = g_stringPool[other_ref].cstr;
    return ref;
}

