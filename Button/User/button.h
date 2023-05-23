#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32f4xx.h"

#define BUTTON_READ()			GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

void button_ini(void);
void Button_Read(void);
uint8_t get_Button_Press(void);

#endif /*BUTTON_H_*/
