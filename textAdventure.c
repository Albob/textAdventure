/*
*
* Copyright Alexis Bauchu 2014
*
*
*/

#include <albob/string.h>
#include <ctype.h>
#include <stdio.h>

void debug(StringRef ref)
{
    printf("<DEBUG>Ref: %u, Content: \"%s\"\n", ref, strCStr(ref));
}

int main(int arg_number, char * arguments[])
{
    puts("Welcome, to ADVENTURE GAME!!");
    int must_exit = 0;

    do
    {
        int c = 10;
        do
        {
            c = getchar();

            if (c == EOF)
            {
                must_exit = 1;
                break;
            }
            printf("You wrote '%c'\n", c);
        } while (c != '\n');
    } while (must_exit == 0);

    // exit
    puts("See you next time!!");
    return 0;
}

