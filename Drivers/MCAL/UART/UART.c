/*
* USART.c
*
* Created: 22/3/2024 12:58:15 AM
*  Author: Eman
*/

#include "UART.h"

/************************************************************************************
 *                                       datatypes                                  *
 * **********************************************************************************/
typedef struct
{
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_CR4;

}USART_Registers_t;

typedef struct{
    u8 parity_error;
    u8  transmission_complete;
    u8 transmit_empty;
    u8 read_empty;
}interrupt_status;



struct{
    USART_buffer_t buffer;
    u32 state;
    TxCB cb;
}TXReq[NUMBER_OF_USART];

    

enum{
    SBK,
    RWU,
    RE,
    TE,
    IDLEIE,
    RXNEIE,
    TCIE,
    TXEIE,
    PEIE,
    PS,
    PCE,
    WAKE,
    M,
    UE,
    OVER8=15
}USART_ctrl_pins;

enum{
    PE,
    FE,
    NF, 
    ORE,
    IDLE,
    RXNE,
    TC,
    TXE,
    LBD,
    CTS 
}USART_SR_pins;
/************************************************************************************
 *                                       #defines                                  *
 * **********************************************************************************/
#define USART1           	                       ((USART_Registers_t*)0x40011000)
#define USART2           	                       ((USART_Registers_t*)0x40004400)
#define USART6           	                       ((USART_Registers_t*)0x40011400)

#define NULL                                       ((void *)0)

#define oversampling_by_16                          0x00008000
#define oversampling_by_8                           0x00000000

#define USART_MASK_TXEIE_ENABLE                     0X00000080
#define USART_MASK_TXEIE_DISABLE                    0XFFFFFF7F
#define USART1_READY_BIT                            0b00000001
#define USART_Busy                                  1
#define USART_Ready                                 0
/************************************************************************************
 *                                       variables                                  *
 * **********************************************************************************/
/* variable to save interrupt status which is enable and disable 
for the config of the parameter of the init function*/
//static interrupt_status interrupt[NUMBER_OF_USART];

/************************************************************************************
 *                                       functions                                  *
 * **********************************************************************************/

USART_ErrorStatus_t USART_Init(const USART_Config_t* ConfigPtr){
    USART_ErrorStatus_t ErrorStatusLocVar = USART_Ok;
    u32 Loc_u32TempValue;
    u16 Loc_u16TempFraction;
    u16 Loc_u16TempMantissa;

    if(ConfigPtr == NULL)
	{
		ErrorStatusLocVar = USART_NULLPOINTER;
	}
    else if(F_CLK >84000000){
        ErrorStatusLocVar = USART_WRONGFREQ;
    }
    else{
        /* DIV and Fracion */
        Loc_u32TempValue = ((u64)F_CLK * 1000) / (ConfigPtr->baudrate * (8 * (2 - ConfigPtr->Oversampling_mode)));
        /* in O.S 8 so it has 3 bit fraction and in O.S 16 so it has 4 bit fraction */
        Loc_u16TempFraction = (Loc_u32TempValue % 1000) * (8 * (2 - ConfigPtr->Oversampling_mode));
		Loc_u16TempFraction = Loc_u16TempFraction / 1000;
        /* mantisa value */
        Loc_u16TempMantissa = Loc_u32TempValue / 1000;
        /* fraction */
        if(ConfigPtr->Oversampling_mode ==  oversampling_by_16){
            /* if fraction >16 which mean more than 4 bits for fraction */
            if(Loc_u16TempFraction > 0xF)
            {
                Loc_u16TempMantissa++;
                Loc_u16TempFraction = 0;
            } 
        }
        else if(ConfigPtr->Oversampling_mode ==  oversampling_by_8){
            /* if fraction >8 which mean more than 3 bits for fraction */
            if(Loc_u16TempFraction > 0x7)
            {
                Loc_u16TempMantissa++;
                Loc_u16TempFraction = 0;
            } 
        }
        TXReq[USART1_channel].state = USART_Ready;
        TXReq[USART2_channel].state = USART_Ready;
        TXReq[USART6_channel].state = USART_Ready;

        switch (ConfigPtr->Channel)
        {
        case USART1_channel:
            /* baudrate reg */
			USART1->USART_BRR = (Loc_u16TempMantissa << 4) | (Loc_u16TempFraction & 0x0F);
            /* because usart is off so i can use reg direct not in need to temp var 
               because i use struct so i didn't use macros u32 because struct size will be over*/
            USART1->USART_CR1 = 0;
            USART1->USART_CR1 |= (ConfigPtr->Oversampling_mode<<OVER8);
            USART1->USART_CR1 |= (ConfigPtr->Word_length<<M);
            USART1->USART_CR1 |= (ConfigPtr->Wakeup_method<<WAKE);
            USART1->USART_CR1 |= (ConfigPtr->Parity_control_enable<<PCE);
            USART1->USART_CR1 |= (ConfigPtr->Parity_selection<<PS);
            USART1->USART_CR1 |= (ConfigPtr->Transmitter_enable<<TE);
            USART1->USART_CR1 |= (ConfigPtr->Receiver_enable<<RE);
            /* interrupt status */
            // interrupt[USART1_channel].parity_error = (ConfigPtr->Receiver_enable<<PEIE);
            // interrupt[USART1_channel].read_empty = (ConfigPtr->Receiver_enable<<RXNEIE);
            // interrupt[USART1_channel].transmit_empty = (ConfigPtr->Receiver_enable<<TXEIE);
            // interrupt[USART1_channel].transmission_complete = (ConfigPtr->Receiver_enable<<TCIE);
            /* clear status reg */
            USART1->USART_SR = 0;
            /* enable USART1 */
            USART1->USART_CR1 |= (ConfigPtr->USART_enable<<UE);
        break;
        case USART2_channel:
            /* baudrate reg */
			USART2->USART_BRR = (Loc_u16TempMantissa << 4) | (Loc_u16TempFraction & 0x0F);
            /* because usart is off so i can use reg direct not in need to temp var 
               because i use struct so i didn't use macros u32 because struct size will be over*/
            USART2->USART_CR1 = 0;
            USART2->USART_CR1 |= (ConfigPtr->Oversampling_mode<<OVER8);
            USART2->USART_CR1 |= (ConfigPtr->Word_length<<M);
            USART2->USART_CR1 |= (ConfigPtr->Wakeup_method<<WAKE);
            USART2->USART_CR1 |= (ConfigPtr->Parity_control_enable<<PCE);
            USART2->USART_CR1 |= (ConfigPtr->Parity_selection<<PS);
            USART2->USART_CR1 |= (ConfigPtr->Transmitter_enable<<TE);
            USART2->USART_CR1 |= (ConfigPtr->Receiver_enable<<RE);
             /* interrupt status */
            // interrupt[USART2_channel].parity_error = (ConfigPtr->Receiver_enable<<PEIE);
            // interrupt[USART2_channel].read_empty = (ConfigPtr->Receiver_enable<<RXNEIE);
            // interrupt[USART2_channel].transmit_empty = (ConfigPtr->Receiver_enable<<TXEIE);
            // interrupt[USART2_channel].transmission_complete = (ConfigPtr->Receiver_enable<<TCIE);
            /* clear status reg */
            USART2->USART_SR = 0;
            /* enable USART2 */
            USART2->USART_CR1 |= (ConfigPtr->USART_enable<<UE);
        break;
        case USART6_channel:
            /* baudrate reg */
			USART6->USART_BRR = (Loc_u16TempMantissa << 4) | (Loc_u16TempFraction & 0x0F);
            /* because usart is off so i can use reg direct not in need to temp var 
               because i use struct so i didn't use macros u32 because struct size will be over*/
            USART6->USART_CR1 = 0;
            USART6->USART_CR1 |= (ConfigPtr->Oversampling_mode<<OVER8);
            USART6->USART_CR1 |= (ConfigPtr->Word_length<<M);
            USART6->USART_CR1 |= (ConfigPtr->Wakeup_method<<WAKE);
            USART6->USART_CR1 |= (ConfigPtr->Parity_control_enable<<PCE);
            USART6->USART_CR1 |= (ConfigPtr->Parity_selection<<PS);
            USART6->USART_CR1 |= (ConfigPtr->Transmitter_enable<<TE);
            USART6->USART_CR1 |= (ConfigPtr->Receiver_enable<<RE);
            
             /* interrupt status */
            // interrupt[USART6_channel].parity_error = (ConfigPtr->Receiver_enable<<PEIE);
            // interrupt[USART6_channel].read_empty = (ConfigPtr->Receiver_enable<<RXNEIE);
            // interrupt[USART6_channel].transmit_empty = (ConfigPtr->Receiver_enable<<TXEIE);
            // interrupt[USART6_channel].transmission_complete = (ConfigPtr->Receiver_enable<<TCIE);
            /* clear status reg */
            USART6->USART_SR = 0;
            /* enable USART6 */
            USART6->USART_CR1 |= (ConfigPtr->USART_enable<<UE);
        break;
        default:
            ErrorStatusLocVar = USART_WRONGCHANNEL;
        break;
        }       
    }
    return ErrorStatusLocVar;
}

/************************************************* send byte **************************************/
USART_ErrorStatus_t USART_SendByteAsynch(USART_Channels_t Channel, u8* buffer, u8 length, TxCB cb){
    USART_ErrorStatus_t ErrorStatusLocVar = USART_Ok;
    if(buffer == NULL || cb== NULL ){
        ErrorStatusLocVar = USART_NULLPOINTER;
    }
    else{
        switch (Channel)
        {
        case USART1_channel:
            /* make TXEIE --> 1*/
            USART1->USART_CR1 |= USART_MASK_TXEIE_ENABLE;
            if(TXReq[USART1_channel].state == USART_Ready){
                TXReq[USART1_channel].state = USART_Busy;
            }
            else{
                ErrorStatusLocVar = USART_BUSY;
            }
            TXReq[USART1_channel].buffer.data = buffer;
            TXReq[USART1_channel].buffer.size = length;
            TXReq[USART1_channel].buffer.pos = 0;
            TXReq[USART1_channel].cb = cb;
            USART1->USART_DR = TXReq[USART1_channel].buffer.data[0];
            TXReq[USART1_channel].buffer.pos++;
        break;
        case USART2_channel:
            USART2->USART_CR1 |= USART_MASK_TXEIE_ENABLE;
            if(TXReq[USART2_channel].state == USART_Ready){
                TXReq[USART2_channel].state = USART_Busy;
            }
            TXReq[USART2_channel].buffer.data = buffer;
            TXReq[USART2_channel].buffer.size = length;
            TXReq[USART2_channel].buffer.pos = 0;
            TXReq[USART2_channel].cb = cb;
            USART2->USART_DR = TXReq[USART2_channel].buffer.data[0];
            TXReq[USART2_channel].buffer.pos++;
        break;
        case USART6_channel:
            USART6->USART_CR1 |= USART_MASK_TXEIE_ENABLE;
            if(TXReq[USART6_channel].state == USART_Ready){
                TXReq[USART6_channel].state = USART_Busy;
            }
            TXReq[USART6_channel].buffer.data = buffer;
            TXReq[USART6_channel].buffer.size = length;
            TXReq[USART6_channel].buffer.pos = 0;
            TXReq[USART6_channel].cb = cb;
            USART6->USART_DR = TXReq[USART6_channel].buffer.data[0];
            TXReq[USART6_channel].buffer.pos++;
        break;
        
        default:
            ErrorStatusLocVar = USART_wrongchannel;
        break;
        }
    }
    
    return ErrorStatusLocVar;
}

void USART1_IRQHandler(void){
    if((USART1->USART_SR >> TXE) & 0x01){//(USART1->USART_SR >> TC) & 0x01
        if(TXReq[USART1_channel].buffer.pos < TXReq[USART1_channel].buffer.size){
            u32 index = TXReq[USART1_channel].buffer.pos;
            USART1->USART_DR = TXReq[USART1_channel].buffer.data[index];
            TXReq[USART1_channel].buffer.pos++;
        }
        else{
            TXReq[USART1_channel].state = USART_Ready;
            if(TXReq[USART1_channel].cb){
                TXReq[USART1_channel].cb();
            }
        }
    }
    if((USART1->USART_SR >> RXNE) & 0x01){
        if(TXReq[USART1_channel].buffer.pos < TXReq[USART1_channel].buffer.size){
            u32 index = TXReq[USART1_channel].buffer.pos;
            TXReq[USART1_channel].buffer.data[index] = USART1->USART_DR;
            TXReq[USART1_channel].buffer.pos++;
        }
        else if(TXReq[USART1_channel].buffer.pos == TXReq[USART1_channel].buffer.size){
            TXReq[USART1_channel].state = USART_Ready;
            TXReq[USART1_channel].buffer.pos = 0;
            TXReq[USART1_channel].buffer.size = 0;
            USART1_Finish_Receiving = USART_FINISH;
        }
    }
}

void USART2_IRQHandler(void){
	if((USART2->USART_SR >> TXE) & 0x01){//(USART2->USART_SR >> TC) & 0x01
		if(TXReq[USART2_channel].buffer.pos < TXReq[USART2_channel].buffer.size){
			u32 index = TXReq[USART2_channel].buffer.pos;
			USART2->USART_DR = TXReq[USART2_channel].buffer.data[index];
			TXReq[USART2_channel].buffer.pos++;
		}
		else{
			TXReq[USART2_channel].state = USART_Ready;
			if(TXReq[USART2_channel].cb){
				TXReq[USART2_channel].cb();
			}
		}
	}
	if((USART2->USART_SR >> RXNE) & 0x01){
		if(TXReq[USART2_channel].buffer.pos < TXReq[USART2_channel].buffer.size){
			u32 index = TXReq[USART2_channel].buffer.pos;
			TXReq[USART2_channel].buffer.data[index] = USART2->USART_DR;
			TXReq[USART2_channel].buffer.pos++;
		}
		else if(TXReq[USART2_channel].buffer.pos == TXReq[USART2_channel].buffer.size){
			TXReq[USART2_channel].state = USART_Ready;
			TXReq[USART2_channel].buffer.pos = 0;
			TXReq[USART2_channel].buffer.size = 0;
			USART2_Finish_Receiving = USART_FINISH;
		}
	}
}

void USART6_IRQHandler(void){
	if((USART6->USART_SR >> TXE) & 0x01){//(USART6->USART_SR >> TC) & 0x01
		if(TXReq[USART6_channel].buffer.pos < TXReq[USART6_channel].buffer.size){
			u32 index = TXReq[USART6_channel].buffer.pos;
			USART6->USART_DR = TXReq[USART6_channel].buffer.data[index];
			TXReq[USART6_channel].buffer.pos++;
		}
		else{
			TXReq[USART6_channel].state = USART_Ready;
			if(TXReq[USART6_channel].cb){
				TXReq[USART6_channel].cb();
			}
		}
	}
	if((USART6->USART_SR >> RXNE) & 0x01){
		if(TXReq[USART6_channel].buffer.pos < TXReq[USART6_channel].buffer.size){
			u32 index = TXReq[USART6_channel].buffer.pos;
			TXReq[USART6_channel].buffer.data[index] = USART6->USART_DR;
			TXReq[USART6_channel].buffer.pos++;
		}
		else if(TXReq[USART6_channel].buffer.pos == TXReq[USART6_channel].buffer.size){
			TXReq[USART6_channel].state = USART_Ready;
			TXReq[USART6_channel].buffer.pos = 0;
			TXReq[USART6_channel].buffer.size = 0;
			USART6_Finish_Receiving = USART_FINISH;
		}
	}
}

