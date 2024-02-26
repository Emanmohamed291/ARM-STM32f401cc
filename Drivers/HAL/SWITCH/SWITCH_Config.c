/*
* SWITCH_Config.c
*
* Created: 12/11/2023 12:58:47 AM
*  Author: Eman
*/
/* including libraries */
#include "SWITCH_Config.h"

/* array of struct of SWITCHS configurations so give configurations for each SWITCH */
SWITCH_Config_t SWITCH_Config[_SWITCH_Num] = {
	/* first SWITCH configurations */
	[SWITCH_Inc] = {
		.SWITCH_Port_Number = GPIO_A,
		.SWITCH_Pin_Number  = GPIO_PIN_0,
		.SWITCH_Active_Mode = SWITCH_Active_PU
	},
	/* second SWITCH configurations and so on..*/
	[SWITCH_Dec] = {
		.SWITCH_Port_Number = GPIO_A,
		.SWITCH_Pin_Number  = GPIO_PIN_1,
		.SWITCH_Active_Mode = SWITCH_Active_PU
	}
};