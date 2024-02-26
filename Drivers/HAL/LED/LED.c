/*
* LED.c
*
* Created: 12/11/2023 12:39:46 AM
*  Author: Eman
*/
#include "LED.h"
#include "GPIO.h"


extern LED_LedConfig_t LED_LedsConfig[_LED_Num];

LED_ErrorStates_t LED_Init(void){
	u8 i;
	LED_ErrorStates_t Loc_Error = LED_Ok;

	GPIO_PinConfiguration_t led;
	    led.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	    led.GPIO_Speed = GPIO_SPEED_LOW;
	    led.GPIO_ALTF = GPIO_ALTERNATIVE_SYSTEM;
		for(i=0; i<_LED_Num; i++){
			led.GPIO_Port = LED_LedsConfig[i].LED_Port_Number;
			led.GPIO_Pin  = LED_LedsConfig[i].LED_Pin_Number;
			GPIO_Init(&led);
		}

	return Loc_Error;
}

LED_ErrorStates_t LED_SetStatus(u8 Copy_LedName,  u8 Copy_LedState){
	LED_ErrorStates_t Loc_Error = LED_Ok;
	if(Copy_LedName > _LED_Num){
		Loc_Error = LED_WrongLedsNumber;
	}
	else if(Copy_LedState > LED_OUTPUT_HIGH){
		Loc_Error = LED_WrongOutState;
	}
	else{
		GPIO_SetPinValue((u32)LED_LedsConfig[Copy_LedName].LED_Port_Number, LED_LedsConfig[Copy_LedName].LED_Pin_Number, LED_LedsConfig[Copy_LedName].LED_Active_Mode^Copy_LedState);
	}
	return Loc_Error;
}

