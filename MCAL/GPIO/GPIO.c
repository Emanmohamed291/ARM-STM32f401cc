/*
 * GPIO.c
 *
 * Created: 2/15/2024 9:00:35 PM
 *  Author: eman
 */ 
#include "GPIO.h"
/*NULL POINTER*/
#define	NULL	                                (void*)0

#define GPIO_MODER_MASK                         0x00000003 /* 2 BITS */
#define GPIO_OTYPER_MASK                        0x00000001 /* 1 BIT */
#define GPIO_OSPEEDR_MASK                       0x00000003
#define GPIO_PUPDR_MASK                         0x00000003

#define PIN_MODER_OFFSET                        0x00000002
#define PIN_OTYPER_OFFSET                       0x00000001
#define PIN_OSPEEDR_OFFSET                      0x00000002
#define PIN_PUPDR_OFFSET                        0x00000002
#define PIN_ALTERNATIVE_OFFSET                  0x00000004

volatile GPIO_Registers_t* const GPIO_Ports[3] =
{
    (GPIO_Registers_t *)GPIOA,
    (GPIO_Registers_t *)GPIOB,
    (GPIO_Registers_t *)GPIOC
};

ErrorStatus_t GPIO_Init(GPIO_PinConfiguration_t* Add_pstrPinConfg){
	ErrorStatus_t Loc_ErrorStatus = GPIO_Ok;
	if(Add_pstrPinConfg == NULL){
		Loc_ErrorStatus = GPIO_NULL;
	}
	else if(Add_pstrPinConfg->GPIO_Pin > GPIO_PIN_15){
		Loc_ErrorStatus = GPIO_WrongPin;
	}
	else if(Add_pstrPinConfg->GPIO_Port > (u32)GPIOC){
		Loc_ErrorStatus = GPIO_WrongPort;
	}
	else if(Add_pstrPinConfg->GPIO_ALTF > GPIO_AF15){
		Loc_ErrorStatus = GPIO_WrongAltf;
	}
	else if(Add_pstrPinConfg->GPIO_Speed > GPIO_SPEED_VERYHIGH){
		Loc_ErrorStatus = GPIO_WrongSpeed;
	}
	else if(Add_pstrPinConfg->GPIO_Mode > GPIO_MODE_AF_OD_PD){
			Loc_ErrorStatus = GPIO_WrongMode;
	}
	else{
		/* These bits are written by software to configure the I/O direction mode */
	    u32 Loc_Temp = GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_MODER;
	    Loc_Temp &= ~(GPIO_MODER_MASK << (Add_pstrPinConfg->GPIO_Pin*PIN_MODER_OFFSET));
	    Loc_Temp |= ((Add_pstrPinConfg->GPIO_Mode & GPIO_MODER_MASK) << (Add_pstrPinConfg->GPIO_Pin*PIN_MODER_OFFSET));
	    GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_MODER = Loc_Temp;
	    /* These bits are written by software to configure the output type of the I/O port */
	    Loc_Temp = GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_OTYPER;
	    Loc_Temp &= ~(GPIO_OTYPER_MASK << (Add_pstrPinConfg->GPIO_Pin*PIN_OTYPER_OFFSET));
		Loc_Temp |= (((Add_pstrPinConfg->GPIO_Mode>>PIN_MODER_OFFSET) & GPIO_OTYPER_MASK) << (Add_pstrPinConfg->GPIO_Pin*PIN_OTYPER_OFFSET));
		GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_OTYPER = Loc_Temp;
	    /* These bits are written by software to configure the I/O pull-up or pull-down */
	    Loc_Temp = GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_PUPDR;
	    Loc_Temp &= ~(GPIO_PUPDR_MASK << (Add_pstrPinConfg->GPIO_Pin*PIN_PUPDR_OFFSET));
		Loc_Temp |= (((Add_pstrPinConfg->GPIO_Mode>>(PIN_MODER_OFFSET + PIN_OTYPER_OFFSET)) & GPIO_PUPDR_MASK) << (Add_pstrPinConfg->GPIO_Pin*PIN_PUPDR_OFFSET));
		GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_PUPDR = Loc_Temp;
		/* These bits are written by software to configure the I/O output speed */
	    Loc_Temp = GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_OSPEEDR;
	    Loc_Temp &= ~(GPIO_OSPEEDR_MASK << (Add_pstrPinConfg->GPIO_Pin*PIN_OSPEEDR_OFFSET));
		Loc_Temp |= ((Add_pstrPinConfg->GPIO_Speed & GPIO_OSPEEDR_MASK) << (Add_pstrPinConfg->GPIO_Pin*PIN_OSPEEDR_OFFSET));
		GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_OSPEEDR = Loc_Temp;
		/* AF */
		if(Add_pstrPinConfg->GPIO_Pin <= GPIO_PIN_7){
			Loc_Temp = GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_AFRL;
			Loc_Temp |= Add_pstrPinConfg->GPIO_ALTF << (PIN_ALTERNATIVE_OFFSET * Add_pstrPinConfg->GPIO_Pin);
			GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_AFRL = Loc_Temp;
		}
		else{
			Loc_Temp = GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_AFRH;
			Loc_Temp |= Add_pstrPinConfg->GPIO_ALTF << (PIN_ALTERNATIVE_OFFSET * Add_pstrPinConfg->GPIO_Pin - GPIO_PIN_7);
			GPIO_Ports[Add_pstrPinConfg->GPIO_Port]->GPIOx_AFRH = Loc_Temp;
		}
	}
	return Loc_ErrorStatus;
}

ErrorStatus_t GPIO_SetPinValue(u32 Copy_GPIOPort, u32 Copy_GPIOPin, u32 Copy_GPIOPinState){
	ErrorStatus_t Loc_ErrorStatus = GPIO_Ok;
		if(Copy_GPIOPin > GPIO_PIN_15){
			Loc_ErrorStatus = GPIO_WrongPin;
		}
		else if(Copy_GPIOPort > (u32)GPIOC){
			Loc_ErrorStatus = GPIO_WrongPort;
		}
		else if(Copy_GPIOPinState != GPIO_LOW && Copy_GPIOPinState != GPIO_HIGH){
				Loc_ErrorStatus = GPIO_WrongMode;
		}
		else{
			GPIO_Ports[Copy_GPIOPort]->GPIOx_BSRR |= 1<<(Copy_GPIOPin+Copy_GPIOPinState);
		}
	return Loc_ErrorStatus;
}

ErrorStatus_t GPIO_GetPinValue(u32 Copy_GPIOPort, u32 Copy_GPIOPin, u32* Add_GPIOPinState){
	ErrorStatus_t Loc_ErrorStatus = GPIO_Ok;
		if(Copy_GPIOPin > GPIO_PIN_15){
			Loc_ErrorStatus = GPIO_WrongPin;
		}
		else if(Copy_GPIOPort > (u32)GPIOC){
			Loc_ErrorStatus = GPIO_WrongPort;
		}
		else if(Add_GPIOPinState == NULL){
				Loc_ErrorStatus = GPIO_NULL;
		}
		else{
			*Add_GPIOPinState = (GPIO_Ports[Copy_GPIOPort]->GPIOx_IDR>>Copy_GPIOPin) & 1;
		}
	return Loc_ErrorStatus;
}






