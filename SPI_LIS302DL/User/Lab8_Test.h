#ifndef LAB8_TEST_H
#define LAB8_TEST_H

#include "stm32f4xx.h"
#include "stdio.h"

#define LIS3DSH					0
#define LIS302DL				1

void Lab8_ini(uint8_t acc_type);
uint32_t Lab8_while(void);
void Lab8_data_out(uint8_t variant);
void Lab8_data_in(uint8_t variant);
void get_decision(uint8_t* data);
void get_version(uint8_t* ver);

#endif
