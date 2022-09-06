#include "led.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int command;
    int choosenLED;

    while(1)
    {
        printf("\n ====== Option ======\n");
        printf("0: Exit\n");
        printf("1: LED Trigger Test\n");
        printf("2: Set Command Test\n");
        printf("3: Clear Command Test\n");
        printf("Enter option: ");
        
        scanf("%d", &command);
        if(command == 0) 
        {   
            printf("Bye...^^\n");
            break;
        }
        else if(command > 3 || command < 0)
        {
            printf("Wrong input. Enter option 1-3...");
            continue;
        }
        printf("\n");
        
        switch(command)
        {
            case 1: // Single LED Test
                while(1)
                {
                    printf("\n ====== Single LED Test ======\n");
                    printf("0: <<< Back\n");
                    printf("1: Red\n");
                    printf("2: Green\n");
                    printf("3: Blue\n");
                    printf("4: Cyan\n");
                    printf("5: Purple\n");
                    printf("6: Yellow\n");
                    printf("7: White\n");
                    printf("Choose LED: \n");
                    scanf("%d", &choosenLED);
                    if(choosenLED == 0) break;
                    else if(choosenLED > 0 && choosenLED < 8)
                    {
                        // convert to ledColor_t
                        switch(choosenLED)
                        {
                            case 1: choosenLED = LED_RED; break;
                            case 2: choosenLED = LED_GREEN; break;
                            case 3: choosenLED = LED_BLUE; break;
                            case 4: choosenLED = LED_CYAN; break;
                            case 5: choosenLED = LED_PURPLE; break;
                            case 6: choosenLED = LED_YELLOW; break;
                            case 7: choosenLED = LED_WHITE; break;
                        }

                        while(1)
                        {   
                            switch(choosenLED)
                            {
                                case LED_RED: printf("\n ====== Red LED Command ======\n"); break;
                                case LED_GREEN: printf("\n ====== Green LED Command ======\n"); break;
                                case LED_BLUE: printf("\n ====== Blue LED Command ======\n"); break;
                                case LED_CYAN: printf("\n ====== Cyan LED Command ======\n"); break;
                                case LED_PURPLE: printf("\n ====== Purple LED Command ======\n"); break;
                                case LED_YELLOW: printf("\n ====== Yellow LED Command ======\n"); break;
                                case LED_WHITE: printf("\n ====== White LED Command ======\n"); break;
                            }
                           
                            printf("0: <<< Back\n");
                            printf("1: Off\n");
                            printf("2: Static On\n");
                            printf("3: Blinking Slow\n");
                            printf("4: Blinking Very Slow\n");
                            printf("5: Blinking Fast\n");
                            printf("Choose LED Command: ");

                            scanf("%d", &command);
                            if(command == 0) break;
                            else if(command > 0 && command < 6)
                            {
                                //convert to triggerType_t
                                switch(command)
                                {
                                    case 1: 
                                        command = LED_OFF; 
                                        printf("Turning off led\n");
                                        break;
                                    case 2: 
                                        command = LED_STATIC; 
                                        printf("Turning on led (Static)\n");
                                        break;
                                    case 3: 
                                        command = LED_BLINKING_SLOW; 
                                        printf("Turning on led (Blinking Slow)\n");
                                        break;
                                    case 4: 
                                        command = LED_BLINKING_VERY_SLOW; 
                                        printf("Turning on led (Blinking Very Slow)\n");
                                        break;
                                    case 5: 
                                        command = LED_BLINKING_FAST; 
                                        printf("Turning on led (Blinking Fast)\n");
                                        break;
                                }

                                LED_setTriggerType(choosenLED, command);
                            }
                            usleep(500000);
                        }
                    }
                    usleep(500000);
                }
                break;
            case 2: // Set Command Test
                while(1)
                {
                    printf("\n ====== Set Command ======\n");
                    printf("0: Exit\n");
             
                    for(int i = 0; i < LED_getLenCommands(); i++) printf("%d: %s\n", i+1, LED_commands[i].command);
                    printf("Enter option: ");
                    scanf("%d", &command);

                    if(command == 0) break;
                    else if(command < LED_getLenCommands() + 1)
                    {
                        printf("\n");
                        LED_setCommand(LED_commands[command-1].command);
                    }

                    usleep(500000);
                }
                break;

            case 3: // Clear Command Test
                while(1)
                {
                    printf("\n ====== Clear Command ======\n");
                    printf("0: Exit\n");
                    for(int i = 0; i < LED_getLenCommands(); i++) printf("%d: %s\n", i+1, LED_commands[i].command);
                    printf("Enter option: ");
                    scanf("%d", &command);
                    
                    if(command == 0) break;
                    else if(command < LED_getLenCommands() + 1)
                    {
                        printf("\n");
                        LED_clearCommand(LED_commands[command-1].command);
                    }

                    usleep(500000);
                }
                break;
        }
    }

    return 0;
}
