/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/

#include "includes.h"


void I2C1_Init()
{
	I2C_InitTypeDef I2C1_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	/*   GPIOB 6,7 Config  */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	I2C1_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C1_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C1_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C1_InitStruct.I2C_ClockSpeed = 50000;
	I2C_Init(I2C1,&I2C1_InitStruct);
	
	I2C_Cmd(I2C1,ENABLE);
	I2C_AcknowledgeConfig(I2C1,ENABLE);
	
}


void I2C2_Init()
{
	I2C_InitTypeDef I2C2_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	/*   GPIOB 10,11 Config  */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	I2C2_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C2_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C2_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C2_InitStruct.I2C_ClockSpeed = 50000;
	I2C_Init(I2C2,&I2C2_InitStruct);
	
	I2C_Cmd(I2C1,ENABLE);
	I2C_AcknowledgeConfig(I2C2,ENABLE);
}

/*==========================================================================================================

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *===========================================================================================================*/
unsigned char I2C1_ByteWrite(unsigned char slave_address,unsigned char data_to_write_in)
{
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Transmitter);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1,data_to_write_in);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	return 1;
}

unsigned char I2C1_ByteWrite_Reg( unsigned char slave_address,unsigned char reg_address,unsigned char data_to_write_in)
{
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Transmitter);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1,reg_address);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2C1,data_to_write_in);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	return 1;
}

/*=============================================================================================================

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=============================================================================================================*/
unsigned char I2C2_ByteWrite(unsigned char slave_address,unsigned char data_to_write_in)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Transmitter);              
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2,data_to_write_in);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	return 1;
}

unsigned char I2C2_ByteWrite_Reg( unsigned char slave_address,unsigned char reg_address,unsigned char data_to_write_in)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Transmitter);              
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2,reg_address);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2C2,data_to_write_in);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	return 1;
}


/*========================================================================================================

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *==========================================================================================================*/
unsigned char I2C1_ByteRead(unsigned char slave_address)
{
	unsigned char data_read;
	
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Receiver);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_AcknowledgeConfig(I2C1,DISABLE);
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	data_read = I2C_ReceiveData(I2C1);
	
	return data_read; 

}

unsigned char I2C1_ByteRead_Reg(unsigned char slave_address,unsigned char reg_address)
{
	unsigned char data_read;
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Transmitter);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_Cmd(I2C1,ENABLE);
	
	I2C_SendData(I2C1,reg_address);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
//----------------------------------------------------------------------+
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Receiver);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_AcknowledgeConfig(I2C1,DISABLE);
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	data_read = I2C_ReceiveData(I2C1);
	
	return data_read;
}

/*===============================================================================================================

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *===============================================================================================================*/
unsigned char I2C2_ByteRead(unsigned char slave_address)
{
	unsigned char data_read;
	
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Receiver);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	data_read = I2C_ReceiveData(I2C2);
	
	return data_read; 

}

unsigned char I2C2_ByteRead_Reg(unsigned char slave_address,unsigned char reg_address)
{
	unsigned char data_read;
	
	while(I2C_GetFlagStatus(I2C2,I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Transmitter);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_Cmd(I2C2,ENABLE);
	
	I2C_SendData(I2C2,reg_address);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
//-------------------------------------------------------------+
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Receiver);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	data_read = I2C_ReceiveData(I2C2);
	
	return data_read;
}