#include "SPI.h"

void SPI_ini(void) {
	//��������� �������
	GPIO_InitTypeDef GPIO_Init_SPI;
	
	//�������� ������������ �������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	//���������� �������������� �������.
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	
	GPIO_Init_SPI.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init_SPI.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_SPI.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_SPI.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_SPI.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Init(GPIOA, &GPIO_Init_SPI);
	
	GPIO_Init_SPI.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init_SPI.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_SPI.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_SPI.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_SPI.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOE, &GPIO_Init_SPI);
	
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
	
	//��������� SPI
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //���������� ����������� � ���������� �������
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //������ ������������� �����
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //������� �������, ������� ��������������� ���� �� ������ ��������
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //����� ����� �� �������� ��� ������ ������
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //�������� ����� ����������� � ���������� ������� ������� (CS)
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; //���������� ������������ �������
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //���������� ������� ���������� �����: �� �������� � �������� ��� ��������
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //����� ������: ������� ��� �������
	
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
	SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
}
