#include "main.h"

static uint8_t i;
static uint8_t flag = 0;
static uint8_t N = 0;
static uint8_t SPI_data;
uint8_t acc_type = LIS302DL;
//uint8_t address;
static uint8_t cmd;
uint32_t count;
uint32_t count_size;
uint8_t TX_Buffer[256];

static uint16_t Button_Press = 0;
static uint16_t Button_State = 0;
static uint8_t  Button_Count = 10;
uint32_t SysTick_CNT = 1;
static uint8_t Flag = 0;

uint8_t RX_Buffer[256];
static uint8_t RX_wr = 0;
static uint8_t RX_rd = 0;
static uint8_t RX_count = 0;

uint8_t TestVar;
uint32_t Test;
static uint8_t decision[4] = {0, 0, 0, 0};

//Функция одной передачи
uint8_t writeData(uint8_t data) {
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {};
	SPI_I2S_SendData(SPI1, data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {};
	return SPI_I2S_ReceiveData(SPI1);
}

//Чтение из регистра:
uint8_t getReg(uint8_t address) {
	uint8_t data=0;
	address|=(1<<7); //устанавливаем старший бит в единицу, это означает, что будет производиться чтение данных
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	writeData(address);
	data = writeData(0x00);
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
	return data;
}

//Запись в регистр выглядит так:
void setReg(uint8_t address, uint8_t value){
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	writeData(address);
	writeData(value);
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
}
	
	
uint8_t Accel_Read_ID(void) {
	uint8_t ctrl = 0x00;
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
		
	//TestVar = Lab8_ini("Dotsenko");
		
	while(1) {
		
		if (getReg(0x0F) == 0x3F) {
		Blue_ON;
		} else Yellow_ON;
		
//		SPI_data = getReg(LIS302DL_OUT_X);
//		if (SPI_data > 10) {
//		Blue_ON; Yellow_OFF;
//		} else if (SPI_data < -10) {
//		Blue_OFF; Yellow_ON;
//		} else {
//		Yellow_OFF; Blue_OFF;
//		}
//		SPI_data = getReg(LIS302DL_OUT_Y);
//		if (SPI_data > 10) {
//		Red_ON; Green_OFF;
//		} else if (SPI_data < -10) {
//		Red_OFF; Green_ON;
//		} else {
//		Red_OFF; Green_OFF;
//		}
//		SPI_data = getReg(LIS302DL_OUT_Z);
//		delay_ms(100);
		
		
		//Test = while_test(decision);
	}	
}
	
void SysTick_Handler(void) {
	// Опрос кнопки
	if(--Button_Count == 0) {
	  uint8_t new_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	  
		Button_Count = 10;
		
		if(new_state != Button_State) { //Если текущее состояние не совпадает с предыдущим, то проваливаемся дальше
			if(new_state == Bit_SET) Button_Press = 1;

			Button_State = new_state;	//Приравниваем текущее состояние предыдущему		
		}
	}
	
	if(SysTick_CNT) { if(--SysTick_CNT == 0) Flag = 1; }	
}
	