#include "flash.h"

uint32_t flash_read(uint32_t address) {
	return (*(__IO uint32_t*) address);
}

void WriteDeviceAddress(char* data) {
	uint8_t i;
	
	FLASH_Unlock();
	FLASH_EraseSector(DEVICE_SECTOR, VoltageRange_3);
	
	for(i=0; i<12; i++) {
		FLASH_ProgramByte(DEVICE_ADDRESS+i, data[i]);
	}
	FLASH_Lock();
}

void ReadDeviceAddress(char* Dout) {
	uint32_t temp, i, j, k=0;
	
	for(i=0; i<3; i++) {
		temp = flash_read(DEVICE_ADDRESS+(i*4));
		for(j=0; j<4; j++) {
			Dout[k] = (char)((temp>>(j*8)) & 0xFF);
			k++;
		}
	}
	Dout[12] = 0;
}