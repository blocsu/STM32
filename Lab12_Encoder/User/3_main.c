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
		if(getEnc_Counter() > 192) {
					OFF_All_LEDs
					Green_ON						
		}else if (getEnc_Counter() > 128) {
					OFF_All_LEDs
					Yellow_ON
		}else if (getEnc_Counter() > 64) {
					OFF_All_LEDs
					Red_ON
			}							
				
				else{
					OFF_All_LEDs
					Blue_ON
							
			}
			cnt = getEnc_Counter();
						
		//Test = lab12_main();
		}	
	}

	
void SysTick_Handler(void) {

	if(SysTick_CNT) if(--SysTick_CNT == 0) Flag = 1;	
			
  Systick_Enc();
	//lab12_systick();
}//https://www.youtube.com/watch?v=tuyms5U7VkA&list=PL8OgDYWys_b6XtOjCejd37aVv0ic24jqV&index=37



