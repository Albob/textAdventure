/*
*
* Copyright Alexis Bauchu 2014
*
*
*/

#include <albob/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void debug(StringRef ref)
{
    printf("<DEBUG>Ref: %u, Content: \"%s\"\n", ref, strCStr(ref));
}

int main(int arg_number, char * arguments[])
{
    puts("Welcome, to ADVENTURE GAME!!");
    int must_exit = 0;
    char * line = NULL;

    do
    {
        if (line != NULL) {
            free(line);
            line = NULL;
        }

        line = readline("> ");

        if (line == NULL) {
            continue;
        }
        
        if (strlen(line) > 0) {
            add_history(line);
        }

        if (strcmp(line, "exit") == 0) {
            must_exit = 1;
        }
    } while (must_exit == 0);

    // exit
    puts("See you next time!!");
    return 0;
}

