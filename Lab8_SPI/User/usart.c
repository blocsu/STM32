#include "stm32f4xx.h"  // Device header
#include "main.h"
#include "init.h"
#include "timers.h"
#include "usart.h"
#include "Lab7_Test.h"

void usart_ini(void) 
{
	GPIO_InitTypeDef GPIO_struct_USART2; ////��������� ��� ������������� �������
	USART_InitTypeDef USART_InitStruct; //��������� ���������������� USART
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //��. ������������ ������ �� �������� ����� ���������� ������ USART
	
	GPIO_struct_USART2.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3; //������������� ��������� � ����������� �� ������ PA2 � PA3
	GPIO_struct_USART2.GPIO_Mode  = GPIO_Mode_AF; //�������� ����� PA2 � PA3 �� ����� �������������� �������
	GPIO_struct_USART2.GPIO_Speed = GPIO_Low_Speed; //��������� �������� LOW �� ��������������� ����� �����*/
	GPIO_struct_USART2.GPIO_OType = GPIO_OType_PP; //������� ������������ ������������� �� ���� ����
	GPIO_struct_USART2.GPIO_PuPd  = GPIO_PuPd_UP;//�������� ������������ �����
	GPIO_Init(GPIOA, &GPIO_struct_USART2); //�������������� ���� A;
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //����������� ������ PA2 � USART2 TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //����������� ������ PA3 � USART2 RX
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //��������� ������������ USART2 
	
	USART_InitStruct.USART_BaudRate = 115200; // �������� �������� ������ ������ ��������� � ��������� � ���������� �� �����
  USART_InitStruct.USART_WordLength = USART_WordLength_8b; //���������� ��� � ����� USART ������� ����� ���������� �� 1 ������ ���������� 8 �� ����� ���� � 9
  USART_InitStruct.USART_StopBits = USART_StopBits_1; //��� ������ ��������� ��� ���� ���������, ���� ������ ��� ���� �������� ��������
  USART_InitStruct.USART_Parity = USART_Parity_No ; //��� �������� �� ������������
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //����� ������ �� �������� � �� ����
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //���������� ������� �� ������������
	
	USART_Init(USART2, &USART_InitStruct); //������� ���������������� USART2
	USART_Cmd(USART2, ENABLE); //�������� USART
	
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	//USART_ITConfig(USART2, USART_IT_TC, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // ��������� ���������� �� �����
	
	NVIC_EnableIRQ(USART2_IRQn); //��������� ���������� �� USART
	
}
