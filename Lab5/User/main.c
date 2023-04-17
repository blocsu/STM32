#include "stm32f4xx.h"  // Device header
#include "main.h"
#include "Lab5_Test.h"

//#define SYSCLOC 168000000U

//#define TIM_EnableIT_UPDATE(TIMx) SET_BIT(TIMx->DIER, TIM_DIER_UIE)
//#define TIM_EnableCounter(TIMx) SET_BIT(TIMx->CR1, TIM_CR1_CEN)
//#define TIM_DisableCounter(TIMx) CLEAR_BIT(TIMx-> CR1, TIM_CR1_CEN)

__IO uint32_t SysTick_CNT = 0;
__IO uint8_t i = 0;
uint8_t TestVar;
uint32_t Test;
uint8_t data[3] = {0, 0, 0};
uint8_t flag = 1;
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


int main(void) {
	GPIO_InitTypeDef GPIO_struct_LED; //�������������� ���������� GPIO_struct_LED � ����� ��������� GPIO_InitTypeDef
	GPIO_InitTypeDef GPIO_struct_Button; //�������������� ���������� GPIO_struct_Button � ����� ��������� GPIO_InitTypeDef
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //�������� ������������ ����� D
		
	GPIO_struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //������������� ��������� � ����������� �� ������ 12-15
	GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT; //�������� ����� 12-15 �� �����
	GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed; //��������� �������� LOW �� ��������������� ����� �����*/
	GPIO_struct_LED.GPIO_OType = GPIO_OType_PP; //������� ������������ ������������� �� ���� ����
	GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;//���� �������� ������������ ��� ��������� ����� �� ����, ������� ���������� ��� �� ���������
		
	GPIO_Init(GPIOD, &GPIO_struct_LED); //�������������� ���� D
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //�������� ������������ ����� A
		
	GPIO_struct_Button.GPIO_Pin = GPIO_Pin_0; //������������� ��������� � ����������� �� ����� PA0
	GPIO_struct_Button.GPIO_Mode = GPIO_Mode_IN; //�������� ����� PA0 �� ����
	GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed; //��������� �������� LOW �� ��������������� ����� �����*/
	GPIO_struct_Button.GPIO_OType = GPIO_OType_PP; //������� ������������ ������������� �� ���� ����
	GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;//���� �������� ������������ ��� ��������� ����� �� ����, ������� ���������� ��� �� ���������
	
	GPIO_Init(GPIOA, &GPIO_struct_Button); //�������������� ���� A

							
	RCC_ClocksTypeDef RCC_Clocks1;
		
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock /1000);
				
	//RCC_GetClocksFreq(&RCC_Clocks1);
		
		while(1) {
			
			Test = while_Test(data);
			
			User_Button = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
			Button_State = Rattle_Of_Button();
			
			if(Button_State == Bit_SET) {
				if(Flag == 0)  {
					Flag = 1;
					
					if (flag == 1) {
							flag = 0;
							switch(i) {
							case 0:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
								//SysTick_CNT = 4100;
								break;
										
							case 1:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_13); //������������� ������� ������� ���������� 1 �� ����� ���������� PD13
								//SysTick_CNT = 100;
								break;
										
							case 2:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_14); //������������� ������� ������� ���������� 1 �� ����� ���������� PD14
								//SysTick_CNT = 4100;
								break;
										
							case 3:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
								//SysTick_CNT = 200;
								break;
										
							case 4:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_15); //������������� ������� ������� ���������� 1 �� ����� ���������� PD15
								//SysTick_CNT = 1000;
								break;
										
							case 5:	
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_12); //������������� ������� ������� ���������� 1 �� ����� ���������� PD12
								//SysTick_CNT = 2000;
								break;
										
							case 6:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_13); //������������� ������� ������� ���������� 1 �� ����� ���������� PD13
								//SysTick_CNT = 3800;
								break;
										
							case 7:
								GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //������������� ������ ������� ���������� 0 �� ����� ���������� PD12/13/14/15
								GPIO_SetBits(GPIOD, GPIO_Pin_15); //������������� ������� ������� ���������� 1 �� ����� ���������� PD15
								//SysTick_CNT = 2800;
								break;
						}
						//delay(700000);
						SysTick_CNT = 50;
						TestVar = Lab5_Test_ini("Dotsenko");
						if(++i == 8) i = 0;		
					}							
			  }
			}else Flag = 0;
						
		}
}
	
void SysTick_Handler(void) {
	if(SysTick_CNT) { if(--SysTick_CNT == 0) flag = 1; }

}
	