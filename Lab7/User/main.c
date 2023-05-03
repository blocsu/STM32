#include "main.h"

static uint8_t i;
static uint8_t flag = 0;
static uint8_t N = 0;
static uint8_t data;
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

void USART2_IRQHandler(void) {
	if (USART_GetITStatus(USART2, USART_IT_TXE) == 1) {
		USART_ClearITPendingBit(USART2, USART_IT_TXE);
		
		if (count == count_size) {
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
			count = 0;
		}
		else {
			USART_SendData(USART2, TX_Buffer[count]);
			count++;
		}
	}
	
	// oбработка событи¤ RXNE (приЄма)
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == 1) { 
		USART_ClearITPendingBit(USART2, USART_IT_RXNE); //сброшен флаг - очистка бина прерывани¤		
		RX_Buffer[RX_wr] = USART_ReceiveData(USART2); //прин¤ли байт
		RX_wr++;
		if(++RX_count == 1) { SysTick_CNT = 1; Flag = 0; }
	}
}

//void Get_cmd(void) {
//	while(1) {
//		while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == 0) { }
//		cmd = USART_ReceiveData(USART2);
//		SysTick_CNT = 1;
//		Flag = 0;
//		while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == 0 && Flag == 0) { }  
//		data = USART_ReceiveData(USART2);
//		if (Flag == 0) break;
//	}
//}

//void Send_cmd(void) {
//	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0) { }
//	USART_SendData(USART2, cmd);
//	
//	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0) { }  
//	USART_SendData(USART2, data);
//}
void  Send_Buffer_Init(uint32_t data_size){
	count_size = data_size;
	
	USART_SendData(USART2, TX_Buffer[0]);
	count++;

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

int main(void) {
							
	RCC_ClocksTypeDef RCC_Clocks1;
	
	LED_init();
				
	SetSysClockTo168();
		
	SystemCoreClockUpdate();
		
	SysTick_Config(SystemCoreClock/1000);
	
	//timer_ini();
	usart_ini();
				
	RCC_GetClocksFreq(&RCC_Clocks1);
		
	TestVar = lab7_test_ini("Dotsenko");
		
	while(1) {
		
		//Get_cmd();
		if(RX_count > 1) {
			if(Flag == 0) {
				TX_Buffer[0] = RX_Buffer[RX_rd++];
				TX_Buffer[1] = RX_Buffer[RX_rd++];
				
				switch(TX_Buffer[0]) {
				case 0x01:
					Send_Buffer_Init(2);			  
					break;

				case 0x02:
					N = TX_Buffer[1];				  
					if(N < 8) {
						while(N) {
						if (i == 7) {
							i = 0;
						} else i++;
						N--;
					 }
					}
					flag = 1;				
					break;
				
				case 0x03:
					N = TX_Buffer[1];				  
					while(N) {
						if (i == 0) {
							i = 7;
						} else i--;
						N--;
					}
					flag = 1;				
					break;
				case 0x06:
					i = TX_Buffer[1];			  
					flag = 1;				
					break;
				case 0x07:				
					TX_Buffer[1] = i;
					Send_Buffer_Init(2);
					break;
				case 0x08:				
					TX_Buffer[1] = Button_State;
					Send_Buffer_Init(2);
					break;
			 }
			}
			RX_count = 0;
		}
		
		if (flag) {
			flag = 0;							
		
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
		Test = while_test(decision);
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
	
	test_systick();
}
	