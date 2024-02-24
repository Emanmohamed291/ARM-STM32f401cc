/*
* SWITCH.c
*
* Created: 12/11/2023 12:58:15 AM
*  Author: Eman
*/

#include "SWITCH.h"
#include "GPIO.h"
#define NULL ((void *)0)
extern SWITCH_Config_t SWITCH_Config[_SWITCH_Num];

SWITCH_ErrorStates_t SWITCH_Init(void){
	u8 i;
	SWITCH_ErrorStates_t Loc_Error = SWITCH_OK;
	GPIO_PinConfiguration_t Switch;
	    
	    Switch.GPIO_Speed = GPIO_SPEED_LOW;
		for(i=0; i<_SWITCH_Num; i++){
			Switch.GPIO_Port = SWITCH_Config[i].SWITCH_Port_Number;
			Switch.GPIO_Pin  = SWITCH_Config[i].SWITCH_Pin_Number;
			Switch.GPIO_Mode = SWITCH_Config[i].SWITCH_Active_Mode;
			Loc_Error = GPIO_Init(&Switch);
		}
	return Loc_Error;
}
SWITCH_ErrorStates_t SWITCH_ReadValue(u8 Copy_u8SwitchName,  SWITCH_Out_State_t* Add_enumSwitchState){
	u8 Loc_Error = SWITCH_OK;
	if(Add_enumSwitchState == NULL){
		Loc_Error = SWITCH_Null_Pointer;
		return Loc_Error;
	}
	GPIO_GetPinValue(SWITCH_Config[Copy_u8SwitchName].SWITCH_Port_Number, SWITCH_Config[Copy_u8SwitchName].SWITCH_Pin_Number, Add_enumSwitchState);
	return Loc_Error;
}

