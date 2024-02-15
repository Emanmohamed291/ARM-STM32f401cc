#ifndef RCC_H_
#define RCC_H_


/************************************************************************************
 *                                       datatypes                                  *
 * **********************************************************************************/
typedef unsigned char         u8;
typedef short unsigned int    u16;
typedef unsigned int          u32;

typedef enum
{
	RCC_Ok,
	RCC_WrongBusName,
	RCC_WrongPeripheralName,
	RCC_WrongMode,
	RCC_TimeOut,
	RCC_WrongPLLSource,
	RCC_WrongPLLConfig,
	RCC_WrongClockSystemName
}ErrorStatus_t;

typedef struct{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 RCC_Reserved0[2];
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 RCC_Reserved1[2];
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 RCC_Reserved2[2];
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	volatile u32 RCC_Reserved3[2];
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	volatile u32 RCC_Reserved4[2];
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 RCC_Reserved5[2];
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
	volatile u32 RCC_RESERVED;
	volatile u32 RCC_DCKCFGR;
}RCC_Registers_t;


/************************************************************************************
 *                                       #defines                                  *
 * **********************************************************************************/


#define RCC                             ((RCC_Registers_t*)(0x40023800))
#define RCC_BITS_NUMBER                 32

#define ENABLE                          0
#define DISABLE                         1

#define RCC_HSI_READY                   0x00000002
#define RCC_HSE_READY                   0x00020000
#define RCC_PLL_READY                   0x02000000

#define RCC_HSI_CLOCK	                0x00000000
#define RCC_HSE_CLOCK	                0x00000001
#define RCC_PLL_CLOCK	                0x00000002


#define RCC_PLL_HSI		                0x00000000
#define RCC_PLL_HSE		                0x00400000
/***************************************************************/
/******************** peripherals ******************************/
/***************************************************************/
#define GPIOA                             0
#define GPIOB                             1
#define GPIOC                             2
#define GPIOD                             3
#define GPIOE                             4
#define GPIOH                             7
#define CRC                               12
#define DMA1                              21
#define DMA2                              22

#define TIM2RST                            0
#define TIM3RST                            1
#define TIM4RST                            2
#define TIM5RST                            3
#define WWDGRST                            11
#define SPI2RST                            14
#define SPI3RST                            15
#define USART2RST                          17
#define I2C1RST                            21
#define I2C2RST                            22
#define I2C3RST                            23
#define PWRRST                             28

#define TIM1EN                             0
#define USART1EN                           4
#define USART6EN                           5
#define ADC1EN                             8
#define SDIOEN                             11
#define SPI1EN                             12
#define SPI4EN                             13
#define SYSCFGEN                           14
#define TIM9EN                             16
#define TIM10EN                            17
#define TIM11EN                            18

enum{
	PLLM0,
	PLLN0=6,
	PLLP0=16
};
typedef enum {
	BusAHB1,
	BusAHB2,
	BusAPB1,
	BusAPB2,
	BusAHB1LP,
	BusAHB2LP,
	BusAPB1LP,
	BusAPB2LP
}RCCBusName_t;

/************************************************************************************
 *                                       functions                                  *
 * **********************************************************************************/
/**
 * \brief :
 *
 * \param ClockSystemName ---->RCC_HSI_CLOCK -- RCC_HSE_CLOCK -- RCC_PLL_CLOCK
 *
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_DesplayClock(u8 ClockSystemName);
/**
 * \brief :
 *
 * \param ClockSystemName ---->RCC_HSI_CLOCK -- RCC_HSE_CLOCK -- RCC_PLL_CLOCK
 *
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_DisableClock(u8 ClockSystemName);
/**
 * \brief :
 *
 * \param ClockSystemName ---->RCC_HSI_CLOCK -- RCC_HSE_CLOCK -- RCC_PLL_CLOCK
 *
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_SelectSystemClock(u8 ClockSystemName);
/**
 * \brief :
 *
 * \param ClockSystemName ---->RCC_HSI_CLOCK -- RCC_HSE_CLOCK -- RCC_PLL_CLOCK
 *
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_PLLSourceConfigration(u8 PLL_Source);
/**
 * \brief
 *
 * \param PLL_Source
 * \param N
 * \param M
 * \param P
 *  • f(VCO clock) = f(PLL clock input) × (PLLN / PLLM)
 • f(PLL general clock output) = f(VCO clock) / PLLP
 • f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_PLLPrescallerConfigration(u16 N, u16 M, u16 P);
/**
 * \brief :
 *
 * \param BusName ----------------> 	BusAHB1, BusAHB2, BusAPB1, BusAPB2, BusAHB1LP, BusAHB2LP, BusAPB1LP, BusAPB2LP
 *
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_EnablePeripheralClock(RCCBusName_t BusName, u8 PeripheralName);
/**
 * \brief :
 *
* \param BusName ----------------> 	BusAHB1, BusAHB2, BusAPB1, BusAPB2, BusAHB1LP, BusAHB2LP, BusAPB1LP, BusAPB2LP
 *
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_DisablePeripheralClock(RCCBusName_t BusName, u8 PeripheralName);
#endif
