/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#include "sys.h"

extern u32 tempup1;	//捕获总高电平的时间
extern u32 tempup2;	//捕获总高电平的时间
extern u32 tempup3;	//捕获总高电平的时间
extern u32 tempup4;	//捕获总高电平的时间

void TIM4_Cap_Init(u16 arr, u16 psc); // PWM输入


void TIM3_PWM_Init(u16 arr,u16 psc); // PWM输出
