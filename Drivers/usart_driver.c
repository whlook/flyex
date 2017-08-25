/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#include "includes.h"

static unsigned char usart1_rx_flag = 0xff;
static unsigned char usart2_rx_flag = 0xff;
static unsigned char usart1_com_data = 0x00;
static unsigned char usart2_com_data = 0x00;

int fputc(int ch, FILE *f)
{ 	
	USART_SendData(USART1,(u8)ch);
	while(!(USART1->SR&USART_FLAG_TXE));
	return ch;
}
//---------------------------------------------------------------------------------------------------+
void USART1_Init(int baud)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef  GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	/*******PA9 configuration****** usart tx  **/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	/*******PA10 configuration******* usart rx **/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStruct.USART_BaudRate = baud; // 波特率 
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 7位数据位和一个可能的校验位
	USART_InitStruct.USART_StopBits = USART_StopBits_1; // 1个停止位
	USART_InitStruct.USART_Parity = USART_Parity_No; // 关闭奇偶校验
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 关闭硬件流控制
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1,&USART_InitStruct);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE); // 使能
	
}

//-----------------------------------------------------------------------------------------------------+
void USART2_Init(int baud)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef  GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	/*******PA2 configuration****** usart tx  **/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	/*******PA3 configuration******* usart rx **/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStruct.USART_BaudRate = baud; // 波特率 
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 7位数据位和一个可能的校验位
	USART_InitStruct.USART_StopBits = USART_StopBits_1; // 1个停止位
	USART_InitStruct.USART_Parity = USART_Parity_No; // 关闭奇偶校验
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 关闭硬件流控制
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART2,&USART_InitStruct);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE); // 使能
}

//---------------------------------------------------------------------------------------------+
void USART1_sendData(unsigned char * tx_data_buf,unsigned char length)
{
	int i;
	USART_ITConfig(USART1,USART_IT_TXE,DISABLE); // disable tx interrupt
	for(i = 0;i<length;i++)
	{
		USART_SendData(USART1,tx_data_buf[i]);
		while(!(USART1->SR&USART_FLAG_TXE)); // wait for the tx reg empty
	}
}

//----------------------------------------------------------------------------------------------+
void USART2_sendData(unsigned char * tx_data_buf,unsigned char length)
{
	int i;
	USART_ITConfig(USART2,USART_IT_TXE,DISABLE); // disable tx interrupt
	for(i = 0;i<length;i++)
	{
		USART_SendData(USART2,tx_data_buf[i]);
		while(!(USART2->SR&USART_FLAG_TXE)); // wait for the tx reg empty
	}
}
//----------------------------------------------------------------------------------------------+
unsigned char  USART1_recData(void)
{
	if(usart1_rx_flag == 0x00)
	{
		usart1_rx_flag = 0xff;
		return usart1_com_data;
	}
	else
	{
		return 0xff;
	}
}
//----------------------------------------------------------------------------------------------+
unsigned char  USART2_recData(void)
{
	if(usart2_rx_flag == 0x00)
	{
		usart2_rx_flag = 0xff;
		return usart2_com_data;
	}
	else
	{
		return 0xff;
	}
}

//////////////////////////////////////////////////////////////////////////////////////
void USART1_IRQHandler(void)
{
	
	if(USART1->SR & USART_IT_ORE)
	{
		usart1_com_data = USART1->SR;
	}
	//发送中断
	if(USART_GetITStatus(USART1,USART_IT_TXE))
	{
		USART1->DR = 0x01; //写DR清除中断标志 
		USART1->CR1 &= ~USART_CR1_TXEIE;		//关闭TXE中断
	}
	
	//接收中断（接收寄存器非空）
	if(USART_GetITStatus(USART1, USART_IT_RXNE))    
	{
		usart1_com_data = USART1->DR;
		usart1_rx_flag = 0x00;

		
	}
	
}

//-------------------------------------------------------------------------+
void USART2_IRQHandler(void)
{
	
	if(USART2->SR & USART_IT_ORE)
	{
		usart2_com_data = USART2->SR;
	}
	//发送中断
	if(USART_GetITStatus(USART2,USART_IT_TXE))
	{
		USART2->DR = 0x01; //写DR清除中断标志 
		USART2->CR1 &= ~USART_CR1_TXEIE;		//关闭TXE中断
	}
	
	//接收中断（接收寄存器非空）
	if(USART_GetITStatus(USART2, USART_IT_RXNE))    
	{
		usart2_com_data = USART2->DR;
		usart2_rx_flag = 0x00;

		
	}
	
}