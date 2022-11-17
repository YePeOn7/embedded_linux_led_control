#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "led.h"

void help()
{
    printf("Usage:");
    printf("led-set-command [option]\n");
    printf("---- Option -----\n");
    
    for(int i = 0; i < LED_getLenCommands(); i++) printf("%s\n", LED_commands[i].command);
}

int main(int argc, char** argv)
{   
    if(argc != 2) help();
    else
    {
        char foundMatch = 0;
        for(int i = 0; i < LED_getLenCommands(); i++)
        {
            if(!strcmp(argv[1], LED_commands[i].command))
            {
                foundMatch = 1;
                char command[100];
                sprintf(command, "led-set-command %s", LED_commands[i].command);
                system("ls");
                break;
            }   
        }
        if(!foundMatch) 
        {
            printf("invalid option....\n");
            help();
        }
    }
    return 0;
}