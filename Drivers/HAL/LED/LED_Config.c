/*
* LED_Config.c
*
* Created: 12/11/2023 12:40:07 AM
*  Author: Eman
*/
/* include libraries */
#include "LED.h"

/* array of struct of LEDS configurations so give configurations for each LED */
LED_LedConfig_t LED_LedsConfig[_LED_Num] = {
	/* first LED configurations */
	[LED_Alarm] = {
		.LED_Port_Number = GPIO_A,
		.LED_Pin_Number  = GPIO_PIN_0,
		.LED_Active_Mode = LED_ACTIVE_HIGH,
		.LED_Out_State   = LED_OUTPUT_HIGH
	},
	/* second LED configurations and so on..*/
	[LED_Start] = {
		.LED_Port_Number = GPIO_A,
		.LED_Pin_Number  = GPIO_PIN_1,
		.LED_Active_Mode = LED_ACTIVE_HIGH,
		.LED_Out_State   = LED_OUTPUT_HIGH
	}
};

