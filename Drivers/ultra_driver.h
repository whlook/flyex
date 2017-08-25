#pragma ONCE
#include "stm32f10x.h"

#define Trig GPIO_Pin_7
#define Echo GPIO_Pin_6

#define Ultra_Send_Start GPIO_SetBits(GPIOB,Trig)
#define Ultra_Send_Stop  GPIO_ResetBits(GPIOB,Trig)

#define Ultra_Rec_Check  GPIO_ReadInputDataBit(GPIOB,Echo)

extern u16 ultra_distance_cm;

extern u8 ultra_start;
extern u8 cnt_begin;

extern u8 distance_ready;

 
void ultra_Init();

void ultra_get_distance();

void ultra_check();
