 #include "main.h"
 
static uint32_t SysTick_CNT = 5000;
static uint8_t Flag = 0;
static uint16_t min=5000, max=0, period=0;
static uint16_t ADC_result;
static uint16_t Buffer[5000];
static uint16_t count = 0;
static uint16_t start = 0;
static uint16_t stop = 0;
static uint16_t i = 0;
static uint8_t variant_num;
static uint32_t Test;

uint16_t min_mv(void);
uint16_t max_mv(void);
uint16_t period_ms(void);

uint16_t min_mv(void) {
	min = Buffer[0];    
	for(uint16_t j=0; j < sizeof(Buffer)/2; j++) {
			if(Buffer[j] < min) {
					min = Buffer[j];
			}
	}
	return min;
}

uint16_t max_mv(void) {
	max = Buffer[0];    
	for(uint16_t j=0; j < sizeof(Buffer)/2; j++) {
			if(Buffer[j] > max) {
					max = Buffer[j];
			}
	}
	return max;
}

uint16_t period_ms(void) {
	for(uint16_t j=0; j < sizeof(Buffer)/2; j++) {
	 if(Buffer[j] == min) {
		 start = j;
		 for(++j; j < sizeof(Buffer)/2; j++) {
			 if(Buffer[j] == min) stop = j;
		 }
	 }
	 period = stop - start;
	}
	return period;
}

void SysTick_Handler(void);

//Функция прерывания
void ADC_IRQHandler(void);
void ADC_IRQHandler(void)
{
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	ADC_result = ADC_GetConversionValue(ADC1);
	Buffer[i] = 300 * (ADC_result * 100) / 40950;
	i++;
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
		
		//delay_ms(10000);
		
		if(Flag) {
			Flag = 0;
			
			max_mv();
			min_mv();
			period_ms();
		}
						
		Test = check_result(min, max, period);
		}	
	}

	
void SysTick_Handler(void) {
	//Считываем данные
	ADC_SoftwareStartConv(ADC1);
	count++;
		
//	if((i += 35) > 9000) i = 2000;	//все значения увеличены в 10 раз, чтобы уйти от дробной части в формуле ниже
//	DAC_SetChannel1Data(DAC_Align_12b_R, (uint16_t)((i * 4095 + 15000)/30000));	
		
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }
	
	lab10_systick();
	
	if (delay_count > 0) delay_count--;
}


