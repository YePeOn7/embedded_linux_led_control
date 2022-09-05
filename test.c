#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include "led.h"

int main(int argc, char** argv)
{
    while(1)
    {
        logPrint("test");
        sleep(1);
    }
    return 0;
}