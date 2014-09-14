/*
*
* Copyright Alexis Bauchu 2014
*
*
*/

#include <albob/string.h>
#include <ctype.h>
#include <stdio.h>
#include <termios.h>

void debug(StringRef ref)
{
    printf("<DEBUG>Ref: %u, Content: \"%s\"\n", ref, strCStr(ref));
}


void ttyCanonOff(void)
{
    tcgetattr(fileno(stdin), &t); //get the current terminal I/O structure
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(fileno(stdin), TSCANOW, &t); //Apply the new settings
}

void ttyCanonOn(void)
{
    tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TSCANOW, &t); //Apply the new settings
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
            else if (c == '\n') {
                putchar('\n');
            }
            else {
                putchar('x');
            }
        } while (c != '\n');
    } while (must_exit == 0);

    // exit
    puts("See you next time!!");
    return 0;
}

