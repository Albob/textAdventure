/*
 * Text Adventure, Copyright Alexis Bauchu 2014
 */

#include <stdio.h>

void say(const char * message, int insert_newline);
char * string_copy(const char * str);

#define SAY(x) say((x), 1)
#define dump_string(x) printf(#x "= '%s'\n", x);
#define dump_int(x) printf(#x "= %d\n", x);
#define dump_float(x) printf(#x "= %.2f\n", x);

