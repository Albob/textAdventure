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

#define MAX_INVENTORY 32
#define MAX_ITEMS     8

// Game types
typedef void (*command_func_t)(void);

typedef struct {
    char * name;
    command_func_t callback;
    char * description;
} command_t ;

typedef struct {
    char* id;
    char* name;
    char* inventory_desc;
    char* scene_desc;
} item_t;

typedef struct {
    char* id;
    char* description;
    item_t *item_list[MAX_ITEMS];
} scene_t;

void initScene(scene_t * s, char* id, char* description)
{
    if (s == NULL) return;
    s->id = id;
    s->description = description;
    memset(s->item_list, 0, sizeof(item_t*) * MAX_ITEMS);
}

// TODO: void releaseScene(scene_t * s);

typedef struct {
    const char* inventory[MAX_INVENTORY];
} player_t;

#define COM_HELP     "help"
#define COM_TAKE     "take"
#define COM_LIST     "list"
#define COM_LOOK     "look"
#define COM_EXIT     "exit"

void cmd_help();
void cmd_take();
void cmd_list();
void cmd_look();
void cmd_exit();

// Globals
command_t g_command_list[] = {
    { COM_HELP, cmd_help, "Displays this help." },
    { COM_TAKE, cmd_take, "Takes <something> and puts it in your inventory." },
    { COM_LIST, cmd_list, "Lists the content of your inventory." },
    { COM_LOOK, cmd_look, "Looks around you." },
    { COM_EXIT, cmd_exit, "Quits the game." },
    { NULL, NULL, NULL }
};
static int g_must_exit = 0;
static player_t g_player;
static scene_t g_current_scene;
static scene_t g_first_scene;

// Command handlers
void cmd_help()
{
    say("Here are the commands you can type and their expected results:");
    for (int i = 0; ; ++i)
    {
        command_t cmd = g_command_list[i];
        
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

void cmd_list()
{
    const char * item = g_player.inventory[0];

    if (item == NULL)
    {
        say("Your inventory is empty.");
    }
    else
    {
        say("In your bag you have:");
        for (int i = 0; ; ++i)
        {
            item = g_player.inventory[i];
            if (item == NULL) break;
            printf("%d) %s\n", i, item);
        }
    }
}

void cmd_look()
{
    say(g_current_scene.description);
}

void cmd_exit()
{
    g_must_exit = 1;
}

// Command parsing
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
        name = g_command_list[index++].name;

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
    memset(name, '\0', sizeof(char) * length + 1);

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
        cmd = g_command_list[i];
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

// Main
int main(int arg_number, char * arguments[])
{
    // Initializing the Readline library
    rl_completion_entry_function = custom_completer;

    // Init the player
    memset(g_player.inventory, 0, MAX_INVENTORY);

    // Init the first scene
    g_first_scene.id = "sc_first";
    g_first_scene.description = "You see that you are in kitchen. The place looks old and abandonned. The only light is a flickering neon tube above the sink.";
    g_current_scene = g_first_scene;

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

