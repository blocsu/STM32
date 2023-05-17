 #include "main.h"
 
static uint32_t SysTick_CNT = 0;
static uint8_t Flag = 0;
uint8_t enc_a=0, enc_b=0, count_a=0, count_b=0;
uint8_t ab=0, encoder_state=0;
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
		
	Lab12_Test_ini();
		
	while(1) {
		if (encoder_state == 1)
		{
				Green_ON;
				Blue_OFF;
		}
		else if (encoder_state == 2)
		{
				Green_OFF;
				Blue_ON;
		}
		encoder_state = 0;
		
		if (ENC_BUTTON() == 0)
		{
			Red_ON;
		}
		else
		{
			Red_OFF;
		}
						
		Test = lab12_main();
		}	
	}

	
void SysTick_Handler(void) {

	if(SysTick_CNT) if(--SysTick_CNT == 0) Flag = 1;
	
	if (delay_count > 0)
	{
		delay_count--;
	}
	//----------------------
	if (ENC_A() == 1)
	{
		if (count_a < ENC_DELAY){count_a++;}
		else 
		{
			enc_a = 1;
			if (enc_b == 1) {ab = 0;}
		}
	}
	else
	{
		if (count_a > 0){count_a--;}
		else 
		{
			enc_a = 0;
			if (ab == 0){ab = 1;}
			else {if(ab == 1) {encoder_state = 1;ab = 2;}}	
		}
	}
	//----------------------
	if (ENC_B() == 1)
	{
		if (count_b < ENC_DELAY){count_b++;}
		else {enc_b = 1; if (enc_a == 1) {ab = 0;}}
	}
	else
	{
		if (count_b > 0){count_b--;}
		else 
		{
			enc_b = 0;
			if (ab == 0){ab = 1;}
			else { if(ab == 1) {encoder_state = 2;ab = 2;}}
		}
	}
	
	lab12_systick();
}


