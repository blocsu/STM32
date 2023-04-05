#include "stm32f4xx.h"  // Device header
#include "main.h"

#define SYSCLOC 168000000U

#define TIM_EnableIT_UPDATE(TIMx) SET_BIT(TIMx->DIER, TIM_DIER_UIE)
#define TIM_EnableCounter(TIMx) SET_BIT(TIMx->CR1, TIM_CR1_CEN)
#define TIM_DisableCounter(TIMx) CLEAR_BIT(TIMx-> CR1, TIM_CR1_CEN)

static void TIM2_Init(void)
{
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
	NVIC_EnableIRQ(TIM2_IRQn);
	WRITE_REG(TIM2->PSC, 3599);
	WRITE_REG(TIM2->ARR, 2000);
}

void SetSysClockTo168(void)
{
	//Enable HSE
	SET_BIT(RCC->CR, RCC_CR_HSEON);
	/*Wait till HSE is ready (∆дЄм когда HSE будет готов)
‘лаг готовности внешнего высокоскоростного тактировани€ - устанавливаетс€ аппаратно, чтобы указать что генератор HSE стабилен*/
	while(READ_BIT(RCC->CR, RCC_CR_HSERDY == RESET)){}
	//Enable Prefeth Buffer
	CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_5WS);
	MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV2);
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV4);
	MODIFY_REG(RCC->CR, RCC_CR_CSSON, RCC_CR_CSSON);
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
	//RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3;
	//MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN, RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_7);
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
  RCC->PLLCFGR |= 0x402A04;
  MODIFY_REG(RCC->CFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLSRC_HSI, RCC_PLLCFGR_PLLSRC_HSE);

	SET_BIT(RCC->CR, RCC_CR_PLLON);
	while(READ_BIT(RCC->CR, RCC_CR_PLLRDY)!= (RCC_CR_PLLRDY)) {}
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != (RCC_CFGR_SWS_PLL)) {}
}


//uint8_t TestVar;
//uint32_t Test;
uint8_t *decision;
uint8_t tim6_count = 0;
uint8_t User_Button = 0;
uint16_t Count_Of_Button = 0;
uint8_t Button_State = 0;
uint8_t Flag = 0;
int Rattle_Of_Button(void); 

int Rattle_Of_Button(void) 
			{
				if(User_Button == Bit_SET) 
          {
						if(Count_Of_Button < 1700)
						{
							Count_Of_Button++;
						}else {
							if(User_Button == Bit_SET) {
								User_Button = Bit_SET;
								return 1;
							}
						}
					}else {
						if(Count_Of_Button > 0) 
							{
								Count_Of_Button--;
							}else {
								User_Button = Bit_RESET;
								return 0;
							}
					}
			}


int main(void)
	{
		GPIO_InitTypeDef GPIO_struct_LED; //инициализируем переменную GPIO_struct_LED с типом структуры GPIO_InitTypeDef
		GPIO_InitTypeDef GPIO_struct_Button; //инициализируем переменную GPIO_struct_Button с типом структуры GPIO_InitTypeDef
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //включаем тактирование порта D
		
		GPIO_struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //конфигурируем структуру с параметрами на ножках 12-15
		GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT; //включаем ножки 12-15 на выход
		GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
		GPIO_struct_LED.GPIO_OType = GPIO_OType_PP; //включем одт€гивающее сопротивление на весь порт
		GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;//этот параметр используетс€ при включении порта на вход, поэтому установили его по умолчанию
		
		GPIO_Init(GPIOD, &GPIO_struct_LED); //инициализируем порт D
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //включаем тактирование порта A
		
		GPIO_struct_Button.GPIO_Pin = GPIO_Pin_0; //конфигурируем структуру с параметрами на ножке PA0
		GPIO_struct_Button.GPIO_Mode = GPIO_Mode_IN; //включаем ножку PA0 на вход
		GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
		GPIO_struct_Button.GPIO_OType = GPIO_OType_PP; //включем одт€гивающее сопротивление на весь порт
		GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;//этот параметр используетс€ при включении порта на вход, поэтому установили его по умолчанию
		
		GPIO_Init(GPIOA, &GPIO_struct_Button); //инициализируем порт A
		
		TIM2_Init();
		TIM_EnableIT_UPDATE(TIM2);
		TIM_EnableCounter(TIM2);

		//TestVar = Lab3_Test_ini("Dotsenko");

		//SystemCoreClockUpdate();
		
				
		RCC_ClocksTypeDef RCC_Clocks1;
		
				
		SetSysClockTo168();
		

		
		RCC_GetClocksFreq(&RCC_Clocks1);
		
		while(1)
		{
			//Test = while_Test(decision);
			User_Button = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
			Button_State = Rattle_Of_Button();
			
				if(Button_State == Bit_SET)
					{
						if(Flag == 0)
						{
							Flag = 1;
						switch(tim6_count)
						{
							case 0:
							case 3:
							case 5:	
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напр€жени€ 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напр€жени€ 1 на ножке светодиода PD12
							  break;
							case 1:
							case 6:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напр€жени€ 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_13); //устанавливаем высокий уровень напр€жени€ 1 на ножке светодиода PD13
							  break;
							case 2:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напр€жени€ 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_14); //устанавливаем высокий уровень напр€жени€ 1 на ножке светодиода PD14
							  break;
							case 4:
							case 7:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напр€жени€ 0 на ножку светодиода PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_15); //устанавливаем высокий уровень напр€жени€ 1 на ножке светодиода PD15
							  break;
							default:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
							  break;
						}
						delay(47000);
						if(tim6_count<7) tim6_count++;
						else tim6_count=0;
					}
						
				}else Flag = 0;
			
		}
		
		
	}
	
	void TIM2_IRQHandler(void)
		{
		}
