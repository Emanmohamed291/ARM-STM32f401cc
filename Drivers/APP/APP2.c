/*
* APP1.c
*
* Created: 17/3/2024 12:58:15 AM
*  Author: Eman
*/

#include "LED.h"
#include "SWITCH.h"



void APP2_Runnable(void){
    u8 switch_state;
    SWITCH_ReadValue(SWITCH_Inc, &switch_state);
    if(switch_state == SWITCH_Out_Low){
        LED_SetStatus(RED, LED_OUTPUT_HIGH);
    }
    else{
        LED_SetStatus(RED, LED_OUTPUT_LOW);
    }  
}