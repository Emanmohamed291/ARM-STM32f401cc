#include "RCC.h"

#define RCC_HSI_ENABLE_MASK					0x00000001
#define RCC_HSI_DISABE_MASK					0xFFFFFFFE
#define RCC_HSE_ENABLE_MASK					0x00010000
#define RCC_HSE_DISABE_MASK					0xFFFEFFFF
#define RCC_PLL_ENABLE_MASK					0x01000000
#define RCC_PLL_DISABE_MASK					0xFEFFFFFF
#define RCC_SYSTEM_CLOCK_SELECTION_MASK		0x03

ErrorStatus_t RCC_ControlClock(ClockSystemName_t ClockSystemName, ModeEnum_t Enable_or_Disable){
	ErrorStatus_t ErrorStatusLocVar = RCCOk;
	if(ClockSystemName > ClockSystemPLLI2s){
		ErrorStatusLocVar = RCCClockSystemName;
		}
	else if(Enable_or_Disable > Enable){
		ErrorStatusLocVar = RCCWrongMode;
		}
	else{
		switch(ClockSystemName){
			case ClockSystemHSI:
				switch(Enable_or_Disable){
					case Enable:
						auto Loc_temp = RCC->RCC_CR;
						Loc_temp |=RCC_HSI_ENABLE_MASK;
						RCC->RCC_CR = Loc_temp;
						
					break;
					case Disable:
						auto Loc_temp = RCC->RCC_CR;
						Loc_temp &=RCC_HSI_DISABE_MASK;
						RCC->RCC_CR = Loc_temp;
						break;
					}
				  break;
				
			  case ClockSystemHSE:
			  switch(Enable_or_Disable){
				  case Enable:
					  auto Loc_temp = RCC->RCC_CR;
					  Loc_temp |=RCC_HSE_ENABLE_MASK;
					  RCC->RCC_CR = Loc_temp;
					  
				  break;
				  case Disable:
					  auto Loc_temp = RCC->RCC_CR;
					  Loc_temp &=RCC_HSE_DISABE_MASK;
					  RCC->RCC_CR = Loc_temp;
				  break;
			  }
				break;
				
				case ClockSystemPLL:
				switch(Enable_or_Disable){
					case Enable:
						auto Loc_temp = RCC->RCC_CR;
						Loc_temp |=RCC_PLL_ENABLE_MASK;
						RCC->RCC_CR = Loc_temp;
						
					break;
					case Disable:
						auto Loc_temp = RCC->RCC_CR;
						Loc_temp &=RCC_PLL_DISABE_MASK;
						RCC->RCC_CR = Loc_temp;
					break;
				}
				break;
					
				}
			}
	return ErrorStatusLocVar;
	
}

ErrorStatus_t RCC_SelectSystemClock(ClockSystemName_t ClockSystemName){
	ErrorStatus_t ErrorStatusLocVar = RCCOk;
	if(ClockSystemName > ClockSystemPLLI2s){
		ErrorStatusLocVar = RCCClockSystemName;
	}
	else{
		switch(ClockSystemName){
			case ClockSystemHSI:
				while(!((RCC->RCC_CR >> HSIRDY)|RCC_HSI_ENABLE_MASK));
				auto Loc_temp = RCC->RCC_CFGR;
				Loc_temp & = ~RCC_SYSTEM_CLOCK_SELECTION_MASK;
				Loc_temp | = RCC_HSI_SYSTEM_CLOCK_SELECTION;
				RCC->RCC_CFGR = Loc_temp;
			break;
			case ClockSystemHSE:
				while(!((RCC->RCC_CR >> HSERDY)| RCC_HSI_ENABLE_MASK));
				auto Loc_temp = RCC->RCC_CFGR;
				Loc_temp & = ~RCC_SYSTEM_CLOCK_SELECTION_MASK;
				Loc_temp | = RCC_HSE_SYSTEM_CLOCK_SELECTION;
				RCC->RCC_CFGR = Loc_temp;
			break;
			case ClockSystemPLL:
				while(!((RCC->RCC_CR >> PLLRDY)| RCC_HSI_ENABLE_MASK));
				auto Loc_temp = RCC->RCC_CFGR;
				Loc_temp & = ~RCC_SYSTEM_CLOCK_SELECTION_MASK;
				Loc_temp | = RCC_HSE_SYSTEM_CLOCK_SELECTION;
				RCC->RCC_CFGR = Loc_temp;
		}	
		}
	return ErrorStatusLocVar;			
}

ErrorStatus_t RCC_PLLConfigration(PLL_Source_t PLL_Source, u8 N, u8 M, u8 P){
	ErrorStatus_t ErrorStatusLocVar = RCCOk;
	if(PLL_Source>PLL_Source_HSI){
		ErrorStatusLocVar = RCCWrongPLLSource;
		}
	else if(N<2 || N>432 || M<2){
		ErrorStatusLocVar = RCCWrongPLLConfig;
		}
	else if((P!=2) && (P!=4) && (P!=6) && (P!=8)){
		ErrorStatusLocVar = RCCWrongPLLConfig;
	}
	else{
		auto Loc_temp = RCC->RCC_PLLCFGR;
		Loc_temp   |= (PLL_Source<<PLLSRC);
		Loc_temp   |= (N<<PLLN0);
		Loc_temp   |= (M<<PLLM0);
		Loc_temp   |= (P<<PLLP0);
		RCC->RCC_PLLCFGR = Loc_temp;
		}
	return ErrorStatusLocVar;
}
ErrorStatus_t RCC_PeripheralClock(RCCBusName_t BusName, u8 PeripheralName, ModeEnum_t Enable_or_Disable){
	ErrorStatus_t ErrorStatusLocVar = RCCOk;
	if(BusName > BusAPB2LP){
		ErrorStatusLocVar = RCCWrongBusName;
		}
	else if(PeripheralName > RCC_BITS_NUMBER){
		ErrorStatusLocVar = RCCWrongPeripheralName;
	}
	else if(Enable_or_Disable > Enable){
		ErrorStatusLocVar = RCCWrongMode;
	}
	else{
		switch(Enable_or_Disable){
			case Enable:
				switch(BusName)
				{
					case BusAHB1: 
						auto Loc_temp = RCC->RCC_AHB1ENR;
						Loc_temp   |=(1<<PeripheralName); 
						RCC->RCC_AHB1ENR = Loc_temp;								 
						break;
					case BusAHB2:
						auto Loc_temp = RCC->RCC_AHB2ENR;
						Loc_temp   |=(1<<PeripheralName);
						RCC->RCC_AHB2ENR = Loc_temp;
						break;
					case BusAPB1:
						auto Loc_temp = RCC->RCC_APB1ENR;
						Loc_temp   |=(1<<PeripheralName);
						RCC->RCC_APB1ENR = Loc_temp;
						break;
					case BusAPB2: 
						auto Loc_temp = RCC->RCC_APB2ENR;
						Loc_temp   |=(1<<PeripheralName);
						RCC->RCC_APB2ENR = Loc_temp;
						break;
					case BusAHB1LP: 
						auto Loc_temp = RCC->RCC_AHB1LPENR ;
						Loc_temp   |=(1<<PeripheralName);
						RCC->RCC_AHB1LPENR  = Loc_temp;
						break;
					case BusAHB2LP:
						auto Loc_temp = RCC->RCC_AHB2LPENR ;
						Loc_temp   |=(1<<PeripheralName);
						RCC->RCC_AHB2LPENR  = Loc_temp;
						break;
					case BusAPB1LP:
						auto Loc_temp = RCC->RCC_APB1LPENR ;
						Loc_temp   |=(1<<PeripheralName);
						RCC->RCC_APB1LPENR  = Loc_temp;
						break;
					case BusAPB1LP:
						auto Loc_temp = RCC->RCC_APB2LPENR ;
						Loc_temp   |=(1<<PeripheralName);
						RCC->RCC_APB2LPENR  = Loc_temp;
						break;
					default:
						/* DO NOTHING */
				 }
			break;
			case Disable:
				switch(BusName)
				{
					case BusAHB1:
						auto Loc_temp = RCC->RCC_AHB1ENR ;
						Loc_temp   &=(~(1<<PeripheralName));
						RCC->RCC_AHB1ENR  = Loc_temp;
						break;
					case BusAHB2:
						auto Loc_temp = RCC->RCC_AHB2ENR ;
						Loc_temp   &=(~(1<<PeripheralName));
						RCC->RCC_AHB2ENR  = Loc_temp;
						break;
					case BusAPB1:
						auto Loc_temp = RCC->RCC_APB1ENR ;
						Loc_temp   &=(~(1<<PeripheralName));
						RCC->RCC_APB1ENR  = Loc_temp;
						break;
					case BusAPB2:
						auto Loc_temp = RCC->RCC_APB2ENR ;
						Loc_temp   &=(~(1<<PeripheralName));
						RCC->RCC_APB2ENR  = Loc_temp;
						break;
					case BusAHB1LP:
						auto Loc_temp = RCC->RCC_AHB1LPENR ;
						Loc_temp   &=(~(1<<PeripheralName));
						RCC->RCC_AHB1LPENR  = Loc_temp;
						break;
					case BusAHB2LP:
						auto Loc_temp = RCC->RCC_AHB2LPENR ;
						Loc_temp   &=(~(1<<PeripheralName));
						RCC->RCC_AHB2LPENR  = Loc_temp;
						break;
					case BusAPB1LP:
						auto Loc_temp = RCC->RCC_APB1LPENR ;
						Loc_temp   &=(~(1<<PeripheralName));
						RCC->RCC_APB1LPENR  = Loc_temp;
						break;
					case BusAPB1LP:
						auto Loc_temp = RCC->RCC_APB2LPENR ;
						Loc_temp   &=(~(1<<PeripheralName));
						RCC->RCC_APB2LPENR  = Loc_temp;
						break;
					default:
					/* DO NOTHING */
				}
				break;
		}
		}
	return ErrorStatusLocVar;
}
