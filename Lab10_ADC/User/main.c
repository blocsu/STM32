 #include "main.h"
 
static uint32_t SysTick_CNT = 1;
static uint8_t Flag = 0;
static uint16_t min, max, period;
static uint16_t ADC_result;
static char str[256];
static uint32_t i = 2000;
static uint8_t variant_num;
static uint32_t Test;

void SysTick_Handler(void);

//Функция прерывания
void ADC_IRQHandler(void);
void ADC_IRQHandler(void)
{
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	ADC_result = ADC_GetConversionValue(ADC1);
	sprintf(str, "V=%d mv", ADC_result);
}

int main(void) {
							
	RCC_ClocksTypeDef RCC_Clocks1;
	
	//LED_init();
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock/1000);
	
	//timer_ini();
	//usart_ini();
	
	DAC_ini();
	ADC_ini();
						
	RCC_GetClocksFreq(&RCC_Clocks1);
		
	lab10_Test_ini(variant_num);
		
	while(1) {
		//Считываем данные
		ADC_SoftwareStartConv(ADC1);
		delay_ms(1000);
						
		Test = check_result(min, max, period);
		}	
	}

	
void SysTick_Handler(void) {
	
//	if((i += 35) > 9000) i = 2000;	//все значения увеличены в 10 раз, чтобы уйти от дробной части в формуле ниже
//	DAC_SetChannel1Data(DAC_Align_12b_R, (uint16_t)((i * 4095 + 15000)/30000));	
		
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }
	
	lab10_systick();
}
