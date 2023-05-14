#include "ADC.h"

void ADC_ini(void) 
{
	GPIO_InitTypeDef GPIO_Init_user;
	ADC_InitTypeDef ADC_InitType;
	
	// Включаем тактирование порта
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//Настраиваем порт как аналоговый
	GPIO_Init_user.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init_user.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init_user.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_user.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_user.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, & GPIO_Init_user);
	
	// Включаем тактирование АЦП
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	//Выключаем повторный запуск по окончании преобразования
	ADC_InitType.ADC_ContinuousConvMode = DISABLE;
	
	//Выравнивание по правому краю
	ADC_InitType.ADC_DataAlign = ADC_DataAlign_Right;
	
	//Триггер выключен
	ADC_InitType.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitType.ADC_ExternalTrigConvEdge =	ADC_ExternalTrigConvEdge_None;
	
	//Преобразование при сканировании одно
	ADC_InitType.ADC_NbrOfConversion = 1;
	
	//Разрешение преобразования в 12 бит
	ADC_InitType.ADC_Resolution = ADC_Resolution_12b;
	
	//Сканирование выключено
	ADC_InitType.ADC_ScanConvMode = DISABLE;
	
	//Записываем в АЦП настройки
	ADC_Init(ADC1, &ADC_InitType);
	
	//Пишем с какого канала читать
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_56Cycles);
	
	//Включаем прерывания
	NVIC_EnableIRQ(ADC_IRQn);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	
	//Включаем АЦП
	ADC_Cmd(ADC1, ENABLE);	
}
