#include "stm32f4xx.h"

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //включим тактирование порта
	GPIOD->MODER = 0x40000000; //включаем ножку 15 на выход
	GPIOD->OTYPER = 0; //включем одт€гивающее сопротивление на весь порт
	GPIOD->OSPEEDR = 0; //установим скорость LOW на все лапки порта
	GPIOD->ODR = 0x8000; //зажжом светодиод, подключенный к лапке 15 порта
	while(1)
	{
		
	}
}
