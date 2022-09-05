#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include "led.h"

typedef struct
{
    int data1;
    int data2;
    int data3;
}s_t;

int main(int argc, char** argv)
{
    s_t myS = {2,3};
    while(1)
    {
        printf("%d %d %d\n", myS.data1, myS.data2, myS.data3);
        sleep(1);
    }
    return 0;
}