#ifndef ENCODER_H_
#define ENCODER_H_

#include "stm32f4xx.h"

#define	ENC_BUTTON()		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)
#define Read_Enc_A			GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
#define Read_Enc_B			GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)

#define	ENC_MAX					3

//----------------------------------------------------

void encoder_ini(void);
void Systick_Enc(void);
uint8_t getEnc_Counter(void);

void Systick_Enc(void);
uint8_t getEnc_Counter(void);

#endif /*ENCODER_H_*/
