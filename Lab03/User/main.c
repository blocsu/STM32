#include "stm32f4xx.h" // Device header
#include "Lab3_Test.h"
#include "main.h"


//uint32_t i;
uint8_t TestVar;
uint32_t Test;
uint8_t *decision;
uint8_t tim6_count = 0;
uint8_t User_Button = 0;
uint16_t Count_Of_Button = 0;
uint8_t Button_State = 0;
uint8_t Flag = 0;
int Rattle_Of_Button(void); 

int Rattle_Of_Button(void) 
			{
				if(User_Button == Bit_SET) 
          {
						if(Count_Of_Button < 1700)
						{
							Count_Of_Button++;
						}else {
							if(User_Button == Bit_SET) {
								User_Button = Bit_SET;
								return 1;
							}
						}
					}else {
						if(Count_Of_Button > 0) 
							{
								Count_Of_Button--;
							}else {
								User_Button = Bit_RESET;
								return 0;
							}
					}
			}

int main(void)
	{
				
		GPIO_InitTypeDef GPIO_struct_LED; //инициализируем переменную GPIO_struct_LED с типом структуры GPIO_InitTypeDef
		GPIO_InitTypeDef GPIO_struct_Button; //инициализируем переменную GPIO_struct_Button с типом структуры GPIO_InitTypeDef
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //включаем тактирование порта D
		
		GPIO_struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //конфигурируем структуру с параметрами на ножках 12-15
		GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT; //включаем ножки 12-15 на выход
		GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
		GPIO_struct_LED.GPIO_OType = GPIO_OType_PP; //включем одт€гивающее сопротивление на весь порт
		GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;//этот параметр используетс€ при включении порта на вход, поэтому установили его по умолчанию
		
		GPIO_Init(GPIOD, &GPIO_struct_LED); //инициализируем порт D
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //включаем тактирование порта A
		
		GPIO_struct_Button.GPIO_Pin = GPIO_Pin_0; //конфигурируем структуру с параметрами на ножке PA0
		GPIO_struct_Button.GPIO_Mode = GPIO_Mode_IN; //включаем ножку PA0 на вход
		GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
		GPIO_struct_Button.GPIO_OType = GPIO_OType_PP; //включем одт€гивающее сопротивление на весь порт
		GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;//этот параметр используетс€ при включении порта на вход, поэтому установили его по умолчанию
		
		GPIO_Init(GPIOA, &GPIO_struct_Button); //инициализируем порт A

		TestVar = Lab3_Test_ini("Dotsenko");

    RCC_ClocksTypeDef RCC_Clocks1;
		
				
	  RCC_GetClocksFreq(&RCC_Clocks1);
		
		while(1)
		{
			Test = while_Test(decision);
			User_Button = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
			Button_State = Rattle_Of_Button();
			
				if(Button_State == Bit_SET)
					{
						if(Flag == 0)
						{
							Flag = 1;
						switch(tim6_count)
						{
							case 0:
							case 3:
							case 5:	
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напр€жени€ 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напр€жени€ 1 на ножке светодиода PD12
							  break;
							case 1:
							case 6:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напр€жени€ 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_13); //устанавливаем высокий уровень напр€жени€ 1 на ножке светодиода PD13
							  break;
							case 2:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напр€жени€ 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_14); //устанавливаем высокий уровень напр€жени€ 1 на ножке светодиода PD14
							  break;
							case 4:
							case 7:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напр€жени€ 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_15); //устанавливаем высокий уровень напр€жени€ 1 на ножке светодиода PD15
							  break;
							default:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
							  break;
						}
						delay(47000);
						if(tim6_count<7) tim6_count++;
						else tim6_count=0;
					}
						
				}else Flag = 0;
	
	   }
  }

