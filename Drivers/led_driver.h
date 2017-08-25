/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#ifndef _LED_DIRVER_H_
#define _LED_DIRVER_H_

#include "stm32f10x.h"

#define LED_WHITE_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define LED_BLUE_ON   GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define LED_WHITE_OFF GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LED_BLUE_OFF  GPIO_SetBits(GPIOC,GPIO_Pin_13)

void led_init();

#endif 