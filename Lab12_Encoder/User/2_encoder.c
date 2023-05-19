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

#define Read_Enc_A			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)
#define Read_Enc_B			GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10)

#define	ENC_MAX					3

uint8_t Enc_counter=0;
uint8_t Enc_Mode=0;

uint8_t Enc_A_count=0;
uint8_t Enc_A_state=0;

uint8_t Enc_B_count=0;
uint8_t Enc_B_state=0;

void Systick_Enc(void)
{
	if (Read_Enc_A == 1)
	{
		if (Enc_A_count < ENC_MAX)
		{
			Enc_A_count++;
		} else {
			if (Enc_A_state == 0)
			{
				if (Enc_Mode == 0)
				{
					Enc_Mode = 1;
					Enc_counter++;
				} else {
					Enc_Mode = 0;
					Enc_counter--;
				}
			}
			Enc_A_state = 1;
		}
	} else {
		if (Enc_A_count > 0)
		{
			Enc_A_count--;
		} else {
			if (Enc_A_state == 1)	
			{
				if (Enc_Mode == 0)
				{
					Enc_Mode = 1;
					Enc_counter++;
				} else {
					Enc_Mode = 0;
					Enc_counter--;
				}
			}
			Enc_A_state = 0;
		}
	}
	
	if (Read_Enc_B == 1)
	{
		if (Enc_B_count < ENC_MAX)
		{
			Enc_B_count++;
		} else {
			if (Enc_B_state == 0)
			{
				if (Enc_Mode == 0)
				{
					Enc_Mode = 1;
					Enc_counter--;
				} else {
					Enc_Mode = 0;
					Enc_counter++;
				}
			}
			Enc_B_state = 1;
		}
	} else {
		if (Enc_B_count > 0)
		{
			Enc_B_count--;
		} else {
			if (Enc_B_state == 1)	
			{
				if (Enc_Mode == 0)
				{
					Enc_Mode = 1;
					Enc_counter--;
				} else {
					Enc_Mode = 0;
					Enc_counter++;
				}
			}
			Enc_B_state = 0;
		}
	}
}

//----------------------------------------------------
uint8_t getEnc_Counter(void)
{
	return Enc_counter;
}