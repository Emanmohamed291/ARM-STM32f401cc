#include "RCC.h"

#define RCC_HSI_ENABLE_MASK					0x00000001
#define RCC_HSI_DISABE_MASK					0xFFFFFFFE
#define RCC_HSE_ENABLE_MASK					0x00010000
#define RCC_HSE_DISABE_MASK					0xFFFEFFFF
#define RCC_PLL_ENABLE_MASK					0x01000000
#define RCC_PLL_DISABE_MASK					0xFEFFFFFF

#define PLL_PRESCALLER_CONFIG_MASK          0x0003FFFF

#define RCC_SYSTEM_CLOCK_SELECTION_MASK		0xFFFFFFFC



ErrorStatus_t RCC_DesplayClock(u8 ClockSystemName){
	ErrorStatus_t ErrorStatusLocVar = RCC_Ok;
	if(ClockSystemName > 2){//ClockSystemPLLI2s
		ErrorStatusLocVar = RCC_WrongClockSystemName;
	}
	else{
		u32 timeout = 1000000;
		switch(ClockSystemName){
			case RCC_HSI_CLOCK:
				RCC->RCC_CR |=RCC_HSI_ENABLE_MASK;
				while(timeout && !(RCC->RCC_CR & RCC_HSI_READY))
				{
					timeout--;
					if(timeout == 0)
						ErrorStatusLocVar = RCC_TimeOut;
				}
				break;
			case RCC_HSE_CLOCK:
				RCC->RCC_CR |=RCC_HSE_ENABLE_MASK;
				while(timeout && !(RCC->RCC_CR & RCC_HSE_READY))
				{
					timeout--;
					if(timeout == 0)
						ErrorStatusLocVar = RCC_TimeOut;
				}
				break;
			case RCC_PLL_CLOCK:
				RCC->RCC_CR |=RCC_PLL_ENABLE_MASK;
				while(timeout && !(RCC->RCC_CR & RCC_PLL_READY))
				{
					timeout--;
					if(timeout == 0)
						ErrorStatusLocVar = RCC_TimeOut;
				}
				break;
		}
	}
	return ErrorStatusLocVar;

}

ErrorStatus_t RCC_DisableClock(u8 ClockSystemName){
	ErrorStatus_t ErrorStatusLocVar = RCC_Ok;
	if(ClockSystemName > 2){//ClockSystemPLLI2s
		ErrorStatusLocVar = RCC_WrongClockSystemName;
	}
	else{
		switch(ClockSystemName){
			case RCC_HSI_CLOCK:
				RCC->RCC_CR |=RCC_HSI_DISABE_MASK;
				break;
			case RCC_HSE_CLOCK:
				RCC->RCC_CR |=RCC_HSE_DISABE_MASK;
				break;
			case RCC_PLL_CLOCK:
				RCC->RCC_CR |=RCC_PLL_DISABE_MASK;
				break;
		}
	}
	return ErrorStatusLocVar;
	
}
ErrorStatus_t RCC_SelectSystemClock(u8 ClockSystemName){
	ErrorStatus_t ErrorStatusLocVar = RCC_Ok;
	if(ClockSystemName > 2){
		ErrorStatusLocVar = RCC_WrongClockSystemName;
	}
	else{
		u32 Loc_temp;
		switch(ClockSystemName){
			case RCC_HSI_CLOCK:
				Loc_temp = RCC->RCC_CFGR;
				Loc_temp =Loc_temp & RCC_SYSTEM_CLOCK_SELECTION_MASK;
				Loc_temp |= RCC_HSI_CLOCK;
				RCC->RCC_CFGR =(u32)Loc_temp;
			    break;
			case RCC_HSE_CLOCK:
				Loc_temp = RCC->RCC_CFGR;
				Loc_temp &= RCC_SYSTEM_CLOCK_SELECTION_MASK;
				Loc_temp |= RCC_HSE_CLOCK;
				RCC->RCC_CFGR = Loc_temp;
			    break;
			case RCC_PLL_CLOCK:
				Loc_temp = RCC->RCC_CFGR;
				Loc_temp &= RCC_SYSTEM_CLOCK_SELECTION_MASK;
				Loc_temp |= RCC_PLL_CLOCK;
				RCC->RCC_CFGR = Loc_temp;
				break;
		}
	}
	return ErrorStatusLocVar;			
}

ErrorStatus_t RCC_PLLSourceConfigration(u8 PLL_Source){
	ErrorStatus_t ErrorStatusLocVar = RCC_Ok;
	switch(PLL_Source){
		case RCC_HSI_CLOCK:
			if(RCC->RCC_CR & RCC_HSI_READY )
				RCC->RCC_PLLCFGR  |= PLL_Source;
			else
				ErrorStatusLocVar = RCC_WrongPLLSource;
			break;
		case RCC_HSE_CLOCK:
			if(RCC->RCC_CR & RCC_HSE_READY )
				RCC->RCC_PLLCFGR  |= PLL_Source;
			else
				ErrorStatusLocVar = RCC_WrongPLLSource;
			break;
	}
	return ErrorStatusLocVar;
}

ErrorStatus_t RCC_PLLPrescallerConfigration(u16 N, u16 M, u16 P){
	ErrorStatus_t ErrorStatusLocVar = RCC_Ok;
	if(N<2 || N>432 || M<2 || M>63){
		ErrorStatusLocVar = RCC_WrongPLLConfig;
		}
	else if((P!=2) && (P!=4) && (P!=6) && (P!=8)){
		ErrorStatusLocVar = RCC_WrongPLLConfig;
	}
	else{
		u32 Loc_temp = RCC->RCC_PLLCFGR;
		Loc_temp &= PLL_PRESCALLER_CONFIG_MASK;
		Loc_temp  |= (N<<PLLN0)|(M<<PLLM0)|(P<<PLLP0);
		RCC->RCC_PLLCFGR = Loc_temp;
		}
	return ErrorStatusLocVar;
}
ErrorStatus_t RCC_EnablePeripheralClock(RCCBusName_t BusName, u8 PeripheralName){
	ErrorStatus_t ErrorStatusLocVar = RCC_Ok;
	if(BusName > BusAPB2LP){
		ErrorStatusLocVar = RCC_WrongBusName;
		}
	else if(PeripheralName > RCC_BITS_NUMBER){
		ErrorStatusLocVar = RCC_WrongPeripheralName;
	}
	else{
		switch(BusName)
		{
		case BusAHB1:
			RCC->RCC_AHB1ENR |=(1<<PeripheralName);
			break;
		case BusAHB2:
			RCC->RCC_AHB2ENR |=(1<<PeripheralName);
			break;
		case BusAPB1:
			RCC->RCC_APB1ENR |=(1<<PeripheralName);
			break;
		case BusAPB2:
			RCC->RCC_APB2ENR |=(1<<PeripheralName);
			break;
		case BusAHB1LP:
			RCC->RCC_AHB1LPENR |=(1<<PeripheralName);
			break;
		case BusAHB2LP:
			RCC->RCC_AHB2LPENR |=(1<<PeripheralName);
			break;
		case BusAPB1LP:
			RCC->RCC_APB1LPENR |=(1<<PeripheralName);
			break;
		case BusAPB2LP:
			RCC->RCC_APB2LPENR |=(1<<PeripheralName);
			break;
		}
	}
	return ErrorStatusLocVar;
}

ErrorStatus_t RCC_DisablePeripheralClock(RCCBusName_t BusName, u8 PeripheralName){
	ErrorStatus_t ErrorStatusLocVar = RCC_Ok;
	if(BusName > BusAPB2LP){
		ErrorStatusLocVar = RCC_WrongBusName;
		}
	else if(PeripheralName > RCC_BITS_NUMBER){
		ErrorStatusLocVar = RCC_WrongPeripheralName;
	}
	else{
		switch(BusName)
		{
			case BusAHB1:
				RCC->RCC_AHB1ENR   &=(~(1<<PeripheralName));
				break;
			case BusAHB2:
				RCC->RCC_AHB2ENR  &=(~(1<<PeripheralName));
				break;
			case BusAPB1:
				RCC->RCC_APB1ENR &=(~(1<<PeripheralName));
				break;
			case BusAPB2:
				RCC->RCC_APB2ENR &=(~(1<<PeripheralName));
				break;
			case BusAHB1LP:
				RCC->RCC_AHB1LPENR  &=(~(1<<PeripheralName));
				break;
			case BusAHB2LP:
				RCC->RCC_AHB2LPENR &=(~(1<<PeripheralName));
				break;
			case BusAPB1LP:
				RCC->RCC_APB1LPENR  &=(~(1<<PeripheralName));
				break;
			case BusAPB2LP:
				RCC->RCC_APB2LPENR  &=(~(1<<PeripheralName));
				break;
		}
	}
	return ErrorStatusLocVar;
}
