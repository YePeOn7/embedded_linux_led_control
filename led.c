#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "led.h"

#define MAX_PRIORITY        10
#define LEN_LED_COMMANDS    sizeof(LED_commands)/sizeof(ledCommand_t)
// #define LED_PATH_PREFIX     "/sys/class/leds"
#define LED_PATH_PREFIX     "."
#define R_LED_PATH          LED_PATH_PREFIX"/led_r"
#define G_LED_PATH          LED_PATH_PREFIX"/led_g"
#define B_LED_PATH          LED_PATH_PREFIX"/led_b"

/********** Declare the LED commands here **************/
ledCommand_t LED_commands[] = {{"c1", LED_WHITE, LED_STATIC, 1},
                                {"c2", LED_BLUE, LED_BLINKING_FAST, 2},
                                {"c3", LED_YELLOW, LED_BLINKING_SLOW, 3},
                                {"c4", LED_YELLOW, LED_BLINKING_SLOW, 4},
                                {"c5", LED_YELLOW, LED_BLINKING_SLOW, 4},
                                {"c6", LED_YELLOW, LED_BLINKING_SLOW, 5},
                                {"c7", LED_YELLOW, LED_BLINKING_SLOW, 5},
                                {"c8", LED_YELLOW, LED_BLINKING_SLOW, 6},
                                {"c9", LED_YELLOW, LED_BLINKING_SLOW, 7},
                                {"c10", LED_YELLOW, LED_BLINKING_SLOW, 9}};

char LED_commadStack[MAX_PRIORITY][50];
int threadStatus = 0;

void test()
{
    printf("Test\n");
}

void delayMs(int ms)
{
    usleep(ms*1000);
}

int LED_isThreadStatusOn()
{
    return threadStatus;
}

void LED_setTheadStatusOn()
{
    threadStatus = 1;
}

void LED_updateStack(char* command)
{
    printf("Updating command stack...\n");
    for(int i = 0; i < LEN_LED_COMMANDS; i++)
    {
        printf("Checking --> %s\n", LED_commands[i].command);
        if(!strcmp(command, LED_commands[i].command))
        {
            printf("updating stack: %s ---- priority: %d\n", LED_commands[i].command, LED_commands[i].priority);
            sprintf(LED_commadStack[LED_commands[i].priority], "%s", LED_commands[i].command);
            break;
        }
    }
}

void *LED_threadLoop(void *args)
{
    // int counter = 0;
    printf("starting thread...\n");
    while(1)
    {
        // printf("counter -> %d\n", counter++);
        // if (counter > 5) break;
        delayMs(500);
    }

    return NULL;
}

pthread_t LED_createThread()
{  
    pthread_t ledThreadHandle;

    pthread_create(&ledThreadHandle, NULL, LED_threadLoop, NULL);
    return ledThreadHandle;
}

void LED_setRType(indicatorType_t type)
{
    FILE *triggerFile;
    FILE *delayOnFile;
    FILE *delayOffFile;

    triggerFile = fopen(R_LED_PATH"/trigger", "w");

    switch(type)
    {
        case LED_OFF:       
            fputs("none", triggerFile); 
            break;
        case LED_STATIC:    
            fputs("default-on", triggerFile); 
            break;
        case LED_BLINKING_FAST:
            fputs("timer", triggerFile);
            
            delayOnFile = fopen(R_LED_PATH"/delay_on", "w");
            delayOffFile = fopen(R_LED_PATH"/delay_off", "w");
            fputs("100", delayOffFile);
            fputs("100", delayOnFile);

            fclose(delayOffFile);
            fclose(delayOnFile);
            break;
        case LED_BLINKING_SLOW:
            fputs("timer", triggerFile);
            break;
        
    }

    fclose(triggerFile);
}

void LED_setGType(indicatorType_t type)
{

}

void LED_setBType(indicatorType_t type)
{

}

void LED_setMode(ledColor_t color, indicatorType_t type)
{

}

void LED_setCommand(char* command)
{
    // pthread_t LED_threadHandle;
    if(!LED_isThreadStatusOn()) 
    {
        printf("creating a thread...\n");
        LED_createThread();
        LED_setTheadStatusOn();
    }

    LED_updateStack(command);

    for(int i = 0; i < MAX_PRIORITY; i++)
    {
        printf("%d - %s\n", i, LED_commadStack[i]);
    }
}