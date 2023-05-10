#include "SPI.h"

void SPI_ini(void) {
	//Настройка выводов
	GPIO_InitTypeDef GPIO_Init_SPI;
	
	//Включаем тактирование выводов
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	//Подключаем альтернативную функцию.
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
	
	//Настройка SPI
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //Определяет направление и количество выводов
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //Размер передаваемого слова
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //Уровень сигнала, который устанавливается пока не ведётся передача
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //Номер среза по которому идёт чтение данных
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //выбирает между программным и аппаратным выбором датчика (CS)
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; //определяет предделитель частоты
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //Определяет порядок следования битов: от старшего к младшему или наоборот
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //режим работы: ведущий или ведомый
	
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
	SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
}
