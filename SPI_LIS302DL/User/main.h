/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include "math.h"



#define OFF_All_LEDs GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножки светодиодов PD12/13/14/15
#define ON_All_LEDs GPIO_SetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //устанавливаем высокий уровень напряжения 1 на ножки светодиодов PD12/13/14/15

#define Green_ON GPIO_SetBits(GPIOD, GPIO_Pin_12); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD12
#define Green_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_12); //устанавливаем низкий уровень напряжения 0 на ножке светодиода PD12

#define Yellow_ON GPIO_SetBits(GPIOD, GPIO_Pin_13); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD13
#define Yellow_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_13); //устанавливаем низкий уровень напряжения 0 на ножке светодиода PD13

#define Red_ON GPIO_SetBits(GPIOD, GPIO_Pin_14); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD14
#define Red_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_14); //устанавливаем низкий уровень напряжения 0 на ножке светодиода PD14

#define Blue_ON GPIO_SetBits(GPIOD, GPIO_Pin_15); //устанавливаем высокий уровень напряжения 1 на ножке светодиода PD15
#define Blue_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_15); //устанавливаем низкий уровень напряжения 0 на ножке светодиода PD15


//Акселерометр
#define LIS302DL_OUT_X ((uint32_t)0x29)
#define LIS302DL_OUT_Y ((uint8_t)0x2B)
#define LIS302DL_OUT_Z ((uint8_t)0x2D)


const uint16_t LEDS = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
const uint16_t LED1 = GPIO_Pin_12;
const uint16_t LED2 = GPIO_Pin_13;
const uint16_t LED3 = GPIO_Pin_14;
const uint16_t LED4 = GPIO_Pin_15;
const uint32_t LIS302DL_FLAG_TIMEOUT = 0x1000;
const uint32_t PWM_PERIOD = 4000;

int main(void);
void init(void);
void loop(void);
void delay(uint32_t ms);

void initLeds(void);
void initSpi(void);
void LIS302DL_Init(void);
void initTimer(void);
void initPWM(void);

uint8_t LIS302DL_SendByte(uint8_t byte);
uint8_t LIS302DL_GetByte(void);
void LIS302DL_Write(uint8_t REG, uint8_t *DATA, uint8_t count);
void LIS302DL_Read(uint8_t REG, uint8_t *DATA, uint8_t count);
void LIS302DL_ReadACC(int32_t* out);
void LIS302DL_ReadACCY(int32_t* out);

uint32_t abs(int32_t n);
int32_t cround(int32_t x, int32_t y);

#endif /* __MAIN_H */
