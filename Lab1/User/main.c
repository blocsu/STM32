#include "stm32f4xx.h"                  // Device header

int main(void)
	{
		RCC_ClocksTypeDef RCC_Clocks1;
		
		RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);
		
		RCC_GetClocksFreq(&RCC_Clocks1);
		
		while(1)
		{
			
		}
	}
