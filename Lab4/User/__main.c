#include "stm32f4xx.h"  // Device header
#include "main.h"
#include "Lab4_Test.h"

//#define SYSCLOC 168000000U

#define TIM_EnableIT_UPDATE(TIMx) SET_BIT(TIMx->DIER, TIM_DIER_UIE)
#define TIM_EnableCounter(TIMx) SET_BIT(TIMx->CR1, TIM_CR1_CEN)
#define TIM_DisableCounter(TIMx) CLEAR_BIT(TIMx-> CR1, TIM_CR1_CEN)

__IO uint32_t SysTick_CNT = 1;
__IO uint8_t TIM2_count =0;
uint8_t TestVar;
uint32_t Test;
uint8_t *data;
uint8_t flag = 1;

//void SysTick_Init(void)
//{
//	MODIFY_REG(SysTick->LOAD,SysTick_LOAD_RELOAD_Msk, SYSCLOC/1000-1);
//	CLEAR_BIT(SysTick->VAL,SysTick_VAL_CURRENT_Msk);
//	SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk);
//}

//void delay_ms(uint32_t ms)
//{
//	MODIFY_REG(SysTick->VAL, SysTick_VAL_CURRENT_Msk, SYSCLOC/1000 - 1);
//	SysTick_CNT = ms;
//	while(SysTick_CNT) {}
//}

//static void TIM2_Init(void)
//{
//	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
//	NVIC_EnableIRQ(TIM2_IRQn);
//	WRITE_REG(TIM2->PSC, 8399);
//	WRITE_REG(TIM2->ARR, 2000);
//}

void SetSysClockTo168(void)
{
	//Enable HSE
	SET_BIT(RCC->CR, RCC_CR_HSEON);
	/*Wait till HSE is ready (��� ����� HSE ����� �����)
���� ���������� �������� ����������������� ������������ - ��������������� ���������, ����� ������� ��� ��������� HSE ��������*/
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
	//MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN, RCC_PLLCFGR_PLLN_2 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_6);
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
  RCC->PLLCFGR |= 0x402A04;
  MODIFY_REG(RCC->CFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLSRC_HSI, RCC_PLLCFGR_PLLSRC_HSE);

	SET_BIT(RCC->CR, RCC_CR_PLLON);
	while(READ_BIT(RCC->CR, RCC_CR_PLLRDY)!= (RCC_CR_PLLRDY)) {}
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != (RCC_CFGR_SWS_PLL)) {}
}


int main(void)
	{
		GPIO_InitTypeDef GPIO_struct_LED; //�������������� ���������� GPIO_struct_LED � ����� ��������� GPIO_InitTypeDef
		GPIO_InitTypeDef GPIO_struct_Button; //�������������� ���������� GPIO_struct_Button � ����� ��������� GPIO_InitTypeDef
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //�������� ������������ ����� D
		
		GPIO_struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //������������� ��������� � ����������� �� ������ 12-15
		GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT; //�������� ����� 12-15 �� �����
		GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed; //��������� �������� LOW �� ��������������� ����� �����*/
		GPIO_struct_LED.GPIO_OType = GPIO_OType_PP; //������� ������������ ������������� �� ���� ����
		GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;//���� �������� ������������ ��� ��������� ����� �� ����, ������� ���������� ��� �� ���������
		
		GPIO_Init(GPIOD, &GPIO_struct_LED); //�������������� ���� D
		
				
		TIM2_Init();
		TIM_EnableIT_UPDATE(TIM2);
		TIM_EnableCounter(TIM2);

		TestVar = Lab4_Test_ini("Dotsenko");

						
		RCC_ClocksTypeDef RCC_Clocks1;
		
				
		SetSysClockTo168();
		//SysTick_Init();
		
		SystemCoreClockUpdate();
		
		SysTick_Config(SystemCoreClock /1000);//
		
				
		RCC_GetClocksFreq(&RCC_Clocks1);
		
		while(1)
		{
			if(flag == 1) 
			{
				flag = 0;
			
			  switch(TIM2_count)
						{
							case 0:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
							  SysTick_CNT = 4100;
							  break;
							case 3:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
							  SysTick_CNT = 200;
							  break;
							case 5:	
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
							  SysTick_CNT = 2000;
							  break;
							case 1:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_13); //������������� ������� ������� ���������� 1 �� ����� ���������� PD13
							  SysTick_CNT = 100;
							  break;
							case 6:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_13); //������������� ������� ������� ���������� 1 �� ����� ���������� PD13
							  SysTick_CNT = 3800;
							  break;
							case 2:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_14); //������������� ������� ������� ���������� 1 �� ����� ���������� PD14
							  SysTick_CNT = 4100;
							  break;
							case 4:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_15); //������������� ������� ������� ���������� 1 �� ����� ���������� PD15
							  SysTick_CNT = 1000;
							  break;
							case 7:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_15); //������������� ������� ������� ���������� 1 �� ����� ���������� PD15
							  SysTick_CNT = 2800;
							  break;
							
						}
						
						if(TIM2_count<7) TIM2_count++;
						else TIM2_count=0;
				
			}
			Test = read_flag(data);
		}
		
				
	}
	
	void SysTick_Handler(void)
		{
			if(SysTick_CNT > 0) 
			{
				SysTick_CNT--;
				if(SysTick_CNT == 0)
				{
					flag = 1;
				}
//			}else {
//			  switch(TIM2_count)
//						{
//							case 0:
//								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
//								GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
//							  SysTick_CNT = 41000;
//							  break;
//							case 3:
//								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
//								GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
//							  SysTick_CNT = 2000;
//							  break;
//							case 5:	
//								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
//								GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
//							  SysTick_CNT = 20000;
//							  break;
//							case 1:
//								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
//								GPIO_SetBits(GPIOD, GPIO_Pin_13); //������������� ������� ������� ���������� 1 �� ����� ���������� PD13
//							  SysTick_CNT = 1000;
//							  break;
//							case 6:
//								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
//								GPIO_SetBits(GPIOD, GPIO_Pin_13); //������������� ������� ������� ���������� 1 �� ����� ���������� PD13
//							  SysTick_CNT = 38000;
//							  break;
//							case 2:
//								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
//								GPIO_SetBits(GPIOD, GPIO_Pin_14); //������������� ������� ������� ���������� 1 �� ����� ���������� PD14
//							  SysTick_CNT = 41000;
//							  break;
//							case 4:
//								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
//								GPIO_SetBits(GPIOD, GPIO_Pin_15); //������������� ������� ������� ���������� 1 �� ����� ���������� PD15
//							  SysTick_CNT = 10000;
//							  break;
//							case 7:
//								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
//								GPIO_SetBits(GPIOD, GPIO_Pin_15); //������������� ������� ������� ���������� 1 �� ����� ���������� PD15
//							  SysTick_CNT = 28000;
//							  break;
//							
//						}
//						
//						if(TIM2_count<7) TIM2_count++;
//						else TIM2_count=0;
				
			}
//			Test = read_flag(data);
		}
	
//	void TIM2_IRQHandler(void)
//		{
//			if(READ_BIT(TIM2->SR, TIM_SR_UIF))
//			{
//				CLEAR_BIT(TIM2->SR, TIM_SR_UIF);				
//			}
//		}
