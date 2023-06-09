#include "stm32f4xx.h"                  // Device header

void RCC_deInit(void)
{
	SET_BIT(RCC->CR, RCC_CR_HSION);
	while(READ_BIT(RCC->CR, RCC_CR_HSIRDY == RESET)) {}
	MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U);
	CLEAR_REG(RCC->CFGR);
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS != RESET)) {}	
	CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
	while(READ_BIT(RCC->CR, RCC_CR_PLLRDY != RESET)) {}	
	CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);
	while(READ_BIT(RCC->CR, RCC_CR_HSERDY != RESET)) {}	
	CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
	//Reset all CSR flags
	SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}

void SetSysClockTo168(void)
{
	SET_BIT(RCC->CR, RCC_CR_HSEON);
	while(READ_BIT(RCC->CR, RCC_CR_HSERDY == RESET)){}
	//Enable Prefeth Buffer
	CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2WS);
	MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV1);
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV2);
  MODIFY_REG(RCC->CFGR, RCC_PLLCFGR_PLLSRC /*| RCC_PLLCFGR_PLLXTPRE | RCC_CFGR_PLLMULL*/, RCC_PLLCFGR_PLLSRC /*| RCC_CFGR_PLLMULL9*/);
	SET_BIT(RCC->CR, RCC_CR_PLLON);
	while(READ_BIT(RCC->CR, RCC_CR_PLLRDY)!= (RCC_CR_PLLRDY)) {}
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != (RCC_CFGR_SWS_PLL)) {}
}

int main(void)
	{

		//SystemCoreClock = HSE_VALUE;
		SystemCoreClockUpdate();
		
				
		RCC_ClocksTypeDef RCC_Clocks1;
		
		RCC_deInit();
		
		SetSysClockTo168();
		
		RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);

		
		RCC_GetClocksFreq(&RCC_Clocks1);
		
		while(1)
		{
			
		}
	}
