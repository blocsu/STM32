#include "DAC.h"

void DAC_ini(void) 
{
	GPIO_InitTypeDef GPIO_struct_DAC; ////—труктура дл€ инициализации выводов
	DAC_InitTypeDef DAC_InitStruct; //структура инициализирующа€ USART
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //¬к. тактировани€ вывода по которому будет передавать данные USART
	
	GPIO_struct_DAC.GPIO_Pin   = GPIO_Pin_4; //конфигурируем структуру с параметрами на ножке PA4
	GPIO_struct_DAC.GPIO_Mode  = GPIO_Mode_AF; //включаем ножку PA4 в режим альтернативной функции
	GPIO_struct_DAC.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
	GPIO_struct_DAC.GPIO_OType = GPIO_OType_PP; //включем одт€гивающее сопротивление на весь порт
	GPIO_struct_DAC.GPIO_PuPd  = GPIO_PuPd_UP;//включаем подт€гивание вверх
	GPIO_Init(GPIOA, &GPIO_struct_DAC); //инициализируем порт A;
			
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE); //включение тактировани€ DAC 
	
	DAC_InitStruct.DAC_Trigger                      = DAC_Trigger_None; //выбираем источник запуска преобразований (в данном случае источна нет т.к. мы будем запускать его сами вызвав функцию в программе)
  DAC_InitStruct.DAC_WaveGeneration               = DAC_WaveGeneration_None; //будет выставл€тс€ свой уровень напр€жени€ и формирование шума или треуголныз импульсов не планируетс€
  DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; //в этом случае значение параметра не важно т.к. не выбрали форму колебаний WaveGeneration
  DAC_InitStruct.DAC_OutputBuffer                 = DAC_OutputBuffer_Enable; //буфеп использовать необходимо чтобу DAC работал корректно
  	
	DAC_Init(DAC_Channel_1, &DAC_InitStruct); //функци€ инициализирующа€ DAC
	DAC_Cmd(DAC_Channel_1, ENABLE); //включаем DAC	
}
