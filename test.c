#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include "led.h"

char str1[];

char str1[]="yohan";


int main(int argc, char** argv)
{
    while(1)
    {
        printf("%s\n", str1);
        sleep(1);
    }
    return 0;
}