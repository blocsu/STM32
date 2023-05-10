 #include "main.h"
 
static uint32_t SysTick_CNT = 1;
static uint8_t Flag = 0;

static char TempStr[20];
static char TempStr2[20];

int main(void) {
							
	RCC_ClocksTypeDef RCC_Clocks1;
	
	//LED_init();
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock/1000);
	
	//timer_ini();
	//usart_ini();
						
	RCC_GetClocksFreq(&RCC_Clocks1);
		
	//TestVar = lab9_test_ini("Dotsenko
	sprintf(TempStr2, "0001951337B1");
	
	WriteDeviceAddress(TempStr2);
	
	ReadDeviceAddress(TempStr);
		
	while(1) {
		
		
		//Test = while_test(decision);
		}	
	}

	
void SysTick_Handler(void) {
		
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }
	
	//test_systick();
}
