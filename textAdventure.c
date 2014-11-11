/*
*
* Copyright Alexis Bauchu 2014
*
*
*/

/// {{{ Includes and forward declarations 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void cmd_help(const char * line);
void cmd_take(const char * line);
void cmd_list(const char * line);
void cmd_look(const char * line);
void cmd_exit(const char * line);

#define MAX_INVENTORY 32
#define MAX_ITEMS     8

/// }}}
/// {{{ Utils 
void say(const char * message)
{
    printf("%s\n", message);
}

char * string_copy(const char * str)
{
    if (str == NULL) return NULL;

    size_t length = strlen(str);
    char * new_str = (char*)malloc(sizeof(char) * length + 1);
    strcpy(new_str, str);

    return new_str;
}

char * string_first_word(const char * input)
{
    if (input == NULL) return NULL;
    int start = 0;
    while (input[start] == ' ' || input[start] == '\t') start++;
    if (input[start] == '\0') return NULL;
    int end = start + 1;
    while (input[end] != ' ' && input[end] != '\t' && input[end] != EOF) end++;

    int length = end - start;
    char * result = (char*)malloc(sizeof(char) * (length + 1));
    memcpy(result, input + start, end - start);
    result[length] = '\0';

    return result;
}

#define dump_string(x) printf(#x ": %s\n", x);
#define dump_int(x) printf(#x ": %d\n", x);

/// }}} Utils
/// {{{ Game types 

typedef void (*command_func_t)(const char * line);

typedef struct {
    char * name;
    char * description;
    command_func_t callback;
} command_t ;

typedef struct item_t {
    char* id;
    char* name;
    char* inventory_desc;
    char* scene_desc;
    struct item_t * nextInScene;
} item_t;

void item_init(item_t * i)
{
    i->id = "";
    i->name = "";
    i->inventory_desc = "";
    i->scene_desc = "";
}

typedef struct {
    char* id;
    char* description;
    item_t * first_item;
} scene_t;

void scene_init(scene_t * s, char* id, char* description)
{
    if (s == NULL) return;
    s->id = id;
    s->description = description;
    s->first_item = NULL;
}

void scene_addItem(scene_t * scene, item_t * item)
{
    if (scene == NULL || item == NULL) return;
    
    if (scene->first_item == NULL) {
        scene->first_item = item;
    }
    else
    {
        item_t * last_item = scene->first_item;
        while (last_item->nextInScene != NULL) {
            last_item = last_item->nextInScene;
        }
        last_item->nextInScene = item;
    }

    item->nextInScene = NULL;
}

void scene_removeItem(scene_t * scene, item_t * item)
{
    if (scene == NULL || item == NULL) return;

}

// TODO: void releaseScene(scene_t * s);

typedef struct {
    const char* inventory[MAX_INVENTORY];
} player_t;

/// }}} Game types
/// {{{ Globals 

#define COM_HELP     "help"
#define COM_TAKE     "take"
#define COM_LIST     "list"
#define COM_LOOK     "look"
#define COM_EXIT     "exit"

command_t g_command_list[] = {
    { COM_HELP, "Displays this help.", cmd_help },
    { COM_TAKE, "Takes <something> and puts it in your inventory.", cmd_take },
    { COM_LIST, "Lists the content of your inventory.", cmd_list },
    { COM_LOOK, "Looks around you.", cmd_look },
    { COM_EXIT, "Quits the game.", cmd_exit },
    { NULL, NULL, NULL }
};
static int g_must_exit = 0;
static player_t g_player;
static scene_t g_current_scene;
static scene_t g_first_scene;

/// }}}
/// {{{ Command handlers 

void cmd_help(const char * line)
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

void cmd_take(const char * line)
{
    char * start = strstr(line, COM_TAKE);
    int take_len = strlen(COM_TAKE);
    int offset = strspn(start + take_len, " ");

    const char * warning = "You must take something!";

    if (offset ==0)
    {
        say(warning);
        return;
    }

    char * object = start + take_len + offset;

    if (strlen(object) ==0)
    {
        say(warning);
        return;
    }

    printf("$ The object you want is: %s\n", object);
}

void cmd_list(const char * line)
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

void cmd_look(const char * line)
{
    say(g_current_scene.description);
    item_t * item = g_current_scene.first_item;
    while (item != NULL)
    {
        say(item->scene_desc);
        item = item->nextInScene;
    }
}

void cmd_exit(const char * line)
{
    g_must_exit = 1;
}

/// }}}
/// {{{ Command parsing 

char * command_generator(const char * text, int state)
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
            return string_copy(name);
        }
    } while (name != NULL);

    return NULL;
}

char * item_generator(const char * text, int state)
{
    static item_t * item;
    static int length;

    if (!text) return NULL;

    if (state == 0)
    {
        item = g_current_scene.first_item;
        length = strlen(text);
    }

    while (item != NULL)
    {
        char * name = item->name;
        item = item->nextInScene;

        if (strncmp(name, text, length) == 0) {
            return string_copy(name);
        }
    }

    return NULL;
}

char ** custom_completer(const char * text, int start, int end)
{
    rl_attempted_completion_over = 1; // prevent readline from providing default completion

    char ** matches = NULL;

    int first_char = 0;
    while (rl_line_buffer[first_char] == ' ') { first_char++; }

    if (start == 0 || start == first_char) {
        matches = rl_completion_matches(text, command_generator);
    }
    else
    {
        char * cmd = string_first_word(rl_line_buffer);
        if (0 == strncmp(cmd, COM_TAKE, 20)) {
            matches = rl_completion_matches(text, item_generator);
        }
        free(cmd);
    }

    return matches;
}

void process_command(const char * line)
{
    if (line == NULL) return;

    char * name = string_first_word(line);

    // Find the corresponding command
    command_t cmd;

    for (int i = 0; ; ++i)
    {
        cmd = g_command_list[i];
        if (cmd.name == NULL) break;

        if (strcmp(cmd.name, name) == 0)
        {
            cmd.callback(line);
            break;
        }
    }

    if (cmd.name == NULL) {
        say("I don't understand...");
    }

    free(name);
}

/// }}}
/// {{{ Main 

int main(int arg_number, char * arguments[])
{
    // Initializing the Readline library
    rl_attempted_completion_function = custom_completer;

    // Init the player
    memset(g_player.inventory, 0, MAX_INVENTORY);

    // Init the first scene
    scene_init(&g_first_scene, "sc_first", "You see that you are in kitchen. The place looks old and abandonned. The only light is a flickering neon tube above the sink.");
    g_current_scene = g_first_scene;

    item_t knife;
    item_init(&knife);
    knife.id = "item_knife";
    knife.name = "knife";
    knife.inventory_desc = "This is a sharp meat knife.";
    knife.scene_desc = "There's a *knife* on the table.";
    scene_addItem(&g_current_scene, &knife);

    item_t soap;
    item_init(&soap);
    soap.id = "item_soap";
    soap.name = "liquid soap";
    soap.inventory_desc = "It smells like lemon. Hummm, lemoooon!";
    soap.scene_desc = "There's *liquid soap* next to the sink.";
    scene_addItem(&g_current_scene, &soap);

    // Game loop
    say("Welcome, to ADVENTURE GAME!!\n");
    cmd_look(NULL);
    say("\nType the action you want to do, or \"help\" to list the commands).");
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

/// }}}

