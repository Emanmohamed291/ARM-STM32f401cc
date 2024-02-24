/*
* SWITCH.h
*
* Created: 12/11/2023 12:54:40 AM
*  Author: Eman
*/


#ifndef SWITCH_H_
#define SWITCH_H_
#include "GPIO.h"
#include "SWITCH_Config.h"
/************************************************************************************
 *                                       #defines                                  *
 * **********************************************************************************/
/* 
#define SWITCH_OUTPUT_HIGH       1
#define SWITCH_OUTPUT_LOW        0 

#define SWITCH_PULL_UP           0
#define SWITCH_PULL_DOWN         1
*/
/************************************************************************************
 *                                       datatypes                                  *
 * **********************************************************************************/
typedef unsigned char         u8;
typedef short unsigned int    u16;
typedef unsigned int          u32;
/* error states for SWITCH driver */
typedef enum {
	SWITCH_OK,
	SWITCH_Null_Pointer,
	SWITCH_Wrong_Active_Mode,
	SWITCH_Wrong_Switchs_Number,
	SWITCH_Wrong_Port_Number,
	SWITCH_Wrong_Pin_Number		
}SWITCH_ErrorStates_t;

/* enum for ACTIVE HIGH or LOW */
typedef enum{
	SWITCH_Out_Low,
	SWITCH_Out_High
}SWITCH_Out_State_t;

/* to give parameters for each LED */
typedef struct{
	u8    SWITCH_Port_Number;
	u8 	  SWITCH_Pin_Number;
	u8	  SWITCH_Active_Mode;/* pull up or pull down */
}SWITCH_Config_t;

/************************************************************************************
 *                                       FUNCTIONS                                  *
 * **********************************************************************************/
/**
* @brief to initialize SWITCHs
*
* @param void
*
* @return error state.
*/
SWITCH_ErrorStates_t SWITCH_Init(void);
/**
* @brief to give value to SWITCH.
*
* @param array of SWITCH_structLedConfig - LedName - SWITCH_enum_Out_State.
*
* @return error state.
*/
SWITCH_ErrorStates_t SWITCH_ReadValue(u8 Copy_u8SwitchName,  SWITCH_Out_State_t* Add_enumSwitchState);


#endif /* SWITCH_H_ */