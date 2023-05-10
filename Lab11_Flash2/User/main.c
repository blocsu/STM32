 #include "main.h"
 
static uint32_t SysTick_CNT = 1;
static uint8_t Flag = 0;

static char TempStr[20];
static uint32_t Test;
static uint8_t count;

int main(void) {
							
	RCC_ClocksTypeDef RCC_Clocks1;
	
	LED_init();
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock/1000);
	
	//timer_ini();
	//usart_ini();
						
	RCC_GetClocksFreq(&RCC_Clocks1);
		
	ReadDeviceAddress(TempStr);
	count = TempStr[0];
  
	switch(TempStr[0]) {
		case 0:
			Red_ON;
			break;
		case 1:
			Yellow_ON;
			break;
		case 2:
			Green_ON;
			break;
		case 3:
			Blue_ON;
			break;
	}
	
	if (count > 2) {
		count = 0;
	}else count++;
		
	WriteDeviceAddress(count);
	Test = Lab11_Test_ini();
			
	while(1) {
						
	}	
}

	
void SysTick_Handler(void) {
		
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }	
	
}
