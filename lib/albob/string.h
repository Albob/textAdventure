/*
* string.h
* Copyright Alexis Bauchu 2014
* 
* Define a string type and function to manipulate them.
*/

#ifndef tae_string_h
#define tae_string_h

typedef unsigned int uint;
typedef uint StringRef;

enum { kBadStringRef = 0 };

void initStringPool();

void str_retain(StringRef);
void str_release(StringRef);
void str_autorelease(StringRef);
/** Returns 0 if impossible to allocate a new string. */
StringRef str_createWithCString(const char * c_string);
StringRef str_createWithStringRef(StringRef ref);
const char * str_getCString(StringRef);

#endif 
