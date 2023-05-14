#include "ADC.h"

void ADC_ini(void) 
{
	GPIO_InitTypeDef GPIO_Init_user;
	ADC_InitTypeDef ADC_InitType;
	
	// �������� ������������ �����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//����������� ���� ��� ����������
	GPIO_Init_user.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init_user.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init_user.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_user.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_user.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, & GPIO_Init_user);
	
	// �������� ������������ ���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	//��������� ��������� ������ �� ��������� ��������������
	ADC_InitType.ADC_ContinuousConvMode = DISABLE;
	
	//������������ �� ������� ����
	ADC_InitType.ADC_DataAlign = ADC_DataAlign_Right;
	
	//������� ��������
	ADC_InitType.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitType.ADC_ExternalTrigConvEdge =	ADC_ExternalTrigConvEdge_None;
	
	//�������������� ��� ������������ ����
	ADC_InitType.ADC_NbrOfConversion = 1;
	
	//���������� �������������� � 12 ���
	ADC_InitType.ADC_Resolution = ADC_Resolution_12b;
	
	//������������ ���������
	ADC_InitType.ADC_ScanConvMode = DISABLE;
	
	//���������� � ��� ���������
	ADC_Init(ADC1, &ADC_InitType);
	
	//����� � ������ ������ ������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_56Cycles);
	
	//�������� ����������
	NVIC_EnableIRQ(ADC_IRQn);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	
	//�������� ���
	ADC_Cmd(ADC1, ENABLE);	
}
