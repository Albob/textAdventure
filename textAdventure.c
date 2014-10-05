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

#define COM_HELP "help"
#define COM_EXIT "exit"

char * COMMANDS[] = {
    COM_HELP,
    COM_EXIT,
    NULL
};

void debug(StringRef ref)
{
    printf("<DEBUG>Ref: %u, Content: \"%s\"\n", ref, strCStr(ref));
}

void say(const char * message)
{
    printf("%s\n", message);
}

char * copy_string(const char * str)
{
    if (str == NULL) return NULL;

    size_t length = strlen(str);
    char * new_str = (char*)malloc(sizeof(char) * length + 1);
    strcpy(new_str, str);

    return new_str;
}

#define dump_string(x) printf(#x ": %s\n", x);
#define dump_int(x) printf(#x ": %d\n", x);

char * custom_completer(const char * text, int state)
{
    static int index, length;

    if (!text) return NULL;

    if (state == 0)
    {
        index = 0;
        length = strlen(text);
    }

    char * name = NULL;
    do {
        name = COMMANDS[index++];

        if (name && strncmp(name, text, length) == 0) {
            return copy_string(name);
        }
    } while (name != NULL);

    return NULL;
}

int main(int arg_number, char * arguments[])
{
    // Initializing the Readline library
    rl_completion_entry_function = custom_completer;

    // Game loop
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

