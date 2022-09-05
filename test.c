#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define LED_TEST    LED_WHITE

int main(int argc, char** argv)
{
    time_t startTime, endTime;

    time(&startTime);

    while(1)
    {
        time(&endTime);
        printf("%li\n", endTime-startTime);
        sleep(1);
    }
    return 0;
}