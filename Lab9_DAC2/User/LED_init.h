#ifndef LED_init_H_
#define LED_init_H_

#include "stm32f4xx.h"

#define OFF_All_LEDs GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ����������� PD12/13/14/15
#define ON_All_LEDs GPIO_SetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������� ������� ���������� 1 �� ����� ����������� PD12/13/14/15

#define Green_ON GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
#define Green_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_12); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12

#define Yellow_ON GPIO_SetBits(GPIOD, GPIO_Pin_13); //������������� ������� ������� ���������� 1 �� ����� ���������� PD13
#define Yellow_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_13); //������������� ������ ������� ���������� 0 �� ����� ���������� PD13

#define Red_ON GPIO_SetBits(GPIOD, GPIO_Pin_14); //������������� ������� ������� ���������� 1 �� ����� ���������� PD14
#define Red_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_14); //������������� ������ ������� ���������� 0 �� ����� ���������� PD14

#define Blue_ON GPIO_SetBits(GPIOD, GPIO_Pin_15); //������������� ������� ������� ���������� 1 �� ����� ���������� PD15
#define Blue_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD15

void LED_init(void);

#endif /*LED_init_H_*/
