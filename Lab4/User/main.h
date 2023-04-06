#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx.h"

extern uint8_t tim6_count;
extern uint8_t User_Button;
extern uint16_t Count_Of_Button;
extern uint8_t Button_State;
extern uint8_t Flag;

void delay(int n);


void delay(int n)
{
while(n > 0) n--;
}	


#endif /*MAIN_H_*/
