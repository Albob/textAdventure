/*
* string.h
* Copyright Alexis Bauchu 2014
* 
* Define a string type and function to manipulate them.
*/

#ifndef tae_string_h
#define tae_string_h

typedef unsigned int StringRef;

struct String
{
    const char * const cstr;
    unsigned int refCount;
    int isAutoreleased;
};

void str_retain(StringRef);
void str_release(StringRef);
void str_autorelease(StringRef);
StringRef str_createWithCString(const char * c_string);
StringRef str_createWithStringRef(StringRef ref);
StringRef str_initWithCString(const char * c_string);
const char * str_getCString(StringRef);

#endif 
