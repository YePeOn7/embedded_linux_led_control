#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "led.h"

#define LED_TEST    LED_WHITE

int main(int argc, char** argv)
{
    int command;
    while(1)
    {
        printf("\n---- option ------\n");
        printf("1: off\n");
        printf("2: static\n");
        printf("3: blinking slow\n");
        printf("4: blinking very slow\n");
        printf("5: blinking fast\n");
                
        printf("Command: ");
        scanf("%d", &command);
        switch(command)
        {
            case 1: LED_setTriggerType(LED_TEST, LED_OFF);break;
            case 2: LED_setTriggerType(LED_TEST, LED_STATIC);break;
            case 3: LED_setTriggerType(LED_TEST, LED_BLINKING_SLOW);break;
            case 4: LED_setTriggerType(LED_TEST, LED_BLINKING_VERY_SLOW);break;
            case 5: LED_setTriggerType(LED_TEST, LED_BLINKING_FAST);break;
        }
    }

    return 0;
}