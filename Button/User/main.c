  #include "main.h"

//#define TIM_EnableIT_UPDATE(TIMx) SET_BIT(TIMx->DIER, TIM_DIER_UIE)
//#define TIM_EnableCounter(TIMx) SET_BIT(TIMx->CR1, TIM_CR1_CEN)
//#define TIM_DisableCounter(TIMx) CLEAR_BIT(TIMx-> CR1, TIM_CR1_CEN)

static __IO uint32_t SysTick_CNT = 0;
static __IO uint8_t i = 7;
static uint8_t Flag = 0;

uint8_t TestVar;
uint32_t Test;
static uint8_t data[3] = {0, 0, 0};

static uint16_t Button_Press = 0;
static uint16_t Button_State = 0;
static uint8_t  Button_Count = 1;

int main(void) {	
							
	RCC_ClocksTypeDef RCC_Clocks1;
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock/1000);
				
	//RCC_GetClocksFreq(&RCC_Clocks1);
	
	LED_init();
		
	while(1) {
		
		Test = while_Test(data);

		if(Button_Press) {
			Button_Press = 0;
			
			if(++i == 8) i = 0;
			
			switch(i) {
				case 0:
					OFF_All_LEDs
					Green_ON						
					break;
							
				case 1:
					OFF_All_LEDs
					Yellow_ON
					break;
							
				case 2:
					OFF_All_LEDs
					Red_ON
					break;
							
				case 3:
					OFF_All_LEDs
					Green_ON
					break;
							
				case 4:
					OFF_All_LEDs
					Blue_ON
					break;
							
				case 5:	
					OFF_All_LEDs
					Green_ON
					break;
							
				case 6:
					OFF_All_LEDs
					Yellow_ON
					break;
							
				case 7:
					OFF_All_LEDs
					Blue_ON
					break;
			}
		}				
	}
}
	
void SysTick_Handler(void) {
  if(SysTick_CNT) if(--SysTick_CNT == 0) Flag = 1;
	// Опрос кнопки
//	if(--Button_Count == 0) {
//		Button_Count = 10;
//		uint8_t new_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
//		if(new_state) {					
//			if(new_state != Button_State) Button_Press = 1;						
//		}
//	  Button_State = new_state;
//	}
	
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
		if(Button_Count < 5) {
			Button_Count++;
		}else if(Button_State == 0) {Button_State = 1; Button_Press = 1;}
	}else {
		if(Button_Count > 0) {
			Button_Count--;
		}else if(Button_State == 1) Button_State = 0;
	}
	
//	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))	{
//		if (Button_Count < 5)	{
//			Button_Count++;
//		} else {
//			if (Button_State == 0) {
//				Button_State=1;
//				Button_Press = 1;
//			}
//		}
//	} else {
//		if (Button_Count > 0)	{
//			Button_Count--;
//		}else{
//			if (Button_State == 1)	{
//				Button_State=0;
//			}
//		}
//	}
	
	TestVar = Lab5_Test_ini("Dotsenko");
}
	