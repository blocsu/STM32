#include "stm32f4xx.h"                  // Device header
uint32_t i;
int main(void)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //�������� ������������ ������ ����� D
		GPIOD->MODER = 0x55000000; //�������� ����� 12-15 �� �����
		GPIOD->OTYPER = 0; //������� ������������ ������������� �� ���� ����
		GPIOD->OSPEEDR = 0; //��������� �������� LOW �� ��� ����� �����
		while(1)
		{
			GPIOD->ODR = 0xF000; //�������� ���������� 12-15
			for(i = 0; i < 1000000; i++) {} //��������
			GPIOD->ODR = 0x0000; //��������� ��� ����� ����� D
			for(i = 0; i < 1000000; i++) {} //��������
		}
	}
