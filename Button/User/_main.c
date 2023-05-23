 #include "main.h"
 
static uint32_t SysTick_CNT = 0;
uint8_t i = 0;
static uint8_t Flag = 0;
uint8_t flag = 1;
uint8_t User_Button = 0;
uint16_t Count_Of_Button = 0;
uint8_t Button_State = 0;
static uint32_t Test;

void SysTick_Handler(void);


int main(void) {
							
	RCC_ClocksTypeDef RCC_Clocks1;						
	SetSysClockTo168();		
	SystemCoreClockUpdate();		
	SysTick_Config(SystemCoreClock/1000);
	RCC_GetClocksFreq(&RCC_Clocks1);
	//timer_ini();
	//usart_ini();
	LED_init();
//	DAC_ini();
//	ADC_ini();	
	encoder_ini();		
		
	while(1) {
		if(Button_State == Bit_SET) {
				if(Flag == 0)  {
					Flag = 1;
					
					if (flag == 1) {
							flag = 0;
							switch(i) {
							case 0:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD12								
								break;
										
							case 1:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_13); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD13
								break;
										
							case 2:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_14); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD14
								break;
										
							case 3:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD12
								break;
										
							case 4:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_15); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD15
								break;
										
							case 5:	
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD12
								break;
										
							case 6:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_13); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD13
								break;
										
							case 7:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_15); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD15
								break;
						}
						SysTick_CNT = 3;
						if(++i == 8) i = 0;
						//TestVar = Lab5_Test_ini("Dotsenko");
					}							
			  }
			}else Flag = 0;
//		if (getEnc_Counter() > 12)
//		{
//			Red_ON;
//			Blue_OFF;
//			Green_OFF;
//			Yellow_OFF;
//		} else if (getEnc_Counter() > 8) {
//			Red_OFF;
//			Blue_ON;
//			Green_OFF;
//			Yellow_OFF;
//		} else if (getEnc_Counter() > 4) {
//			Red_OFF;
//			Blue_OFF;
//			Green_ON;
//			Yellow_OFF;
//		} else {
//			Red_OFF;
//			Blue_OFF;
//			Green_OFF;
//			Yellow_ON;
//		}
						
		
		}	
	}

	
void SysTick_Handler(void) {

	if(SysTick_CNT) if(--SysTick_CNT == 0) Flag = 1;
	
	if (delay_count > 0) delay_count--;
	//----------------------
	Systick_Enc();
	
}


