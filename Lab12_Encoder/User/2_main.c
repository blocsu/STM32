 #include "main.h"
 
static uint32_t SysTick_CNT = 10;
static uint8_t Flag = 0;
uint8_t new_state_A = 1;
uint8_t new_state_B = 1;
uint8_t enc_a=1, enc_b=1;
int32_t count_a=0, count_b=0;
uint8_t M=0, encoder_state=0;
uint8_t cnt=4;
static uint32_t Test;

static uint16_t Button_Press = 0;
static uint16_t Button_State = 0;
static uint8_t  Button_Count = 10;

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
		
	//Lab12_Test_ini();
		
	while(1) {
		switch(cnt/4) {
				case 1:
					OFF_All_LEDs
					Green_ON						
					break;
							
				case 2:
					OFF_All_LEDs
					Yellow_ON
					break;
							
				case 3:
					OFF_All_LEDs
					Red_ON
					break;							
				
				case 4:
					OFF_All_LEDs
					Blue_ON
					break;				
			}
						
		//Test = lab12_main();
		}	
	}

	
void SysTick_Handler(void) {

	if(SysTick_CNT) if(--SysTick_CNT == 0) Flag = 1;	
	
	// Опрос кнопки
	if(--Button_Count == 0) {
	  uint8_t new_state_A = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9);
	  
		Button_Count = 10;
		
		if(new_state_A != Button_State) { //Если текущее состояние не совпадает с предыдущим, то проваливаемся дальше
			if(new_state_A == Bit_SET) Button_Press = 1;

			Button_State = new_state_A;	//Приравниваем текущее состояние предыдущему		
		}
	}
	
	if(--Button_Count == 0) {
	  uint8_t new_state_B = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10);
	  
		Button_Count = 10;
		
		if(new_state != Button_State) { //Если текущее состояние не совпадает с предыдущим, то проваливаемся дальше
			if(new_state == Bit_SET) Button_Press = 1;

			Button_State = new_state;	//Приравниваем текущее состояние предыдущему		
		}
	}
			
	//Анализ энкодера
//	if(Flag){
//		Flag = 0;
//		new_state_A = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9);
//	  new_state_B = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10);
//		SysTick_CNT = 5;
//	}
	
	switch(M) {
		case 0:
			if(new_state_A != enc_a) { //Если текущее состояние не совпадает с предыдущим, то проваливаемся дальше
				enc_a = new_state_A;	//Приравниваем текущее состояние предыдущему		
				count_a--;
//				if(cnt > 4) {
//						cnt--;
//				}else cnt = 20;
			}else {				
				if(new_state_B != enc_b) { //Если текущее состояние не совпадает с предыдущим, то проваливаемся дальше
					enc_b = new_state_B;	//Приравниваем текущее состояние предыдущему
					count_b++;
//					if(cnt < 20) {
//							cnt++;
//					}else cnt = 4;		
				}
			}			
			M = 1;
			break;			
			
		case 1:			
				if(new_state_A != enc_a) { //Если текущее состояние не совпадает с предыдущим, то проваливаемся дальше
					enc_a = new_state_A;	//Приравниваем текущее состояние предыдущему	
					count_a++;
//					if(cnt < 20) {
//							cnt++;
//					}else cnt = 4;					
				}else {
					if(new_state_B != enc_b) { //Если текущее состояние не совпадает с предыдущим, то проваливаемся дальше
						enc_b = new_state_B;	//Приравниваем текущее состояние предыдущему
						count_b--;
//						if(cnt > 4) {
//								cnt--;
//						}else cnt = 20;					
					}
				}			
			M = 0;
			break;		
	}
	//lab12_systick();
}


