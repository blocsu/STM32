#ifndef FLASH_H_
#define FLASH_H_

#include "stm32f4xx.h"

#define DEVICE_ADDRESS 0x08007F00
#define DEVICE_SECTOR FLASH_Sector_1

uint32_t flash_read(uint32_t address);
void WriteDeviceAddress(uint8_t data);
void ReadDeviceAddress(char* Dout);



#endif /*FLASH_H_*/
