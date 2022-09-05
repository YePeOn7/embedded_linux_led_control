#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "led.h"


#define LOG                 1       // still not used
#define MAX_PRIORITY        10
#define LEN_LED_COMMANDS    sizeof(LED_commands)/sizeof(ledCommand_t)
#define LED_PATH_PREFIX     "/sys/class/leds"
//#define LED_PATH_PREFIX     "."
#define RED_LED_PATH        LED_PATH_PREFIX"/led_r"
#define GREEN_LED_PATH      LED_PATH_PREFIX"/led_g"
#define BLUE_LED_PATH       LED_PATH_PREFIX"/led_b"

/********** Declare the LED commands here **************/
ledCommand_t LED_commands[] = {{"c1", LED_WHITE, LED_STATIC, 1, 0},
                                {"c2", LED_BLUE, LED_BLINKING_FAST, 2, 0},
                                {"c3", LED_YELLOW, LED_BLINKING_SLOW, 3, 0},
                                {"c4", LED_YELLOW, LED_BLINKING_SLOW, 4, 5},
                                {"c5", LED_YELLOW, LED_BLINKING_SLOW, 4, 5},
                                {"c6", LED_YELLOW, LED_BLINKING_SLOW, 5, 0},
                                {"c7", LED_YELLOW, LED_BLINKING_SLOW, 5, 0},
                                {"c8", LED_YELLOW, LED_BLINKING_SLOW, 6, 0},
                                {"c9", LED_YELLOW, LED_BLINKING_SLOW, 7, 0},
                                {"c10", LED_YELLOW, LED_BLINKING_SLOW, 9, 0}};

ledCommand_t* LED_commandStack[MAX_PRIORITY] = {NULL};
time_t LED_commandStartTime[MAX_PRIORITY] = {0};
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

void LED_setThreadStatusOn()
{
    threadStatus = 1;
}

void LED_addCommandToStack(char* command)
{
    for(int i = 0; i < LEN_LED_COMMANDS; i++)
    {
        printf("Checking --> %s\n", LED_commands[i].command);
        if(!strcmp(command, LED_commands[i].command))
        {
            printf("updating stack: %s ---- priority: %d\n", LED_commands[i].command, LED_commands[i].priority);            
            LED_commandStack[LED_commands[i].priority] = &LED_commands[i];
            break;
        }
    }
}

void LED_clearCommandStackByPriority(int priority)
{
    LED_commandStack[priority] = NULL;
}

int LED_clearCommandFromStack(char* command)
{
    int found = 0;
    for(int i = 0; i < LEN_LED_COMMANDS; i++)
    {
        printf("Checking --> %s\n", LED_commands[i].command);
        if(!strcmp(command, LED_commands[i].command))
        {
            printf("Clearing stack: %s ---- priority: %d\n", LED_commands[i].command, LED_commands[i].priority);            
            LED_clearCommandStackByPriority(LED_commands[i].priority);
            found = 1;
            break;
        }
    }

    if(!found) return -1; // the command is not found in the stack
    return 0;
}



void *LED_threadLoop(void *args)
{
    // int counter = 0;
    // int LED_currentRunningPriority = 0;
    printf("starting thread...\n");
    while(1)
    {
        // get the highest priority command to be executed
        // for(int i = 0; i < MAX_PRIORITY; i++)
        // {
        //     if(!strcmp())
        // }
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

void LED_setRedTriggerType(triggerType_t type)
{
    FILE *triggerFile;
    FILE *delayOnFile;
    FILE *delayOffFile;

    triggerFile = fopen(RED_LED_PATH"/trigger", "w");

    switch(type)
    {
        case LED_OFF:       
            fputs("none", triggerFile); 
            fclose(triggerFile);
            break;
        case LED_STATIC:    
            fputs("default-on", triggerFile); 
            fclose(triggerFile);
            break;
        case LED_BLINKING_FAST:
            fputs("timer", triggerFile);
            fclose(triggerFile);

            delayOnFile = fopen(RED_LED_PATH"/delay_on", "w");
            delayOffFile = fopen(RED_LED_PATH"/delay_off", "w");
            if(delayOnFile == NULL || delayOffFile == NULL) printf("led.c: delay file can't be opened\n");
            fputs("100", delayOffFile);
            fputs("100", delayOnFile);

            fclose(delayOffFile);
            fclose(delayOnFile);
            break;
        case LED_BLINKING_SLOW:
            fputs("timer", triggerFile);
            fclose(triggerFile);
            break;
        
        case LED_BLINKING_VERY_SLOW:
            fputs("timer", triggerFile);
            fclose(triggerFile);

            delayOnFile = fopen(RED_LED_PATH"/delay_on", "w");
            delayOffFile = fopen(RED_LED_PATH"/delay_off", "w");
            if(delayOnFile == NULL || delayOffFile == NULL) printf("led.c: delay file can't be opened\n");
            fputs("1000", delayOffFile);
            fputs("1000", delayOnFile);

            fclose(delayOffFile);
            fclose(delayOnFile);
            break;
    }
}

void LED_setGreenTriggerType(triggerType_t type)
{
    FILE *triggerFile;
    FILE *delayOnFile;
    FILE *delayOffFile;

    triggerFile = fopen(GREEN_LED_PATH"/trigger", "w");

    switch(type)
    {
        case LED_OFF:       
            fputs("none", triggerFile); 
            fclose(triggerFile);
            break;
        case LED_STATIC:    
            fputs("default-on", triggerFile); 
            fclose(triggerFile);
            break;
        case LED_BLINKING_FAST:
            fputs("timer", triggerFile);
            fclose(triggerFile);

            delayOnFile = fopen(GREEN_LED_PATH"/delay_on", "w");
            delayOffFile = fopen(GREEN_LED_PATH"/delay_off", "w");
            if(delayOnFile == NULL || delayOffFile == NULL) printf("led.c: delay file can't be opened\n");
            fputs("100", delayOffFile);
            fputs("100", delayOnFile);

            fclose(delayOffFile);
            fclose(delayOnFile);
            break;
        case LED_BLINKING_SLOW:
            fputs("timer", triggerFile);
            fclose(triggerFile);
            break;

        case LED_BLINKING_VERY_SLOW:
            fputs("timer", triggerFile);
            fclose(triggerFile);

            delayOnFile = fopen(GREEN_LED_PATH"/delay_on", "w");
            delayOffFile = fopen(GREEN_LED_PATH"/delay_off", "w");
            if(delayOnFile == NULL || delayOffFile == NULL) printf("led.c: delay file can't be opened\n");
            fputs("1000", delayOffFile);
            fputs("1000", delayOnFile);

            fclose(delayOffFile);
            fclose(delayOnFile);
            break;
    }
}

void LED_setBlueTriggerType(triggerType_t type)
{
    FILE *triggerFile;
    FILE *delayOnFile;
    FILE *delayOffFile;

    triggerFile = fopen(BLUE_LED_PATH"/trigger", "w");

    switch(type)
    {
        case LED_OFF:       
            fputs("none", triggerFile); 
            fclose(triggerFile);
            break;
        case LED_STATIC:    
            fputs("default-on", triggerFile); 
            fclose(triggerFile);
            break;
        case LED_BLINKING_FAST:
            fputs("timer", triggerFile);
            fclose(triggerFile);

            delayOnFile = fopen(BLUE_LED_PATH"/delay_on", "w");
            delayOffFile = fopen(BLUE_LED_PATH"/delay_off", "w");
            if(delayOnFile == NULL || delayOffFile == NULL) printf("led.c: delay file can't be opened\n");
            fputs("100", delayOffFile);
            fputs("100", delayOnFile);

            fclose(delayOffFile);
            fclose(delayOnFile);
            break;
        case LED_BLINKING_SLOW:
            fputs("timer", triggerFile);
            fclose(triggerFile);
            break;

        case LED_BLINKING_VERY_SLOW:
            fputs("timer", triggerFile);
            fclose(triggerFile);

            delayOnFile = fopen(BLUE_LED_PATH"/delay_on", "w");
            delayOffFile = fopen(BLUE_LED_PATH"/delay_off", "w");
            if(delayOnFile == NULL || delayOffFile == NULL) printf("led.c: delay file can't be opened\n");
            
            fputs("1000", delayOffFile);
            fputs("1000", delayOnFile);

            fclose(delayOffFile);
            fclose(delayOnFile);
            break;
    }
}

void LED_setTriggerType(ledColor_t color, triggerType_t type) // can be used to represent any color on ledColor_t
{
    switch(color)
    {
        case LED_RED:
            LED_setRedTriggerType(type);
            LED_setGreenTriggerType(LED_OFF);
            LED_setBlueTriggerType(LED_OFF);
            break;

        case LED_GREEN:
            LED_setRedTriggerType(LED_OFF);
            LED_setGreenTriggerType(type);
            LED_setBlueTriggerType(LED_OFF);
            break;

        case LED_BLUE:
            LED_setRedTriggerType(LED_OFF);
            LED_setGreenTriggerType(LED_OFF);
            LED_setBlueTriggerType(type);
            break;

        case LED_CYAN:
            LED_setRedTriggerType(LED_OFF);
            LED_setGreenTriggerType(type);
            LED_setBlueTriggerType(type);
            break;

        case LED_PURPLE:
            LED_setRedTriggerType(type);
            LED_setGreenTriggerType(LED_OFF);
            LED_setBlueTriggerType(type);
            break;

        case LED_YELLOW:
            LED_setRedTriggerType(type);
            LED_setGreenTriggerType(type);
            LED_setBlueTriggerType(LED_OFF);
            break;

        case LED_WHITE:
            LED_setRedTriggerType(type);
            LED_setGreenTriggerType(type);
            LED_setBlueTriggerType(type);
            break;
    }
}

void LED_setCommand(char* command)
{
    // pthread_t LED_threadHandle;
    if(!LED_isThreadStatusOn()) 
    {
        printf("creating a thread...\n");
        // LED_createThread();
        LED_setThreadStatusOn();
    }

    LED_addCommandToStack(command);

    for(int i = 0; i < MAX_PRIORITY; i++)
    {
        if(LED_commandStack[i] != NULL) printf("%d - %s\n", i, LED_commandStack[i]->command);
        else printf("%d - empty\n", i);
    }
}

void LED_clearCommand(char* command)
{
    LED_clearCommandFromStack(command);

    for(int i = 0; i < MAX_PRIORITY; i++)
    {
        if(LED_commandStack[i] != NULL) printf("%d - %s\n", i, LED_commandStack[i]->command);
        else printf("%d - empty\n", i);
    }
}