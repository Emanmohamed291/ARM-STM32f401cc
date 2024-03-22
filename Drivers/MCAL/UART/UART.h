/*
 * USART.h
 *
 * Created: 22/3/2024 5:53:43 PM
 *  Author: Eman
 */ 


#ifndef USART_H_
#define USART_H_

/************************************************************************************
 *                                       datatypes                                  *
 * **********************************************************************************/
typedef unsigned char         u8;
typedef signed char           s8;
typedef short unsigned int    u16;
typedef short signed int      s16;
typedef unsigned int          u32;
typedef signed int            s32;
typedef unsigned long long int u64;

typedef enum
{
	USART_Ok,
	USART_WRONGCHANNEL,
	USART_NULLPOINTER,
    USART_wrongchannel,
	USART_WRONGFREQ,
    USART_BUSY
}USART_ErrorStatus_t;

typedef struct {
    u8 Channel;
    u8 Oversampling_mode;
    u8 USART_enable;
    u8 Word_length;
    u8 Wakeup_method;
    u8 Parity_control_enable;
    u8 Parity_selection;
    u8 PE_interrupt_enable;
    u8 TXE_interrupt_enable;
    u8 Transmission_complete_interrupt_enable;
    u8 RXNE_interrupt_enable;
    u8 IDLE_interrupt_enable;
    u8 Transmitter_enable;
    u8 Receiver_enable;
    u8 Receiver_wakeup;
    u8 Send_break;
    u8 STOP_bits;
    u16 baudrate;

}USART_Config_t;

typedef enum
{
	USART1_channel,
	USART2_channel,
	USART6_channel

}USART_Channels_t;

typedef struct
{
    u8* data;
    u32 pos;
    u32 size;
}USART_buffer_t;

typedef void(*TxCB)(void);
/************************************************************************************
 *                                       #defines                                  *
 * **********************************************************************************/
#define NUMBER_OF_USART                  3
#define F_CLK	                         16000000

#define USART_ENABLE                      1
#define USART_DISABLE                     0

#define USART_FINISH                      1
#define USART_NOT_FINISH                  0

u8 USART1_Finish_Receiving = USART_NOT_FINISH;
u8 USART2_Finish_Receiving = USART_NOT_FINISH;
u8 USART6_Finish_Receiving = USART_NOT_FINISH;
/************************************************************************************
 *                                       functions                                  *
 * **********************************************************************************/

USART_ErrorStatus_t USART_Init(const USART_Config_t* ConfigPtr);
USART_ErrorStatus_t USART_SendByteAsynch(USART_Channels_t Channel, u8* buffer, u8 length, TxCB cb);
USART_ErrorStatus_t USART_ReceiveByteAsynch(USART_Channels_t Channel, u8* buffer, u8 length, TxCB cb);


#endif /* USART_H_ */