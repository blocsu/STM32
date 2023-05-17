#include "encoder.h"

void encoder_ini(void)
{
	GPIO_InitTypeDef GPIO_Init_Encoder;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//---------button-------
	GPIO_Init_Encoder.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init_Encoder.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_Encoder.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_Encoder.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Encoder.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOE, &GPIO_Init_Encoder);
	
	GPIO_Init_Encoder.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init_Encoder.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Encoder.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_Encoder.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Encoder.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Init(GPIOE, &GPIO_Init_Encoder);
	
	GPIO_SetBits(GPIOE, GPIO_Pin_7);
	//---------end button-------
	
	//---------rotor-------
	GPIO_Init_Encoder.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_Init_Encoder.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Encoder.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_Encoder.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Encoder.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOE, &GPIO_Init_Encoder);
	//---------end rotor-------
}
