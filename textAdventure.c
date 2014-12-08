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

#include "utils.h"

void cmd_help(const char * line);
void cmd_take(const char * line);
void cmd_list(const char * line);
void cmd_look(const char * line);
void cmd_exit(const char * line);

struct item_t;
static struct item_t * g_inventory_first_item;

/// }}}
/// {{{ Game types 

typedef void (*command_func_t)(const char * line);

typedef struct command_t {
    char * name;
    char * description;
    command_func_t callback;
} command_t;

typedef struct item_t {
    char* id;
    char* name;
    char* inventory_desc;
    char* scene_desc;
    struct item_t * previousInScene;
    struct item_t * nextInScene;
    struct item_t * previousInInventory;
    struct item_t * nextInInventory;
} item_t;

void item_init(item_t * i)
{
    i->id = "";
    i->name = "";
    i->inventory_desc = "";
    i->scene_desc = "";
    i->previousInScene = NULL;
    i->nextInScene = NULL;
    i->previousInInventory = NULL;
    i->nextInInventory = NULL;
}

typedef struct portal_t {
    char * sceneId;
    char * description;
    struct portal_t * nextInScene;
    struct portal_t * previousInScene;
} portal_t;

typedef struct scene_t {
    char* id;
    char* description;
    item_t * firstItem;
    portal_t * firstPortal;
} scene_t;

void scene_init(scene_t * s, char* id, char* description)
{
    if (s == NULL) return;
    s->id = id;
    s->description = description;
    s->firstItem = NULL;
    s->firstPortal = NULL;
}

void scene_addItem(scene_t * scene, item_t * item)
{
    if (scene == NULL || item == NULL) return;
    
    if (scene->firstItem == NULL) {
        scene->firstItem = item;
    }
    else
    {
        item_t * last_item = scene->firstItem;
        while (last_item->nextInScene != NULL) {
            last_item = last_item->nextInScene;
        }
        last_item->nextInScene = item;
        item->previousInScene = last_item;
    }

    item->nextInScene = NULL;
}

void scene_removeItem(scene_t * scene, item_t * item)
{
    if (scene == NULL || item == NULL) return;

    item_t * previous = item->previousInScene;
    item_t * next = item->nextInScene;

    if (previous != NULL) {
        previous->nextInScene = next; 
    }

    if (next != NULL) {
        next->previousInScene = previous; 
    }

    if (item == scene->firstItem) {
        scene->firstItem = next;
    }

    item->nextInScene = NULL;
    item->previousInScene = NULL;
}

void scene_addPortal(scene_t * scene, portal_t * portal)
{
    if (scene->firstPortal == NULL)
    {
        scene->firstPortal = portal;
    }
    else
    {
        portal_t * last_portal = scene->firstPortal;
        // TODO
    }

    portal->nextInScene = NULL;
}

void inventory_addItem(item_t * item)
{
    if (item == NULL) return;

    if (g_inventory_first_item == NULL) {
        g_inventory_first_item = item;
    }
    else
    {
        item_t * last_item = g_inventory_first_item;
        while (last_item->nextInInventory != NULL) {
            last_item = last_item->nextInInventory;
        }
        last_item->nextInInventory = item;
        item->previousInInventory = last_item;
    }

    printf("You stuff the %s in your bag\n", item->name);
    item->nextInInventory = NULL;
}

void portal_init(portal_t * portal)
{
    portal->sceneId = NULL;
    portal->description = NULL;
    portal->nextInScene = NULL;
    portal->previousInScene = NULL;
}

// TODO: void releaseScene(scene_t * s);

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
static scene_t g_current_scene;
static scene_t g_first_scene;
static item_t * g_inventory_first_item;

/// }}}
/// {{{ Command handlers 

void cmd_help(const char * line)
{
    puts("Here are the commands you can type and their expected results:");
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
    const char * warning = "You must take something!";

    // Find the position of the name of the object in the command
    char * start = strstr(line, COM_TAKE);
    int take_len = strlen(COM_TAKE);
    int offset = strspn(start + take_len, " ");

    if (offset == 0)
    {
        SAY(warning);
        return;
    }

    char * object = start + take_len + offset;

    if (strlen(object) ==0)
    {
        SAY(warning);
        return;
    }

    item_t * item = g_current_scene.firstItem;

    while (item != NULL)
    {
        char * name = item->name;

        if (strncmp(name, object, strlen(name)) == 0) {
            break;
        }

        item = item->nextInScene;
    }

    if (item != NULL)
    {
        inventory_addItem(item);
        scene_removeItem(&g_current_scene, item);
    }
    else
    {
        SAY("There's nothing of that name here...\n");
    }
}

void cmd_list(const char * line)
{
    const item_t * item = g_inventory_first_item;

    if (item == NULL)
    {
        SAY("Your inventory is empty.");
    }
    else
    {
        SAY("In your bag you have:");
        while (item != NULL)
        {
            printf("- %s\n", item->name);
            item = item->nextInInventory;
        }
    }
}

void cmd_look(const char * line)
{
    say(g_current_scene.description, 1);
    item_t * item = g_current_scene.firstItem;

    while (item != NULL)
    {
        SAY(item->scene_desc);
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
        item = g_current_scene.firstItem;
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

    int first_char = strspn(rl_line_buffer, " \t");

    if (start == first_char) {
        matches = rl_completion_matches(text, command_generator);
    }
    else
    {
        char * cmd = string_copy(rl_line_buffer);
        char * first = strtok(cmd, " \t");
        if (first != NULL && strcmp(first, COM_TAKE) == 0) {
            matches = rl_completion_matches(text, item_generator);
        }
        free(cmd);
    }

    return matches;
}

void process_command(const char * p_line)
{
    if (p_line == NULL) return;

    char * line = string_copy(p_line);
    char * name = strtok(line, " \t");

    // Find the corresponding command
    command_t cmd;

    for (int i = 0; ; ++i)
    {
        cmd = g_command_list[i];
        if (cmd.name == NULL) break;

        if (strcmp(cmd.name, name) == 0)
        {
            cmd.callback(p_line);
            break;
        }
    }

    if (cmd.name == NULL) {
        say("I don't understand...", 1);
    }

    free(line);
}

/// }}}
/// {{{ Main 

int main(int arg_number, char * arguments[])
{
    // Initializing the Readline library
    rl_attempted_completion_function = custom_completer;

    // Init the player
    g_inventory_first_item = NULL;

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

    item_t saucisson;
    item_init(&saucisson);
    saucisson.id = "item_saucisson";
    saucisson.name = "saussice seche";
    saucisson.inventory_desc = "It smells like lemon. Hummm, lemoooon!";
    saucisson.scene_desc = "There's a delicious *saussice seche* in the cupboard.";
    scene_addItem(&g_current_scene, &saucisson);

    item_t magnet;
    item_init(&magnet);
    magnet.id = "item_magnet";
    magnet.name = "magnet";
    magnet.inventory_desc = "Its shaped like a strawberry.";
    magnet.scene_desc = "There's a *magnet* on the fridge door.";
    scene_addItem(&g_current_scene, &magnet);

    item_t cigarettes;
    item_init(&cigarettes);
    cigarettes.id = "item_cigarettes";
    cigarettes.name = "cigarettes";
    cigarettes.inventory_desc = "I really should quit...";
    cigarettes.scene_desc = "";
    inventory_addItem(&cigarettes);

    item_t keys;
    item_init(&keys);
    keys.id = "item_keys";
    keys.name = "keys";
    keys.inventory_desc = "Theses are the keys to my car";
    keys.scene_desc = "";
    inventory_addItem(&keys);

    // Game loop
    printf("\033[2J\033[1;1H");  // "Home"s the text cursor, ie: reset the terminal so the first character is in the top-left corner
    SAY("Welcome, to ADVENTURE GAME!!");
    SAY("");
    cmd_look(NULL);
    SAY("");
    SAY("(Type in the action you want to do, or type \"help\" to list the commands. You can also press the 'tab' key to complete words).");
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
            process_command(line);
        }
        else {
            SAY("Come on, don't be shy!");
        }

    } while (g_must_exit == 0);

    // exit
    puts("See you next time!!");
    return 0;
}

/// }}}

