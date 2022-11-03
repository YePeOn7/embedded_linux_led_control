#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "led.h"

#define LED_LOG             1  
#define USE_THREAD          1

#define MAX_PRIORITY        10
#define LED_PATH_PREFIX     "/sys/class/leds"
#define LEN_LED_COMMANDS    sizeof(LED_commands)/sizeof(ledCommand_t)
// #define LED_PATH_PREFIX     "."
#define RED_LED_PATH        LED_PATH_PREFIX"/led_r"
#define GREEN_LED_PATH      LED_PATH_PREFIX"/led_g"
#define BLUE_LED_PATH       LED_PATH_PREFIX"/led_b"

/********** Declare the LED commands here **************/
ledCommand_t LED_commands[] = {{"off", LED_RED, LED_OFF, LED_ACTION_SET, 0, 0, 0},
                                {"on", LED_RED, LED_OFF, LED_ACTION_CLEAR, 0, 0, 0},
                                {"ota_start", LED_BLUE, LED_STATIC, LED_ACTION_SET_CLEAR, 7, 4, 0},
                                {"boot", LED_BLUE, LED_BLINKING_SLOW, LED_ACTION_SET, 9, 0, 0},
                                {"run", LED_GREEN, LED_STATIC, LED_ACTION_SET, 8, 0, 0},
                                {"event", LED_GREEN, LED_BLINKING_SLOW, LED_ACTION_SET, 6, 0, 5},
                                {"sd_fail", LED_RED, LED_STATIC, LED_ACTION_SET, 2, 0, 0},
                                {"network_fail", LED_RED, LED_BLINKING_SLOW, LED_ACTION_SET, 4, 0, 0},
                                {"ota_fail", LED_RED, LED_BLINKING_SLOW, LED_ACTION_SET, 4, 0, 0},
                                {"cloud_fail", LED_RED, LED_BLINKING_VERY_SLOW, LED_ACTION_SET, 6, 0, 0},
                                {"ota_success", LED_RED, LED_OFF, LED_ACTION_CLEAR, 0, 7, 0},
                                {"sd_formatted", LED_RED, LED_OFF, LED_ACTION_CLEAR, 0, 2, 0},
                                {"network_success", LED_RED, LED_OFF, LED_ACTION_CLEAR, 0, 4, 0},
                                {"cloud_success", LED_RED, LED_OFF, LED_ACTION_CLEAR, 0, 6, 0},
                                {"test_white_enable", LED_WHITE, LED_STATIC, LED_ACTION_SET, 1, 0, 0},
                                {"test_white_disable", LED_WHITE, LED_STATIC, LED_ACTION_CLEAR, 0, 1, 0}};

ledCommand_t* LED_priorityStack[MAX_PRIORITY] = {NULL};
time_t LED_commandStartTime[MAX_PRIORITY] = {0};
char* LED_currentRunningcommand = NULL;
int threadStatus = 0;

void logPrint(const char* fmt, ...)
{
    if(LED_LOG)
    {
        va_list argptr;
        va_start(argptr, fmt);
        vprintf(fmt, argptr);
        printf("\n");
        va_end(argptr);
    }
}

int LED_getLenCommands()
{
    return LEN_LED_COMMANDS;
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
        logPrint("Checking --> %s", LED_commands[i].command);
        if(!strcmp(command, LED_commands[i].command))
        {
            logPrint("updating priority stack: %d --> %s ", LED_commands[i].prioritySet, LED_commands[i].command);            
            LED_priorityStack[LED_commands[i].prioritySet] = &LED_commands[i];
            time(&LED_commands[i].startTime);
            break;
        }
    }
}

void LED_clearCommandStackByPriority(int priority)
{
    LED_priorityStack[priority] = NULL;
}

int LED_clearCommandFromStack(char* command)
{
    int found = 0;
    for(int i = 0; i < MAX_PRIORITY; i++)
    {
        logPrint("Checking --> %s", LED_commands[i].command);
        if(LED_priorityStack[i] != NULL && !strcmp(command, LED_priorityStack[i]->command))
        {
            logPrint("Clearing stack: %s ---- priority: %d", LED_priorityStack[i]->command, LED_priorityStack[i]->prioritySet);            
            LED_clearCommandStackByPriority(LED_priorityStack[i]->prioritySet);
            found = 1;
            break;
        }
    }

    if(!found) 
    {
        logPrint("\nCommand is not found in the priority Stack...\n");
        return -1; // the command is not found in the priority stack
    }
    return 0;
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
            if(delayOnFile == NULL || delayOffFile == NULL) logPrint("led.c: delay file can't be opened");
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
            if(delayOnFile == NULL || delayOffFile == NULL) logPrint("led.c: delay file can't be opened");
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
            if(delayOnFile == NULL || delayOffFile == NULL) logPrint("led.c: delay file can't be opened\n");
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
            if(delayOnFile == NULL || delayOffFile == NULL) logPrint("led.c: delay file can't be opened");
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
            if(delayOnFile == NULL || delayOffFile == NULL) logPrint("led.c: delay file can't be opened");
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
            if(delayOnFile == NULL || delayOffFile == NULL) logPrint("led.c: delay file can't be opened");
            
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

void* LED_check()
{
    time_t currentTime;
    
    time(&currentTime);
    for(int i = 0; i < MAX_PRIORITY; i++)
    {
        if(LED_priorityStack[i] != NULL)
        {
            // Check if Timeout
            if(LED_priorityStack[i]->holdTime != 0 && 
                currentTime - LED_priorityStack[i]->startTime >= LED_priorityStack[i]->holdTime)
            {
                logPrint("\nHold time timeout reached - Clearing stack on priority %d: %s", i, LED_priorityStack[i]->command);
                LED_clearCommandStackByPriority(i);

                for(int i = 0; i < MAX_PRIORITY; i++)
                {
                    if(LED_priorityStack[i] != NULL) logPrint("%d - %s, enterTime: %li", i, LED_priorityStack[i]->command, LED_priorityStack[i]->startTime);
                    else logPrint("%d - empty", i);
                }
                continue;
            }

            // Execute LED command if the highest priority different with current running command
            else if(LED_currentRunningcommand == NULL || strcmp(LED_currentRunningcommand, LED_priorityStack[i]->command))
            {
                logPrint("running command \"%s\", with priority %d", LED_priorityStack[i]->command, i);
                LED_currentRunningcommand = LED_priorityStack[i]->command;
                    
                LED_setTriggerType(LED_priorityStack[i]->color, LED_priorityStack[i]->type);  
            }

            break; 
        }

        else if(i == MAX_PRIORITY-1 && LED_currentRunningcommand != NULL) 
        {
            logPrint("Priority Stack is empty, turning off the LED...");
            LED_setTriggerType(LED_WHITE, LED_OFF);
            LED_currentRunningcommand = NULL;
        }
    }

    return NULL;
}

void *LED_threadLoop(void *args)
{
    logPrint("starting thread...");
    while(1)
    {
        LED_check();
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

void LED_setCommand(char* command)
{
    // pthread_t LED_threadHandle;
    if(!LED_isThreadStatusOn() && USE_THREAD) 
    {
        LED_createThread();
        LED_setThreadStatusOn();
    }
    
    for(int i = 0; i < LEN_LED_COMMANDS; i++)
    {
        if(!strcmp(command, LED_commands[i].command))
        {
            switch(LED_commands[i].action)
            {
                case LED_ACTION_NONE:
                    break;
                case LED_ACTION_SET:
                    LED_addCommandToStack(command);
                    break;
                case LED_ACTION_CLEAR:
                    logPrint("Clearing priority %d, -- %s\n", LED_commands[i].priorityClear, LED_commands[i].command);
                    LED_clearCommandStackByPriority(LED_commands[i].priorityClear);
                    break;
                case LED_ACTION_SET_CLEAR:
                    LED_clearCommandStackByPriority(LED_commands[i].priorityClear);
                    LED_addCommandToStack(command);
                    break;
            }
        }
    }

    for(int i = 0; i < MAX_PRIORITY; i++)
    {
        if(LED_priorityStack[i] != NULL) logPrint("%d - %s, enterTime: %li", i, LED_priorityStack[i]->command, LED_priorityStack[i]->startTime);
        else logPrint("%d - empty", i);
    }
}

void LED_clearCommand(char* command)
{
    LED_clearCommandFromStack(command);

    for(int i = 0; i < MAX_PRIORITY; i++)
    {
        if(LED_priorityStack[i] != NULL) logPrint("%d - %s, enterTime: %li", i, LED_priorityStack[i]->command, LED_priorityStack[i]->startTime);
        else logPrint("%d - empty", i);
    }
}