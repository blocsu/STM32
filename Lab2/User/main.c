#include "stm32f4xx.h"                  // Device header
#include "Lab2_Test.h"
uint32_t i;
uint8_t Test;
uint32_t Flag;
int main(void)
	{
				
		GPIO_InitTypeDef GPIO_struct_LED; //инициализируем переменную GPIO_struct_LED с типом структуры GPIO_InitTypeDef
		
		//RCC_AHB1Periph_GPIOD
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //включаем тактирование только порта D
		
		GPIO_struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //конфигурируем структуру с параметрами на ножках 12-15
		GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT; //включаем ножки 12-15 на выход
		GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
		GPIO_struct_LED.GPIO_OType = GPIO_OType_PP; //включем одтягивающее сопротивление на весь порт
		GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;//этот параметр используется при включении порта на вход, поэтому установили его по умолчанию
		
		GPIO_Init(GPIOD, &GPIO_struct_LED); //инициализируем порт D
		
		//Flag = read_flag();
		
		Test = Lab2_Test_ini("Dotsenko");
		
		read_flag();
		
		GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов 12
		for(i = 0; i < 1000000; i++) {} //задержка
		GPIO_ResetBits(GPIOD, GPIO_Pin_12); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов 12
		GPIO_SetBits(GPIOD, GPIO_Pin_13); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов 13
		for(i = 0; i < 1000000; i++) {} //задержка
		GPIO_ResetBits(GPIOD, GPIO_Pin_13); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов 13
		GPIO_SetBits(GPIOD, GPIO_Pin_14); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов 14
		for(i = 0; i < 1000000; i++) {} //задержка
		GPIO_ResetBits(GPIOD, GPIO_Pin_14); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов 14
		GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов 12
		for(i = 0; i < 1000000; i++) {} //задержка
		GPIO_ResetBits(GPIOD, GPIO_Pin_12); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов 12
		GPIO_SetBits(GPIOD, GPIO_Pin_15); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов 15
		for(i = 0; i < 1000000; i++) {} //задержка
		GPIO_ResetBits(GPIOD, GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов 15
		GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов 12
		for(i = 0; i < 10000000; i++) {} //задержка
		GPIO_ResetBits(GPIOD, GPIO_Pin_12); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов 12
		GPIO_SetBits(GPIOD, GPIO_Pin_13); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов 13
		for(i = 0; i < 1000000; i++) {} //задержка
		GPIO_ResetBits(GPIOD, GPIO_Pin_13); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов 13
		GPIO_SetBits(GPIOD, GPIO_Pin_15); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов 15
		for(i = 0; i < 1000000; i++) {} //задержка
		GPIO_ResetBits(GPIOD, GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов 15
		for(i = 0; i < 1000000; i++) {} //задержка
		Flag = read_flag();
		
		while(1)
		{
			
		}				
		
	}
	
