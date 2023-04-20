#include "stm32f4xx.h"  // Device header
#include "main.h"
#include "init.h"
#include "timers.h"
#include "Lab6_Test.h"


static __IO uint8_t i;

uint8_t TestVar;
uint32_t Test;
static uint16_t data[2] = {0, 0};


static void SetSysClockTo168(void) {
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
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV8);
	MODIFY_REG(RCC->CR, RCC_CR_CSSON, RCC_CR_CSSON);
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3;
	MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN, RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_6);
	//RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
  //RCC->PLLCFGR |= 0x402A04;
  MODIFY_REG(RCC->CFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLSRC_HSI, RCC_PLLCFGR_PLLSRC_HSE);

	SET_BIT(RCC->CR, RCC_CR_PLLON);
	while(READ_BIT(RCC->CR, RCC_CR_PLLRDY)!= (RCC_CR_PLLRDY)) {}
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != (RCC_CFGR_SWS_PLL)) {}
}


int main(void) {
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
		
	GPIO_struct_Button.GPIO_Pin   = GPIO_Pin_2; //конфигурируем структуру с параметрами на ножке PA2
	GPIO_struct_Button.GPIO_Mode  = GPIO_Mode_OUT; //включаем ножку PA2 на выход
	GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed; //установим скорость LOW на конфигурируемые ножки порта*/
	GPIO_struct_Button.GPIO_OType = GPIO_OType_PP; //включем одт€гивающее сопротивление на весь порт
	GPIO_struct_Button.GPIO_PuPd  = GPIO_PuPd_NOPULL;//этот параметр используетс€ при включении порта на вход, поэтому установили его по умолчанию
	GPIO_Init(GPIOA, &GPIO_struct_Button); //инициализируем порт A
							
	RCC_ClocksTypeDef RCC_Clocks1;
	
	//LED_init();
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock/1000);
	
	timer_ini();
				
	RCC_GetClocksFreq(&RCC_Clocks1);
		
	while(1) {
		
		Test = while_Test(data);

						
		TestVar = Lab6_Test_ini("Dotsenko");
	}
}
	
void SysTick_Handler(void) {
	
}
	