/*
*
* Copyright Alexis Bauchu 2014
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

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

typedef void (*command_func_t)(void);

typedef struct {
    char * name;
    command_func_t callback;
    char * description;
} command_t ;

#define COM_HELP     "help"
#define COM_TAKE     "take"
#define COM_GREET    "greet"
#define COM_EXIT     "exit"

static int g_must_exit = 0;

void cmd_help();
void cmd_take();
void cmd_greet();
void cmd_exit();

command_t command_list[] = {
    { COM_HELP, cmd_help, "Displays this help" },
    { COM_TAKE, cmd_take, "Take <something>. Puts an object in your inventory" },
    { COM_GREET, cmd_greet, "Say hello of course!" },
    { COM_EXIT, cmd_exit, "Quits the game" },
    { NULL, NULL, NULL }
};

void cmd_help()
{
    say("Here are the commands you can type and their expected results:");
    for (int i = 0; ; ++i)
    {
        command_t cmd = command_list[i];
        
        if (cmd.name == NULL) {
            break;
        }

        printf("- \"%s\": %s\n", cmd.name, cmd.description);
    }
}

void cmd_take()
{
    say("There's nothing to take");
}

void cmd_greet()
{
    say("Hello!");
}

void cmd_exit()
{
    g_must_exit = 1;
}

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
        name = command_list[index++].name;

        if (name && strncmp(name, text, length) == 0) {
            return copy_string(name);
        }
    } while (name != NULL);

    return NULL;
}

void process_command(const char * line)
{
    if (line == NULL) return;

    int length = strlen(line);
    char * name = (char*)malloc(sizeof(char) * length + 1);
    memset(name, '\0', length + 1);

    // Isolate the first word
    for (int i = 0, index = 0; i < length + 1; ++i)
    {
        if (line[i] == ' ' && index > 0)
        {
            break;
        }
        else if (line[i] != ' ')
        {
            name[index] = line[i];
            ++index;
        }
    }

    // Find the corresponding command
    command_t cmd;

    for (int i = 0; ; ++i)
    {
        cmd = command_list[i];
        if (cmd.name == NULL) break;

        if (strcmp(cmd.name, name) == 0)
        {
            cmd.callback();
            break;
        }
    }

    if (cmd.name == NULL) {
        say("I don't understand...");
    }
}

int main(int arg_number, char * arguments[])
{
    // Initializing the Readline library
    rl_completion_entry_function = custom_completer;

    // Game loop
    puts("Welcome, to ADVENTURE GAME!!\n(Type the action you want to do, or \"help\" to list the commands).");
    char * line = NULL;

    do
    {
        if (line != NULL) {
            free(line);
            line = NULL;
        }

        line = readline("\n> ");

        if (line == NULL) {
            continue;
        }
        
        if (strlen(line) > 0) {
            add_history(line);
        }

        process_command(line);
    } while (g_must_exit == 0);

    // exit
    puts("See you next time!!");
    return 0;
}

