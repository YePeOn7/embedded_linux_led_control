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
    LED_BLINKING_FAST
}indicatorType_t;

typedef struct {
    char* command;
    ledColor_t color;
    indicatorType_t type;
    int priority;
}ledCommand_t;

/****************************************/

void test();
pthread_t LED_createThread();
void LED_setRType(indicatorType_t type);
void LED_setGType(indicatorType_t type);
void LED_setBType(indicatorType_t type);
void LED_setCommand(char* command);

#endif // __LED_H__