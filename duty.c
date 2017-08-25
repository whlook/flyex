/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#include "includes.h"


void duty1ms()
{
	/*
	TIM3->CCR1 = tempup1;
	TIM3->CCR2 = tempup2;
	TIM3->CCR3 = tempup3;
	TIM3->CCR4 = tempup4;
	*/
	/*
	if(distance_ready)
	{
		//Send_Status(ultra_start,ultra_distance_cm,cnt_begin);
		distance_ready = 0;
		LED_BLUE_ON;
	}
	*/
	
	MPU9250_get_data();

	
}

void duty2ms()
{
	
	LED_BLUE_OFF;
}

void duty5ms()
{
	
}

void duty10ms()
{
	Send_Status(mpu_data.acc_x,mpu_data.acc_y,mpu_data.acc_z);
}

void duty20ms()
{

}

void duty1s()
{
	
}
