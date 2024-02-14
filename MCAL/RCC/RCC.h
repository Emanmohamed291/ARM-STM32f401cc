#ifndef RCC_H_
#define RCC_H_

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

#define RCC_HSI_SYSTEM_CLOCK_SELECTION     0
#define RCC_HSE_SYSTEM_CLOCK_SELECTION     1
#define RCC_PLL_SYSTEM_CLOCK_SELECTION     2

#define RCC                                ((RCC_registers*)(0x40023800))
#define RCC_BITS_NUMBER                    32

enum {
	HSION          ,
	HSIRDY         ,
	HSITRIM0     =3,
	HSITRIM1       ,
	HSITRIM2       ,
	HSITRIM3       ,
	HSITRIM4       ,
	HSICAL0        ,
	HSICAL1        ,
	HSICAL2        ,
	HSICAL3        ,
	HSICAL4        ,
	HSICAL5        ,
	HSICAL6        ,
	HSICAL7        ,
	HSEON          ,
	HSERDY         ,
	HSEBYP         ,
	CSSON       =24,
	PLLON         ,
	PLLRDY        ,
	PLLI2SON      ,
	PLLI2SRDY     
};

enum {
	PLLM0         ,
	PLLM1         ,
	PLLM2         ,
	PLLM3         ,
	PLLM4         ,
	PLLM5         ,
	PLLN0         ,
	PLLN1         ,
	PLLN2         ,
	PLLN3         ,
	PLLN4         ,
	PLLN5         ,
	PLLN6         ,
	PLLN7         ,
	PLLN8         ,
	PLLP0      =16,
	PLLP1         ,
	PLLSRC     =22,
	PLLQ0      =24,
	PLLQ1         ,
	PLLQ2         ,
	PLLQ3      
};

enum {
	SW0           ,
	SW1           ,
	SWS0          ,
	SWS1          ,
	HPRE0         ,
	HPRE1         ,
	HPRE2         ,
	HPRE3         ,
	Reserved      ,
	PPRE10        ,
	PPRE11        ,
	PPRE12        ,
	PPRE20        ,
	PPRE21        ,
	PPRE22        ,
	RTCPRE0       ,
	RTCPRE1       ,
	RTCPRE2       ,
	RTCPRE3       ,
	RTCPRE4       ,
	MCO10         ,
	MCO11         ,
	I2SSRC        ,
	MCO1PRE0      ,
	MCO1PRE1      ,
	MCO1PRE2      ,
	MCO2PRE0      ,
	MCO2PRE1      ,
	MCO2PRE2      ,
	MCO20         ,
	MCO21         
};

enum {
	 LSIRDYF       ,
	 LSERDYF       ,
	 HSIRDYF       ,
	 HSERDYF       ,
	 PLLRDYF       ,
	 PLLI2SRDYF    ,
	 CSSF        =7,
	 LSIRDYIE      ,
	 LSERDYIE      ,
	 HSIRDYIE      ,
	 HSERDYIE      ,
	 PLLRDYIE      ,
	 PLLI2SRDYIE   ,
	 LSIRDYC    =16,
	 LSERDYC       ,
	 HSIRDYC       ,
	 HSERDYC       ,
	 PLLRDYC       ,
	 PLLI2SRDYC    ,
	 Reserved      ,
	 CSSC          
};
typedef unsigned int  u32;
typedef unsigned char u8;

typedef struct{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 RCC_Reserved[2];
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 RCC_Reserved[2];
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 RCC_Reserved[2];
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	volatile u32 RCC_Reserved[2];
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	volatile u32 RCC_Reserved[2];
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 RCC_Reserved[2];
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
	volatile u32 RCC_RESERVED;
	volatile u32 RCC_DCKCFGR;
}RCC_registers_t;

typedef enum {
	Disable,
	Enable
}ModeEnum_t;

typedef enum {
	RCCOk,
	RCCWrongBusName,
	RCCWrongPeripheralName,
	RCCWrongMode,
	RCCWrongPLLSource,
	RCCWrongPLLConfig,
	RCCClockSystemName
}ErrorStatus_t;
typedef enum {
	ClockSystemHSI,
	ClockSystemHSE,
	ClockSystemPLL,
	ClockSystemPLLI2s
}ClockSystemName_t;
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

typedef enum{
	PLL_Source_HSE,
	PLL_Source_HSI
}PLL_Source_t;

/**
 * \brief : 
 * 
 * \param ClockSystemName
 * \param Enable_or_Disable
 * 
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_ControlClock(ClockSystemName_t ClockSystemName, ModeEnum_t Enable_or_Disable);
/**
 * \brief 
 * 
 * \param ClockSystemName
 * 
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_SelectSystemClock(ClockSystemName_t ClockSystemName);
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
ErrorStatus_t RCC_PLLConfigration(PLL_Source_t PLL_Source, u8 N, u8 M, u8 P);

/**
 * \brief:  
 * 
 * \param BusName ----------------> 	BusAHB1, BusAHB2, BusAPB1, BusAPB2, BusAHB1LP, BusAHB2LP, BusAPB1LP, BusAPB2LP
 * \param PeripheralName --------->     RCC_HSI_SYSTEM_CLOCK_SELECTION,   RCC_HSE_SYSTEM_CLOCK_SELECTION, RCC_PLL_SYSTEM_CLOCK_SELECTION
 * \param Enable_or_Disable
 * 
 * \return ErrorStatus_t
 */
ErrorStatus_t RCC_PeripheralClock(RCCBusName_t BusName, u8 PeripheralName, ModeEnum_t Enable_or_Disable);

#endif

// #define RCC_CR      *((volatile unsigned char*)0x40023800)
// #define RCC_PLLCFGR *((volatile unsigned char*)0x40023804)
// #define RCC_CFGR    *((volatile unsigned char*)0x40023808)
// #define RCC_CIR     *((volatile unsigned char*)0x4002380C)
//
// typedef struct {
// 	unsigned int HSION      :1;
// 	unsigned int HSIRDY     :1;
// 	unsigned int Reserved   :1;
// 	unsigned int HSITRIM0   :1;
// 	unsigned int HSITRIM1   :1;
// 	unsigned int HSITRIM2   :1;
// 	unsigned int HSITRIM3   :1;
// 	unsigned int HSITRIM4   :1;
// 	unsigned int HSICAL0    :1;
// 	unsigned int HSICAL1    :1;
// 	unsigned int HSICAL2    :1;
// 	unsigned int HSICAL3    :1;
// 	unsigned int HSICAL4    :1;
// 	unsigned int HSICAL5    :1;
// 	unsigned int HSICAL6    :1;
// 	unsigned int HSICAL7    :1;
// 	unsigned int HSEON      :1;
// 	unsigned int HSERDY     :1;
// 	unsigned int HSEBYP     :1;
// 	unsigned int CSSON      :1;
// 	unsigned int Reserved   :4;
// 	unsigned int PLL_ON     :1;
// 	unsigned int PLL_RDY    :1;
// 	unsigned int PLL_I2SON  :1;
// 	unsigned int PLL_I2SRDY :1;
// 	unsigned int Reserved   :4;
// }RCC_CR_bits;
//
// typedef struct {
// 	unsigned int PLLM0      :1;
// 	unsigned int PLLM1      :1;
// 	unsigned int PLLM2      :1;
// 	unsigned int PLLM3      :1;
// 	unsigned int PLLM4      :1;
// 	unsigned int PLLM5      :1;
// 	unsigned int PLLN0      :1;
// 	unsigned int PLLN1      :1;
// 	unsigned int PLLN2      :1;
// 	unsigned int PLLN3      :1;
// 	unsigned int PLLN4      :1;
// 	unsigned int PLLN5      :1;
// 	unsigned int PLLN6      :1;
// 	unsigned int PLLN7      :1;
// 	unsigned int PLLN8      :1;
// 	unsigned int Reserved   :1;
// 	unsigned int PLLP0      :1;
// 	unsigned int PLLP1      :1;
// 	unsigned int Reserved   :4;
// 	unsigned int PLLSRC     :1;
// 	unsigned int Reserved   :1;
// 	unsigned int PLLQ0      :1;
// 	unsigned int PLLQ1      :1;
// 	unsigned int PLLQ2      :1;
// 	unsigned int PLLQ3      :1;
// 	unsigned int Reserved   :4;
// }RCC_PLLCFGR_bits;
//
// typedef struct {
// 	unsigned int SW0           :1;
// 	unsigned int SW1           :1;
// 	unsigned int SWS0          :1;
// 	unsigned int SWS1          :1;
// 	unsigned int HPRE0         :1;
// 	unsigned int HPRE1         :1;
// 	unsigned int HPRE2         :1;
// 	unsigned int HPRE3         :1;
// 	unsigned int Reserved      :2;
// 	unsigned int PPRE10        :1;
// 	unsigned int PPRE11        :1;
// 	unsigned int PPRE12        :1;
// 	unsigned int PPRE20        :1;
// 	unsigned int PPRE21        :1;
// 	unsigned int PPRE22        :1;
// 	unsigned int RTCPRE0       :1;
// 	unsigned int RTCPRE1       :1;
// 	unsigned int RTCPRE2       :1;
// 	unsigned int RTCPRE3       :1;
// 	unsigned int RTCPRE4       :1;
// 	unsigned int MCO10         :1;
// 	unsigned int MCO11         :1;
// 	unsigned int I2SSRC        :1;
// 	unsigned int MCO1PRE0      :1;
// 	unsigned int MCO1PRE1      :1;
// 	unsigned int MCO1PRE2      :1;
// 	unsigned int MCO2PRE0      :1;
// 	unsigned int MCO2PRE1      :1;
// 	unsigned int MCO2PRE2      :1;
// 	unsigned int MCO20         :1;
// 	unsigned int MCO21         :1;
// }RCC_CFGR_bits;
//
// typedef struct {
// 	unsigned int LSIRDYF       :1;
// 	unsigned int LSERDYF       :1;
// 	unsigned int HSIRDYF       :1;
// 	unsigned int HSERDYF       :1;
// 	unsigned int PLLRDYF       :1;
// 	unsigned int PLLI2SRDYF    :1;
// 	unsigned int Reserved      :1;
// 	unsigned int CSSF          :1;
// 	unsigned int LSIRDYIE      :1;
// 	unsigned int LSERDYIE      :1;
// 	unsigned int HSIRDYIE      :1;
// 	unsigned int HSERDYIE      :1;
// 	unsigned int PLLRDYIE      :1;
// 	unsigned int PLLI2SRDYIE   :1;
// 	unsigned int Reserved      :2;
// 	unsigned int LSIRDYC       :1;
// 	unsigned int LSERDYC       :1;
// 	unsigned int HSIRDYC       :1;
// 	unsigned int HSERDYC       :1;
// 	unsigned int PLLRDYC       :1;
// 	unsigned int PLLI2SRDYC    :1;
// 	unsigned int Reserved      :1;
// 	unsigned int CSSC          :1;
// 	unsigned int Reserved      :8;
// }RCC_CIR_bits;          
