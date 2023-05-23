#include "button.h"

void button_ini(void) {
	GPIO_InitTypeDef GPIO_struct_Button; //�������������� ���������� GPIO_struct_Button � ����� ��������� GPIO_InitTypeDef
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //�������� ������������ ����� A
	
	GPIO_struct_Button.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1; //������������� ��������� � ����������� �� ����� PA0
	GPIO_struct_Button.GPIO_Mode  = GPIO_Mode_IN; //�������� ����� PA0 �� ����
	GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed; //��������� �������� LOW �� ��������������� ����� �����*/
	GPIO_struct_Button.GPIO_OType = GPIO_OType_PP; //������� ����������� ������������� �� ���� ����
	GPIO_struct_Button.GPIO_PuPd  = GPIO_PuPd_NOPULL;//���� �������� ����������� ��� ��������� ����� �� ����, ������� ���������� ��� �� ���������
	
	GPIO_Init(GPIOA, &GPIO_struct_Button); //�������������� ���� A
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

uint8_t get_Button_Press(void) {
	return Button_Press;
}