#ifndef ENCODER_H_
#define ENCODER_H_

#include "stm32f4xx.h"

#define	ENC_BUTTON()		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)
#define	ENC_A()					GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)
#define	ENC_B()					GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)

#define ENC_DELAY				10

void encoder_ini(void);

void Systick_Enc(void);
uint8_t getEnc_Counter(void);

#endif /*ENCODER_H_*/
