#include "stm32f4xx.h"

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //������� ������������ �����
	GPIOD->MODER = 0x40000000; //�������� ����� 15 �� �����
	GPIOD->OTYPER = 0; //������� ������������ ������������� �� ���� ����
	GPIOD->OSPEEDR = 0; //��������� �������� LOW �� ��� ����� �����
	GPIOD->ODR = 0x8000; //������ ���������, ������������ � ����� 15 �����
	while(1)
	{
		
	}
}
