#include "DMA_USART.h"

void DMA_USART_ini(void) 
{
	DMA_InitTypeDef DMA_Init_struct;
	
	uint8_t text[256]={0};
	
// �������� ������������
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

DMA_Init_struct.DMA_Channel = DMA_Channel_1;// ��������� ����� 1
DMA_Init_struct.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);//���������� ��������� �����
DMA_Init_struct.DMA_Memory0BaseAddr = (uint32_t)text;//���������� ��������� ������
DMA_Init_struct.DMA_DIR = DMA_DIR_MemoryToPeripheral;//����� �� ����� ������� ������ � �����
DMA_Init_struct.DMA_BufferSize = sizeof(text);//����� ������� ���������� (��� ���� �����)
DMA_Init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//������� �� ����������� ��������� ������������� ������ �� �������
DMA_Init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;//������� ����������� ��������� ������ ������ �� �������
DMA_Init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������, ��� ������ � ��������� �����������
DMA_Init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�������, ��� ������ � ������ �����������
DMA_Init_struct.DMA_Mode = DMA_Mode_Normal;//�������� ��������� ��������
DMA_Init_struct.DMA_Priority = DMA_Priority_Medium;//��������� ���������
DMA_Init_struct.DMA_FIFOMode = DMA_FIFOMode_Disable;//��������� ����
DMA_Init_struct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
DMA_Init_struct.DMA_MemoryBurst = DMA_MemoryBurst_Single;//��������� �������� �� ������ ����� �� �������
DMA_Init_struct.DMA_PeripheralBurst = DMA_MemoryBurst_Single;
	
// �������������� DMA
DMA_Init(DMA1_Stream1, &DMA_Init_struct);

// ��������� ������ DMA � ��������� USART1
USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

// �������� ���������� �� ��������� ������ DMA
NVIC_EnableIRQ(DMA1_Stream1_IRQn); //�������� ����� ���������� �� DMA1
DMA_ITConfig(DMA1_Stream1, DMA_IT_TC, ENABLE); //�������� ���������� �� ��������� ��������
}

// DMA interrupt - ��������� ����������
void DMA1_Stream1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1) == SET) {
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_FLAG_TCIF1);
		
		//����� ���� ������ ��������, ���������� �������:
    DMA_Cmd(DMA1_Stream1, ENABLE);
	}
}
