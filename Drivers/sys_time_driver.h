/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#ifndef _SYS_TIME_DRIVER_H_
#define _SYS_TIME_DRIVER_H_

#include "stm32f10x.h"


//----- externs ------//

extern u32 sysTickCnt;

//--------------------//
 

void sys_time_init();
void delay_ms_soft(u16 nms);
void delay_ms(u16 nms);
void heart_beat();

#endif