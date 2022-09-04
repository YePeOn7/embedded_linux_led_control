#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "led.h"

int main(int argc, char** argv)
{
    int command;
    while(1)
    {
        printf("Command: ");
        scanf("%d", &command);
        switch(command)
        {
            case 1: LED_setRType(LED_OFF);break;
            case 2: LED_setRType(LED_STATIC);break;
            case 3: LED_setRType(LED_BLINKING_SLOW);break;
            case 4: LED_setRType(LED_BLINKING_FAST);break;
        }
    }

    return 0;
}