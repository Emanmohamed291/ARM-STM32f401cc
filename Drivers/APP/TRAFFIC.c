/*
* TRAAFIC.c
*
* Created: 17/3/2024 12:58:15 AM
*  Author: Eman
*/

#include "LED.h"

#define PERIODICITY_SEC          1

enum{
    red,
    yellow,
    green
}state, prev;

static void red_on(void){
    LED_SetStatus(RED, LED_OUTPUT_HIGH);
    LED_SetStatus(YELLOW, LED_OUTPUT_LOW);
    LED_SetStatus(GREEN, LED_OUTPUT_LOW);
}
static void yellow_on(void){
    LED_SetStatus(RED, LED_OUTPUT_LOW);
    LED_SetStatus(YELLOW, LED_OUTPUT_HIGH);
    LED_SetStatus(GREEN, LED_OUTPUT_LOW);
}
static void green_on(void){
    LED_SetStatus(RED, LED_OUTPUT_LOW);
    LED_SetStatus(YELLOW, LED_OUTPUT_LOW);
    LED_SetStatus(GREEN, LED_OUTPUT_HIGH);
}
void Traffic_Runnable(void){
    switch (state)
    {
        static u32 seconds = 0;
	    seconds += PERIODICITY_SEC;
    case red:
    red_on();
    if(seconds == 3){
        seconds = 0;
        state = yellow;
        prev = red;
    }
    break;
    case yellow:
    yellow_on();
    if(seconds == 1 && prev == red){
        seconds = 0;
        state = green;
        prev = yellow;
    }
    if(seconds == 1 && prev == green){
        seconds = 0;
        state = red;
        prev = yellow;
    }
    break;
    case green:
    green_on();
    if(seconds == 2){
        seconds = 0;
        state = yellow;
        prev = green;
    }
    break;
    default:
        while (1)
        {
            /* code */
        }
        break;
    }
}
