#include "termux_output.h"

void notif_print(char *text, char *title)
{
    char command[1000];
    sprintf(command, 
            "echo -e \"%s\" | "
            "termux-notification -t \"%s\" ",
            text,
            title);
    system(command);
}

void toast_print(char *text)
{
    system("termux-toast \"%s\"\n");
}