#include "stm32f4xx.h"  // Device header
#include "main.h"
#include "init.h"
#include "timers.h"
#include "Lab6_Test.h"

void TIM3_IRQHandler(void);
void TIM3_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			
			GPIO_ToggleBits(GPIOA, GPIO_Pin_2);
		}
}

void timer_ini(void) 
{
	TIM_TimeBaseInitTypeDef timer_struct;
	NVIC_InitTypeDef NVIC_struct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	timer_struct.TIM_Prescaler = 5-1; //4400000
	timer_struct.TIM_CounterMode = TIM_CounterMode_Up;
	timer_struct.TIM_Period = 1000;
	timer_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	timer_struct.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3, &timer_struct);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	NVIC_struct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_struct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_struct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_struct);
	
	TIM_Cmd(TIM3, ENABLE);
}
