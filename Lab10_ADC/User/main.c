 #include "main.h"
 
static uint32_t SysTick_CNT = 1;
static uint8_t Flag = 0;
static uint16_t min=300, max=500, period=1/2;
static uint16_t ADC_result;
static uint16_t Buffer[256];
static uint16_t delay_count=0;
static uint8_t i = 0;
static uint8_t variant_num;
static uint32_t Test;

void SysTick_Handler(void);

void delay_ms(uint16_t delay_temp);
void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;
	
	while(delay_count){}
}

//Функция прерывания
void ADC_IRQHandler(void);
void ADC_IRQHandler(void)
{
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	ADC_result = ADC_GetConversionValue(ADC1);
	//sprintf(str, "V=%d mv", ADC_result);
	Buffer[i] = 330 * (ADC_result * 100) / 40950;
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
		//Считываем данные
		ADC_SoftwareStartConv(ADC1);
		delay_ms(1000);
		
		min = Buffer[0];    
    for(uint8_t j=0; j < sizeof(Buffer)/4; j++) {
        if(Buffer[j] < min) {
            min = Buffer[j];
        }
    }
		
		max = Buffer[0];    
    for(uint8_t j=0; j < sizeof(Buffer)/4; j++) {
        if(Buffer[j] > max) {
            max = Buffer[j];
        }
    }
						
		Test = check_result(min, max, period);
		}	
	}

	
void SysTick_Handler(void) {
	
//	if((i += 35) > 9000) i = 2000;	//все значения увеличены в 10 раз, чтобы уйти от дробной части в формуле ниже
//	DAC_SetChannel1Data(DAC_Align_12b_R, (uint16_t)((i * 4095 + 15000)/30000));	
		
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }
	
	lab10_systick();
	
	if (delay_count > 0)
	{
		delay_count--;
	}
}


