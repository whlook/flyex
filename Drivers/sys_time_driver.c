/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#include "includes.h"

//------ global -------//
 u32 sysTickCnt = 0;

static u16 timeCnt1ms  = 0;
static u16 timeCnt2ms  = 0;
static u16 timeCnt5ms  = 0;
static u16 timeCnt10ms = 0;
static u16 timeCnt20ms = 0;

//----------------------//

uint32_t GetSysTime_us(void) 
{
	register uint32_t us;
	u32 value;
	us = sysTickCnt;
	value = us + (SysTick->LOAD - SysTick->VAL) / SysTick->LOAD;
	return value;
}

void sys_time_init()
{
	while(SysTick_Config(SystemCoreClock/100000)); // 10us
	NVIC_SetPriority(SysTick_IRQn,1);
}

void delay_ms_soft(u16 nms)
{	
	
	uint16_t i,j;
	
	for(i=0;i<nms;i++)
	
		for(j=0;j<8500;j++);
	
} 

static void delay_us(u16 us)
{
	u32 temp = sysTickCnt;
	while((sysTickCnt-temp)<us);
}


void delay_ms(u16 nms)
{
		for(u16 i = 0;i<nms;i++)
		delay_us(100);
}


/*=================================================*

	author: 
	version: 2017-8-9
	input: 
	output: 
	description: system duty (main),beat every 10 us

 *=================================================*/
void heart_beat()
{
	
	timeCnt1ms++;
	timeCnt2ms++;
	timeCnt5ms++;
	timeCnt10ms++;
	
//	ultra_get_distance();
//	ultra_check();
	
	if(timeCnt1ms==100)
	{
		timeCnt1ms = 0;
		duty1ms(); // run every 1ms
	}
	if(timeCnt2ms == 200)
	{
		timeCnt2ms = 0;
		duty2ms(); // run every 2ms
	}
	if(timeCnt5ms == 500)
	{
		timeCnt5ms = 0;
		duty5ms(); // run every 5ms
	}
	if(timeCnt10ms == 1000)
	{
		timeCnt10ms = 0;
		duty10ms(); // run every 10ms
	}

	
}