/*
* LED.h
*
* Created: 12/11/2023 12:50:53 AM
*  Author: Eman
*/


#ifndef LED_H_
#define LED_H_
#include "GPIO.h"
#include "LED_Config.h"
/************************************************************************************
 *                                       #defines                                  *
 * **********************************************************************************/
#define LED_OUTPUT_HIGH       1
#define LED_OUTPUT_LOW        0

#define LED_ACTIVE_HIGH       0
#define LED_ACTIVE_LOW        1

/************************************************************************************
 *                                       datatypes                                  *
 * **********************************************************************************/
typedef unsigned char         u8;
typedef short unsigned int    u16;
typedef unsigned int          u32;
/* error states for LED driver */
typedef enum{
	LED_Ok,
	LED_WrongOutState,
	LED_WrongActiveConfig,
	LED_WrongLedsNumber,
	LED_WrongPortNumber,
	LED_WrongPinNumber
}LED_ErrorStates_t;

/* to give parameters for each LED */
typedef struct{
	u8    LED_Port_Number;
	u8 	  LED_Pin_Number;
	u8	  LED_Active_Mode;
	u8	  LED_Out_State;
}LED_LedConfig_t;




/************************************************************************************
 *                                       FUNCTIONS                                  *
 * **********************************************************************************/
//LED_structErrors LED_structInit(void);
/**
* @brief to initialize LEDs
*
* @param void
*
* @return u8
*/
LED_ErrorStates_t LED_Init(void);
/**
* @brief to give value to LED.
*
* @param array of LED_structLedConfig - LedName - LED_enum_Out_State.
*
* @return u8.
*/
LED_ErrorStates_t LED_SetStatus(u8 Copy_LedName,  u8 Copy_LedState);
#endif /* LED_H_ */
