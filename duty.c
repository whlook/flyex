/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#include "includes.h"


void duty1ms()
{
	
	TIM3->CCR1 = tempup1;
	TIM3->CCR2 = tempup2;
	TIM3->CCR3 = tempup3;
	TIM3->CCR4 = tempup4;
	

	
	//MPU9250_get_data();

	
}

void duty2ms()
{
	
}

void duty5ms()
{
	
}

void duty10ms()
{
	
}

void duty20ms()
{

}

void duty1s()
{
	
}
