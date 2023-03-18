#include "stm32f4xx.h"                  // Device header
uint32_t i;
int main(void)
	{
				
		GPIO_InitTypeDef GPIO_struct_LED; //�������������� ���������� GPIO_struct_LED � ����� ��������� GPIO_InitTypeDef
		GPIO_InitTypeDef GPIO_struct_Button; //�������������� ���������� GPIO_struct_Button � ����� ��������� GPIO_InitTypeDef
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //�������� ������������ ����� D
		
		GPIO_struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //������������� ��������� � ����������� �� ������ 12-15
		GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT; //�������� ����� 12-15 �� �����
		GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed; //��������� �������� LOW �� ��������������� ����� �����*/
		GPIO_struct_LED.GPIO_OType = GPIO_OType_PP; //������� ������������ ������������� �� ���� ����
		GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;//���� �������� ������������ ��� ��������� ����� �� ����, ������� ���������� ��� �� ���������
		
		GPIO_Init(GPIOD, &GPIO_struct_LED); //�������������� ���� D
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //�������� ������������ ����� A
		
		GPIO_struct_Button.GPIO_Pin = GPIO_Pin_0; //������������� ��������� � ����������� �� ����� PA0
		GPIO_struct_Button.GPIO_Mode = GPIO_Mode_IN; //�������� ����� PA0 �� ����
		GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed; //��������� �������� LOW �� ��������������� ����� �����*/
		GPIO_struct_Button.GPIO_OType = GPIO_OType_PP; //������� ������������ ������������� �� ���� ����
		GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;//���� �������� ������������ ��� ��������� ����� �� ����, ������� ���������� ��� �� ���������
		
		GPIO_Init(GPIOA, &GPIO_struct_Button); //�������������� ���� A
		
		while(1)
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1) 
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
			}
			else
			{
				GPIO_ResetBits(GPIOD, GPIO_Pin_12); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12
			}			
		}
	}
