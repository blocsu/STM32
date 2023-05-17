 #include "main.h"
 
static uint32_t SysTick_CNT = 5000;
static uint8_t Flag = 0;
static uint16_t min = 5000, max = 0, period=0;
static uint16_t ADC_result;
static uint16_t Buffer[5000];
static uint16_t i = 0;
static uint8_t variant_num;
static uint32_t Test;

uint16_t mtime[2] = {0};

void SysTick_Handler(void);

//Функция прерывания
void ADC_IRQHandler(void);
void ADC_IRQHandler(void)
{
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	ADC_result = ADC_GetConversionValue(ADC1);
	Buffer[i] = 330 * (ADC_result * 100) / 40950;
	if(++i == 5000) i = 0;
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
		if(Flag) {
		  uint16_t sind = 0,
				   mind = 0;
		  
			Flag = 0;
			
			do {
				if(Buffer[sind] < min) min = Buffer[sind];
				if(Buffer[sind] > max) max = Buffer[sind];
				
				if(Buffer[sind] > Buffer[sind+1] + 500) mtime[mind++] = sind;
				if(mind == 2) break;
			} while(++sind < 4999);
			
			period = mtime[1] - mtime[0];
		}
						
		Test = check_result(min, max, period);
		}	
	}

	
void SysTick_Handler(void) {
	//Считываем данные
	ADC_SoftwareStartConv(ADC1);
		
//	if((i += 35) > 9000) i = 2000;	//все значения увеличены в 10 раз, чтобы уйти от дробной части в формуле ниже
//	DAC_SetChannel1Data(DAC_Align_12b_R, (uint16_t)((i * 4095 + 15000)/30000));	
		
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }
	
	lab10_systick();
}


