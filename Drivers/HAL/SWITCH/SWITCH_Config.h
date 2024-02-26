/*
* SWITCH_Config.h
*
* Created: 12/11/2023 12:55:05 AM
*  Author: Eman
*/


#ifndef SWITCH_CONFIG_H_
#define SWITCH_CONFIG_H_

/* include libraries */
#include "SWITCH.h"

/* Naming for each LED */
typedef enum{
	SWITCH_Inc,
	SWITCH_Dec,
	_SWITCH_Num  
}SWITCH_t;


/* enum for ACTIVE HIGH or LOW */
typedef enum{
	SWITCH_Active_PU,
	SWITCH_Active_PD
}SWITCH_Active_Config_t;



#endif /* SWITCH_CONFIG_H_ */