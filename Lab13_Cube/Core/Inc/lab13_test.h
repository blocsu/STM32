#ifndef LAB13_TEST_H
#define LAB13_TEST_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rng.h"
#include "stdio.h"

uint32_t lab13_get_result(void);
uint8_t lab13_while(uint8_t* test_out);
void lab13_test_ini(void);

#endif
