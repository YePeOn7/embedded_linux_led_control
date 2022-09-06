#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include "led.h"

char str1[100] = "Yohan";
char* str2;

int main(int argc, char** argv)
{
    str2 = str1;
    while(1)
    {
        printf("%s %s\n", str1, str2);
        sleep(1);
    }
    return 0;
}