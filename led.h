// #pragma once

#ifndef __LED_H__
#define __LED_H__

#include <stdio.h>
#include <pthread.h>

typedef enum
{
    LED_WHITE,
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_YELLOW, //RG
    LED_PURPLE, //RB
    LED_CYAN    //GB
}ledColor_t;

typedef enum
{
    LED_OFF,
    LED_STATIC,
    LED_BLINKING_SLOW,
    LED_BLINKING_VERY_SLOW,
    LED_BLINKING_FAST
}triggerType_t;

typedef struct {
    char* command;
    ledColor_t color;
    triggerType_t type;
    int priority;
    int holdTime; // in seconds
}ledCommand_t;

/****************************************/

void test();
// pthread_t LED_createThread();
// void LED_setRedTriggerType(triggerType_t type);
// void LED_setGreenTriggerType(triggerType_t type);
// void LED_setBlueTriggerType(triggerType_t type);
void LED_setTriggerType(ledColor_t color, triggerType_t type);
void LED_setCommand(char* command);
void LED_clearCommand(char* command);

#endif // __LED_H__