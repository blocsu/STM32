#include "DAC.h"

void DAC_ini(void) 
{
	GPIO_InitTypeDef GPIO_struct_DAC; ////��������� ��� ������������� �������
	DAC_InitTypeDef DAC_InitStruct; //��������� ���������������� USART
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //��. ������������ ������ �� �������� ����� ���������� ������ USART
	
	GPIO_struct_DAC.GPIO_Pin   = GPIO_Pin_4; //������������� ��������� � ����������� �� ����� PA4
	GPIO_struct_DAC.GPIO_Mode  = GPIO_Mode_AF; //�������� ����� PA4 � ����� �������������� �������
	GPIO_struct_DAC.GPIO_Speed = GPIO_Low_Speed; //��������� �������� LOW �� ��������������� ����� �����*/
	GPIO_struct_DAC.GPIO_OType = GPIO_OType_PP; //������� ������������ ������������� �� ���� ����
	GPIO_struct_DAC.GPIO_PuPd  = GPIO_PuPd_UP;//�������� ������������ �����
	GPIO_Init(GPIOA, &GPIO_struct_DAC); //�������������� ���� A;
			
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE); //��������� ������������ DAC 
	
	DAC_InitStruct.DAC_Trigger                      = DAC_Trigger_None; //�������� �������� ������� �������������� (� ������ ������ ������� ��� �.�. �� ����� ��������� ��� ���� ������ ������� � ���������)
  DAC_InitStruct.DAC_WaveGeneration               = DAC_WaveGeneration_None; //����� ����������� ���� ������� ���������� � ������������ ���� ��� ���������� ��������� �� �����������
  DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; //� ���� ������ �������� ��������� �� ����� �.�. �� ������� ����� ��������� WaveGeneration
  DAC_InitStruct.DAC_OutputBuffer                 = DAC_OutputBuffer_Enable; //����� ������������ ���������� ����� DAC ������� ���������
  	
	DAC_Init(DAC_Channel_1, &DAC_InitStruct); //������� ���������������� DAC
	DAC_Cmd(DAC_Channel_1, ENABLE); //�������� DAC	
}
