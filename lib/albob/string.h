/*
* string.h
* Copyright Alexis Bauchu 2014
* 
* Define a string type and function to manipulate them.
*/

#ifndef libalbob_string_h
#define libalbob_string_h

typedef unsigned int uint;
typedef uint StringRef;

enum { kBadStringRef = 0 };

void initStringPool();

void strRetain(StringRef);
void strRelease(StringRef);
void strAutorelease(StringRef);
/** Returns 0 if impossible to allocate a new string. */
StringRef strMake(const char * c_string);
StringRef strCopy(StringRef ref);
const char * strCStr(StringRef);

#endif 
