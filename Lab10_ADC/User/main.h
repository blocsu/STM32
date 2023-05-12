#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx.h"
#include "init.h"
//#include "timers.h"
//#include "usart.h"
//#include "LED_init.h"
#include "DAC.h"
#include "ADC.h"
#include "stdio.h"
#include "Lab10_test.h"

void delay_ms(int n);

void delay_ms(int n)
{
while(n > 0) n--;
}

#endif /*MAIN_H_*/
