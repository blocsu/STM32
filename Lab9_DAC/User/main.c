 #include "main.h"
 
static uint32_t SysTick_CNT = 1;
static uint8_t Flag = 0;

int main(void) {
							
	RCC_ClocksTypeDef RCC_Clocks1;
	
	//LED_init();
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock/1000);
	
	//timer_ini();
	//usart_ini();
	
	DAC_ini();
	
	DAC_SetChannel1Data(DAC_Align_12b_R, 1365);
				
	RCC_GetClocksFreq(&RCC_Clocks1);
		
	//TestVar = lab9_test_ini("Dotsenko");
		
	while(1) {
		
		
		//Test = while_test(decision);
		}	
	}

	
void SysTick_Handler(void) {
		
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }
	
	//test_systick();
}
