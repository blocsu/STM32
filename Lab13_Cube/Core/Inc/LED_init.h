#ifndef LED_init_H_
#define LED_init_H_

#include "stm32f4xx.h"

#define OFF_All_LEDs HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов PD12/13/14/15
#define ON_All_LEDs HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов PD12/13/14/15

#define Green_ON HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD12
#define Green_OFF HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); //устанавливаем низкий уровень напряжения 0 на ножке светодиода PD12

#define Yellow_ON HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD13
#define Yellow_OFF HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET); //устанавливаем низкий уровень напряжения 0 на ножке светодиода PD13

#define Red_ON HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD14
#define Red_OFF HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); //устанавливаем низкий уровень напряжения 0 на ножке светодиода PD14

#define Blue_ON HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD15
#define Blue_OFF HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET); //устанавливаем низкий уровень напряжения 0 на ножке светодиода PD15

void LED_init(void);

#endif /*LED_init_H_*/
