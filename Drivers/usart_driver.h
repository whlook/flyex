/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#ifndef _USART_DRIVER_H_
#define _USART_DRIVER_H_

#include "stm32f10x.h"

void USART1_Init(int baud);
void USART2_Init(int baud);

void USART1_sendData(unsigned char * tx_data_buf,unsigned char length);  
void USART2_sendData(unsigned char * tx_data_buf,unsigned char length); 

unsigned char  USART1_recData(void);
unsigned char  USART2_recData(void);


#endif