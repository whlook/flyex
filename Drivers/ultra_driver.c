/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#include "includes.h"

u16 ultra_distance_cm = 0;

 u8 ultra_start = 0;

 u8 cnt_begin = 0;
 
 u8 distance_ready = 0;
 
static u32 safe_cnt = 0; 

static u32 sysTickCnt_temp = 0;

static u8 emit_cnt = 0;


/**
	*  echo -- PB6
	*  trig -- PB7
	*
	*/
void ultra_Init()
{
	GPIO_InitTypeDef GPIO_Struct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_Struct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_Struct);
	
	GPIO_Struct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_Struct);
	
}



void ultra_get_distance()
{
	if(ultra_start == 0)
	{
		Ultra_Send_Start;
		emit_cnt++;
		if(emit_cnt>1)
		{
			Ultra_Send_Stop;
			emit_cnt = 0;
			ultra_start = 1;
		}

	}
}


void ultra_check()
{
	if(ultra_start == 1)
	{
		if(cnt_begin == 0)
		{
			safe_cnt++;
			if(safe_cnt>6000)
			{
				safe_cnt = 0;
				ultra_start = 0;
				return;
			}
		}
		else
		{
			safe_cnt = 0;
		}
		
		if(Ultra_Rec_Check == 1 && cnt_begin == 0)
		{
			sysTickCnt_temp = sysTickCnt;
			cnt_begin = 1;
			LED_WHITE_ON;
		}
		if(Ultra_Rec_Check == 0 && cnt_begin == 1)
		{
			ultra_distance_cm = (sysTickCnt-sysTickCnt_temp)*0.17;
			distance_ready = 1;
			
			ultra_start = 0;
			cnt_begin = 0;
			
			LED_WHITE_OFF;
		}
	}
}