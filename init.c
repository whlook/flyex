/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#include "includes.h"

void init_all()
{
	led_init();
	
	USART1_Init(9600);

	LED_WHITE_ON;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//TIM4_Cap_Init(0xffff,72-1);
	
	//TIM3_PWM_Init(0xffff,72-1);
	
	//ultra_Init();
	
	I2C1_Init();
	MPU9250_init();
	
	LED_BLUE_ON;
	delay_ms_soft(300);
	LED_BLUE_OFF;
	delay_ms_soft(300);
	LED_BLUE_ON;
	delay_ms_soft(300);
	LED_BLUE_OFF;
	delay_ms_soft(1000);
	LED_BLUE_ON;
	
//	delay_ms_soft(5000);

	sys_time_init();
}