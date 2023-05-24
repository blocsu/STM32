#include "button.h"

void button_ini(void) {
	GPIO_InitTypeDef GPIO_struct_Button; //инициализируем переменную GPIO_struct_Button с типом структуры GPIO_InitTypeDef
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //включаем тактирование порта A
	
	GPIO_struct_Button.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1; //конфигурируем структуру с параметрами на ножке PA0
	GPIO_struct_Button.GPIO_Mode  = GPIO_Mode_IN; //включаем ножку PA0 на вход
	GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
	GPIO_struct_Button.GPIO_OType = GPIO_OType_PP; //включем одт¤гивающее сопротивление на весь порт
	GPIO_struct_Button.GPIO_PuPd  = GPIO_PuPd_NOPULL;//этот параметр используетс¤ при включении порта на вход, поэтому установили его по умолчанию
	
	GPIO_Init(GPIOA, &GPIO_struct_Button); //инициализируем порт A
}
//-----------------------------------------------------------------------------

uint8_t Button_State = 0;
uint8_t Button_Count = 0;
uint8_t Button_Press = 0;

void Button_Read(void) {
	if(--Button_Count == 0) {
		Button_Count = 10;
		uint8_t new_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		if(new_state) {
			if(new_state != Button_State) Button_Press = 1;						
		}
		Button_State = new_state;
	}	
} 

void Buttons_Filter(void) {
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
		if(Button_Count < 5) {
			Button_Count++;
		}else if(Button_State == 0) {Button_State = 1; Button_Press = 1;}
	}else {
		if(Button_Count > 0) {
			Button_Count--;
		}else if(Button_State == 1) {Button_State = 0; Button_Press = 0;}
	}
}
