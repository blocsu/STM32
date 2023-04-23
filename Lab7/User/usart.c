#include "stm32f4xx.h"  // Device header
#include "main.h"
#include "init.h"
#include "timers.h"
#include "usart.h"
#include "Lab7_Test.h"

void usart_ini(void) 
{
	GPIO_InitTypeDef GPIO_struct_USART2;
	USART_InitTypeDef USART_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_struct_USART2.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3; //конфигурируем структуру с параметрами на ножках PA2 и PA3
	GPIO_struct_USART2.GPIO_Mode  = GPIO_Mode_AF; //включаем ножки PA2 и PA3 на режим альтернативной функции
	GPIO_struct_USART2.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
	GPIO_struct_USART2.GPIO_OType = GPIO_OType_PP; //включем одт€гивающее сопротивление на весь порт
	GPIO_struct_USART2.GPIO_PuPd  = GPIO_PuPd_UP;//включаем подт€гивание вверх
	GPIO_Init(GPIOA, &GPIO_struct_USART2); //инициализируем порт A;
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_InitStruct.USART_BaudRate = 9600; // скорость передачи данных должна совпадать с указанной в приложении на компе
  USART_InitStruct.USART_WordLength = USART_WordLength_8b; //количество бит в слове USART которые будет передавать за 1 псылку стандартно 8 но может быть и 9
  USART_InitStruct.USART_StopBits = USART_StopBits_1; //чем больше стопбитов тем выше надЄжность, чмем меньше тем выше скорость передачи
  USART_InitStruct.USART_Parity = USART_Parity_No ; //бит чЄьности не используетс€
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //резим работы на передачу и на приЄм
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //управление потоком не используетс€
	
	USART_Init(USART2, &USART_InitStruct);
	USART_Cmd(USART2, ENABLE);
	
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	//USART_ITConfig(USART2, USART_IT_TC, ENABLE);
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	//NVIC_EnableIRQ(USART2_IRQn);
	
}
