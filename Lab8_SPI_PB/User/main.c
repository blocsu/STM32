#include "main.h"

static int8_t SPI_data;
uint8_t acc_type = LIS302DL;
static uint8_t ID;
uint32_t SysTick_CNT = 1;
static uint8_t Flag = 0;

uint8_t ver[2] = {0, 0};
uint32_t Test;
static uint8_t decision[4] = {0, 0, 0, 0};

//Функция одной передачи
int8_t writeData(uint8_t data) {
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {};
	SPI_I2S_SendData(SPI1, data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {};
	return SPI_I2S_ReceiveData(SPI1);
}

//Чтение из регистра:
uint8_t getReg(uint8_t address) {
	int8_t data=0;
	address|=(1<<7); //устанавливаем старший бит в единицу, это означает, что будет производиться чтение данных
	Lab8_data_out(address);
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	data =writeData(address);	
	data = writeData(0x00);	
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
	return data;
}

//Запись в регистр выглядит так:
void setReg(int8_t address, int8_t value){
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	writeData(address);
	writeData(value);
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
}	
	
uint8_t Accel_Read_ID(void) {
	uint8_t ctrl = getReg(0x0F);
	return ctrl;
}

int main(void) {
							
	RCC_ClocksTypeDef RCC_Clocks1;
	
	LED_init();
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock/1000); //1mc
	
	SPI_ini();
	
	setReg(0x20, 0x47);	
			
	//timer_ini();
	//usart_ini();
				
	RCC_GetClocksFreq(&RCC_Clocks1);
		
	Lab8_ini(acc_type);
	
	ID = Accel_Read_ID();
		
	while(1) {
		
//		if (getReg(0x0F) == 0x3B) {
//		Blue_ON;
//		} else Yellow_ON;
		
		SPI_data = getReg(LIS302DL_OUT_X);		
		Lab8_data_in(SPI_data);
		if (SPI_data > 45) {
		Blue_ON; Yellow_OFF;
		} else if (SPI_data < -45) {
		Blue_OFF; Yellow_ON;
		} else {
		Yellow_OFF; Blue_OFF;
		}
		SPI_data = getReg(LIS302DL_OUT_Y);		
		Lab8_data_in(SPI_data);
		if (SPI_data > 45) {
		Red_ON; Green_OFF;
		} else if (SPI_data < -45) {
		Red_OFF; Green_ON;
		} else {
		Red_OFF; Green_OFF;
		}
//		SPI_data = getReg(LIS302DL_OUT_Z);
//		delay_ms(100);		

		Test = Lab8_while();				
		get_decision(decision);
		get_version(ver);
	}	
}
	
void SysTick_Handler(void) {
		
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }	
}
	