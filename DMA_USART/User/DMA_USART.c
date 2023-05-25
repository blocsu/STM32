#include "DMA_USART.h"

void DMA_USART_ini(void) 
{
	DMA_InitTypeDef DMA_Init_struct;
	
	uint8_t text[256]={0};
	
// Включаем тактирование
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

DMA_Init_struct.DMA_Channel = DMA_Channel_1;// Указываем канал 1
DMA_Init_struct.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);//Записываем указатель куда…
DMA_Init_struct.DMA_Memory0BaseAddr = (uint32_t)text;//Записываем указатель откуда
DMA_Init_struct.DMA_DIR = DMA_DIR_MemoryToPeripheral;//Пишем от какой области памяти к какой
DMA_Init_struct.DMA_BufferSize = sizeof(text);//Пишем сколько передавать (Тут весь буфер)
DMA_Init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//Говорим не увеличивать указатель периферийного адреса на единицу
DMA_Init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;//Говорим увеличивать указатель адреса памяти на единицу
DMA_Init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//Говорим, что данные в периферии однобайтные
DMA_Init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//Говорим, что данные в памяти однобайтные
DMA_Init_struct.DMA_Mode = DMA_Mode_Normal;//Выбираем одиночную передачу
DMA_Init_struct.DMA_Priority = DMA_Priority_Medium;//Указываем приоритет
DMA_Init_struct.DMA_FIFOMode = DMA_FIFOMode_Disable;//Выключаем ФИФО
DMA_Init_struct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
DMA_Init_struct.DMA_MemoryBurst = DMA_MemoryBurst_Single;//Потоковая передача по одному слову за посылку
DMA_Init_struct.DMA_PeripheralBurst = DMA_MemoryBurst_Single;
	
// Инициализируем DMA
DMA_Init(DMA1_Stream1, &DMA_Init_struct);

// Указываем работу DMA с передачей USART1
USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

// Включаем прерывания по окончанию работы DMA
NVIC_EnableIRQ(DMA1_Stream1_IRQn); //Включаем общие прерывания от DMA1
DMA_ITConfig(DMA1_Stream1, DMA_IT_TC, ENABLE); //Включаем прерывания по окончанию передачи
}

// DMA interrupt - обработка прерываний
void DMA1_Stream1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1) == SET) {
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_FLAG_TCIF1);
		
		//Когда надо начать передачу, используем функцию:
    DMA_Cmd(DMA1_Stream1, ENABLE);
	}
}
