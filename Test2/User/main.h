#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx.h"
#include "ports.h"

void port_ini(void);
void delay(int n);

void port_ini(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //������� ������������ �����
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //������� ������������ �����
	
	GPIOD->MODER = 0x55000000; //�������� ����� 12-15 �� �����
	GPIOD->OTYPER = 0; //������� ������������ ������������� �� ���� ����
	GPIOD->OSPEEDR = 0; //��������� �������� LOW �� ��� ����� �����	
	
	GPIOA->MODER = 0xA800AAAA; //�������� ����� 0-7 �� �����
	GPIOA->OTYPER = 0; //������� ������������ ������������� �� ���� ����
	GPIOA->OSPEEDR = 0; //��������� �������� LOW �� ��� ����� �����	
}

void delay(int n)
{
while(n > 0) n--;
}	


#endif /*MAIN_H_*/
