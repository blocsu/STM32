#include "stm32f4xx.h"                  // Device header
uint32_t i;
int main(void)
	{
				
		GPIO_InitTypeDef GPIO_struct_LED; //инициализируем переменную GPIO_struct_LED с типом структуры GPIO_InitTypeDef
		GPIO_InitTypeDef GPIO_struct_Button; //инициализируем переменную GPIO_struct_Button с типом структуры GPIO_InitTypeDef
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //включаем тактирование порта D
		
		GPIO_struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //конфигурируем структуру с параметрами на ножках 12-15
		GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT; //включаем ножки 12-15 на выход
		GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
		GPIO_struct_LED.GPIO_OType = GPIO_OType_PP; //включем одт€гивающее сопротивление на весь порт
		GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;//этот параметр используетс€ при включении порта на вход, поэтому установили его по умолчанию
		
		GPIO_Init(GPIOD, &GPIO_struct_LED); //инициализируем порт D
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //включаем тактирование порта A
		
		GPIO_struct_Button.GPIO_Pin = GPIO_Pin_0; //конфигурируем структуру с параметрами на ножке PA0
		GPIO_struct_Button.GPIO_Mode = GPIO_Mode_IN; //включаем ножку PA0 на вход
		GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
		GPIO_struct_Button.GPIO_OType = GPIO_OType_PP; //включем одт€гивающее сопротивление на весь порт
		GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;//этот параметр используетс€ при включении порта на вход, поэтому установили его по умолчанию
		
		GPIO_Init(GPIOA, &GPIO_struct_Button); //инициализируем порт A
		
		while(1)
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1) 
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напр€жени€ 1 на ножке светодиода PD12
			}
			else
			{
				GPIO_ResetBits(GPIOD, GPIO_Pin_12); //устанавливаем низкий уровень напр€жени€ 0 на ножку светодиода PD12
			}			
		}
	}
