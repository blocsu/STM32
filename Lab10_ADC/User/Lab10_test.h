#ifndef LAB10_TEST_H
#define LAB10_TEST_H

#include "stm32f4xx.h"
#include "stdio.h"

void lab10_Test_ini(uint8_t variant_num);
void lab10_systick(void);
uint32_t check_result(uint16_t min, uint16_t max, uint16_t period);

#endif
