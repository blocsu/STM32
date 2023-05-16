#include "main.h"

int main(void)
{
	port_ini();
	while(1)
	{
		GPIOA->ODR = (1<<PORTA0) | (1<<PORTA1);
		delay(2000000);
		GPIOA->ODR = (1<<PORTA2) | (1<<PORTA3);
		delay(2000000);
		GPIOA->ODR = (1<<PORTA4) | (1<<PORTA5);
		delay(2000000);
		GPIOA->ODR = (1<<PORTA6) | (1<<PORTA7);
		delay(2000000);
		//1000
		//0100
		//0010
		//0001
		GPIOD->ODR = (1<<PORTD12) | (1<<PORTD13);
		delay(2000000);
		GPIOD->ODR = (1<<PORTD13) | (1<<PORTD14);
		delay(2000000);
		GPIOD->ODR = (1<<PORTD14) | (1<<PORTD15);
		delay(2000000);
		GPIOD->ODR = (1<<PORTD12) | (1<<PORTD15);
		delay(2000000);
	}
}
