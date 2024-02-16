/*
 * GPIO.h
 *
 * Created: 2/15/2024 8:59:58 PM
 *  Author: eman
 */ 


#ifndef GPIO_H_
#define GPIO_H_
/************************************************************************************
 *                                       datatypes                                  *
 * **********************************************************************************/
typedef unsigned char         u8;
typedef short unsigned int    u16;
typedef unsigned int          u32;

typedef enum
{
	GPIO_Ok,
	GPIO_WrongPin,
	GPIO_WrongPort,
	GPIO_WrongMode,
	GPIO_WrongSpeed,
	GPIO_WrongAltf,
	GPIO_NULL
}ErrorStatus_t;

typedef struct
{
	volatile u32 GPIOx_MODER;
	volatile u32 GPIOx_OTYPER;
	volatile u32 GPIOx_OSPEEDR;
	volatile u32 GPIOx_PUPDR;
	volatile u32 GPIOx_IDR;
	volatile u32 GPIOx_ODR;
	volatile u32 GPIOx_BSRR;
	volatile u32 GPIOx_LCKR;
	volatile u32 GPIOx_AFRL;
	volatile u32 GPIOx_AFRH;

}GPIO_Registers_t;

typedef struct
{
	u32 GPIO_Port;
	u32 GPIO_Mode;
	u32 GPIO_Speed;
	u32 GPIO_Pin;
	u32 GPIO_ALTF;

}GPIO_PinConfiguration_t;

/************************************************************************************
 *                                       #defines                                  *
 * **********************************************************************************/

#define GPIO_HIGH                   0
#define GPIO_LOW                    16

#define  GPIO_SPEED_LOW             0x00000000
#define  GPIO_SPEED_MEDIUM          0x00000001
#define  GPIO_SPEED_HIGH            0x00000002
#define  GPIO_SPEED_VERYHIGH        0x00000003

#define GPIO_AF00                   0x00000000
#define GPIO_AF01                   0x00000001
#define GPIO_AF02                   0x00000002
#define GPIO_AF03                   0x00000003
#define GPIO_AF04                   0x00000004
#define GPIO_AF05                   0x00000005
#define GPIO_AF06                   0x00000006
#define GPIO_AF07                   0x00000007
#define GPIO_AF08                   0x00000008
#define GPIO_AF09                   0x00000009
#define GPIO_AF10                   0x0000000A
#define GPIO_AF11                   0x0000000B
#define GPIO_AF12                   0x0000000C
#define GPIO_AF13                   0x0000000D
#define GPIO_AF14                   0x0000000E
#define GPIO_AF15                   0x0000000F

#define GPIO_MODE_INPUT_FL          0x00000000  /* moder 00*/
#define GPIO_MODE_INPUT_PU          0x00000008  /* 4,5TH FOR PU OR PD */
#define GPIO_MODE_INPUT_PD          0x00000010

#define GPIO_MODE_OUTPUT_PP         0x00000001  /* moder 01*/
#define GPIO_MODE_OUTPUT_PP_PU      0x00000009
#define GPIO_MODE_OUTPUT_PP_PD      0x00000011
#define GPIO_MODE_OUTPUT_OD         0x00000005  /* 3RD BIT FOR PP OR OD */
#define GPIO_MODE_OUTPUT_OD_PU      0x0000000D
#define GPIO_MODE_OUTPUT_OD_PD      0x00000015

#define GPIO_MODE_AF_PP             0x00000002  /* moder 02*/
#define GPIO_MODE_AF_PP_PU          0x0000000A
#define GPIO_MODE_AF_PP_PD          0x00000012
#define GPIO_MODE_AF_OD             0x00000006
#define GPIO_MODE_AF_OD_PU          0x0000000E
#define GPIO_MODE_AF_OD_PD          0x00000016


#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_TIM1		0x01
#define GPIO_ALTERNATIVE_TIM3		0x02
#define GPIO_ALTERNATIVE_TIM9		0x03
#define GPIO_ALTERNATIVE_I2C		0x04
#define GPIO_ALTERNATIVE_SPI		0x05
#define GPIO_ALTERNATIVE_SPI3		0x06
#define GPIO_ALTERNATIVE_USART1		0x07
#define GPIO_ALTERNATIVE_USART6		0x08
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00


#define GPIOA	                    ((volatile GPIO_Registers_t* const)0x40020000)
#define GPIOB	                    ((volatile GPIO_Registers_t* const)0x40020400)
#define GPIOC	                    ((volatile GPIO_Registers_t* const)0x40020800)
/*
#define GPIOD	                    ((volatile GPIO_Registers_t* const)0x40020C00)
#define GPIOE	                    ((volatile GPIO_Registers_t* const)0x40021000)
#define GPIOH	                    ((volatile GPIO_Registers_t* const)0x40021C00)
*/
#define GPIO_PIN_0                  0x00000000
#define GPIO_PIN_1                  0x00000001
#define GPIO_PIN_2                  0x00000002
#define GPIO_PIN_3                  0x00000003
#define GPIO_PIN_4                  0x00000004
#define GPIO_PIN_5                  0x00000005
#define GPIO_PIN_6                  0x00000006
#define GPIO_PIN_7                  0x00000007
#define GPIO_PIN_8                  0x00000008
#define GPIO_PIN_9                  0x00000009
#define GPIO_PIN_10                 0x0000000A
#define GPIO_PIN_11                 0x0000000B
#define GPIO_PIN_12                 0x0000000C
#define GPIO_PIN_13                 0x0000000D
#define GPIO_PIN_14                 0x0000000E
#define GPIO_PIN_15                 0x0000000F

/************************************************************************************
 *                                       functions                                  *
 * **********************************************************************************/

ErrorStatus_t GPIO_Init(GPIO_PinConfiguration_t* Add_pstrPinConfg);
ErrorStatus_t GPIO_SetPinValue(u32 Copy_GPIOPort, u32 Copy_GPIOPin, u32 Copy_GPIOPinState);
ErrorStatus_t GPIO_GetPinValue(u32 Copy_GPIOPort, u32 Copy_GPIOPin, u32* Add_GPIOPinState);
#endif /* GPIO_H_ */
