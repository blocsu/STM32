#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx.h"
#include "init.h"
//#include "timers.h"
//#include "usart.h"
#include "LED_init.h"
//#include "DAC.h"
//#include "ADC.h"
#include "encoder.h"
#include "stdio.h"
#include "Lab12_Test.h"

static uint16_t delay_count=0;

//void delay_ms(int n);

//void delay_ms(int n)
//{
//while(n > 0) n--;
//}

void delay_ms(uint16_t delay_temp);
void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;
	
	while(delay_count){}
}

#endif /*MAIN_H_*/
