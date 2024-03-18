/*
* APP1.c
*
* Created: 17/3/2024 12:58:15 AM
*  Author: Eman
*/

#include "LED.h"

void APP1_Runnable(void){
    static u8 counter = 0;
    if(counter == 0){
        LED_SetStatus(RED, LED_OUTPUT_HIGH);
        counter = 1;
    }
    else{
        LED_SetStatus(RED, LED_OUTPUT_LOW);
        counter = 0;
    }  
}