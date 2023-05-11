 #include "main.h"
 
static uint32_t SysTick_CNT = 1;
static uint8_t Flag = 0;
static uint16_t data[5];
static uint32_t i = 2000;
static uint8_t TestVar;
static uint32_t Test;

void SysTick_Handler(void);

int main(void) {
							
	RCC_ClocksTypeDef RCC_Clocks1;
	
	//LED_init();
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock/1000);
	
	//timer_ini();
	//usart_ini();
	
	DAC_ini();
						
	RCC_GetClocksFreq(&RCC_Clocks1);
		
	TestVar = lab9_Test_ini("Dotsenko");
		
	while(1) {
		
//		if (Flag) {
//			i = 0;
//			DAC_SetChannel1Data(DAC_Align_12b_R, data[i]);//0.2 * 4095/3 или (0.2/3.3*4095)
//			SysTick_CNT = 200;
//		}
						
		Test = lab9_while(data);
		}	
	}

	
void SysTick_Handler(void) {
//	if(i) i = 0; else i = 4000;
//	DAC_SetChannel1Data(DAC_Align_12b_R, i);
	
	if((i += 35) > 9000) i = 2000;	//все значения увеличены в 10 раз, чтобы уйти от дробной части в формуле ниже
	DAC_SetChannel1Data(DAC_Align_12b_R, (uint16_t)((i * 4095 + 15000)/30000));	
		
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }
	
	lab9_systick();
}
