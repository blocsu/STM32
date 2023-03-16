#include "stm32f4xx.h"                  // Device header
uint32_t i;
int main(void)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //включаем тактирование только порта D
		GPIOD->MODER = 0x55000000; //включаем ножки 12-15 на выход
		GPIOD->OTYPER = 0; //включем одт€гивающее сопротивление на весь порт
		GPIOD->OSPEEDR = 0; //установим скорость LOW на все лапки порта
		while(1)
		{
			GPIOD->ODR = 0xF000; //зажигаем светодиоды 12-15
			for(i = 0; i < 1000000; i++) {} //задержка
			GPIOD->ODR = 0x0000; //выключаем все ножки порта D
			for(i = 0; i < 1000000; i++) {} //задержка
		}
	}
