#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx.h"

extern uint8_t tim6_count;

void delay(int n);


void delay(int n)
{
while(n > 0) n--;
}	


#endif /*MAIN_H_*/
