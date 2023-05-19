 #include "main.h"
 
static uint32_t SysTick_CNT = 0;
static uint8_t Flag = 0;
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
		
	Lab12_Test_ini();
		
	while(1) {
		if (getEnc_Counter() > 12)
		{
			Red_ON;
			Blue_OFF;
			Green_OFF;
			Yellow_OFF;
		} else if (getEnc_Counter() > 8) {
			Red_OFF;
			Blue_ON;
			Green_OFF;
			Yellow_OFF;
		} else if (getEnc_Counter() > 4) {
			Red_OFF;
			Blue_OFF;
			Green_ON;
			Yellow_OFF;
		} else {
			Red_OFF;
			Blue_OFF;
			Green_OFF;
			Yellow_ON;
		}
						
		Test = lab12_main();
		}	
	}

	
void SysTick_Handler(void) {

	if(SysTick_CNT) if(--SysTick_CNT == 0) Flag = 1;
	
	if (delay_count > 0) delay_count--;
	//----------------------
	Systick_Enc();
	lab12_systick();
}


