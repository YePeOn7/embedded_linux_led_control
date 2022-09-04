#include "led.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int command;
    int choosenLED;

    while(1)
    {
        printf("\n ====== Option ======\n");
        printf("0: Exit\n");
        printf("1: Single LED Test\n");
        printf("2: Command test\n");
        printf("Enter option: ");
        
        scanf("%d", &command);
        if(command == 0) 
        {   
            printf("Bye...\n");
            break;
        }

        printf("\n");
        switch(command)
        {
            case 1: // Single LED Test
                while(1)
                {
                    printf("\n ====== Single LED Test ======\n");
                    printf("0: Back\n");
                    printf("1: Red\n");
                    printf("2: Green\n");
                    printf("3: Blue\n");
                    printf("Choose LED: \n");
                    scan("%d", &choosenLED);
                    if(choosenLED == 0) break;
                    else if(choosenLED == 1 || choosenLED == 2 || choosenLED == 3)
                    {
                        while(1)
                        {   
                            switch(choosenLED)
                            {
                                case 1:  printf("\n ====== Red LED Command ======\n"); break;
                                case 2:  printf("\n ====== Green LED Command ======\n"); break;
                                case 3:  printf("\n ====== Blue LED Command ======\n"); break;
                            }
                           
                            printf("0: Back\n");
                            printf("1: Off\n");
                            printf("2: Static On\n");
                            printf("3: Blinking Slow\n");
                            printf("4: Blinking Fast\n");
                            printf("Choose LED Command: \n");

                            scanf("%d", &command);
                            if(command == 0) break;
                            switch(choosenLED)
                            {   
                                case 1: // Red
                                    switch(command)
                                    {
                                        case 1: LED_setRType(LED_OFF);break;
                                        case 2: LED_setRType(LED_STATIC);break;
                                        case 3: LED_setRType(LED_BLINKING_SLOW);break;
                                        case 4: LED_setRType(LED_BLINKING_FAST);break;
                                    }
                                    break; 

                                case 2: // Green
                                    switch(command)
                                    {
                                        case 1: LED_setGType(LED_OFF);break;
                                        case 2: LED_setGType(LED_STATIC);break;
                                        case 3: LED_setGType(LED_BLINKING_SLOW);break;
                                        case 4: LED_setGType(LED_BLINKING_FAST);break;
                                    }
                                    break;

                                case 3: // Blue
                                    switch(command)
                                    {
                                        case 1: LED_setBType(LED_OFF);break;
                                        case 2: LED_setBType(LED_STATIC);break;
                                        case 3: LED_setBType(LED_BLINKING_SLOW);break;
                                        case 4: LED_setBType(LED_BLINKING_FAST);break;
                                    }
                                    break;
                            }
                        }
                    }
                }
                break;
            case 2: // Command test
                while(1)
                {
                    printf("\n ====== Command ======\n");
                    printf("0: Exit\n");
                    printf("1: c1\n");
                    printf("2: c2\n");
                    printf("3: c3\n");
                    printf("4: c4\n");
                    printf("5: c5\n");
                    printf("6: c6\n");
                    printf("7: c7\n");
                    printf("8: c8\n");
                    printf("9: c9\n");
                    printf("10: c10\n");
                    printf("Enter option: ");
                    
                    scanf("%d", &command);
                    if(command == 0) break;
                    
                    printf("\n");
                    switch(command)
                    {
                        case 1: LED_setCommand("c1"); break;
                        case 2: LED_setCommand("c2"); break;
                        case 3: LED_setCommand("c3"); break;
                        case 4: LED_setCommand("c4"); break;
                        case 5: LED_setCommand("c5"); break;
                        case 6: LED_setCommand("c6"); break;
                        case 7: LED_setCommand("c7"); break;
                        case 8: LED_setCommand("c8"); break;
                        case 9: LED_setCommand("c9"); break;
                        case 10: LED_setCommand("c10"); break;
                    }
                }
                break;
        }
    }

    return 0;
}