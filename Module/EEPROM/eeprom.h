#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "bsp_iic.h"
#include "error_handle.h"

#define EEPROM_ADDR 0x50 //1010000
#define EEPROM_PORT_INDEX 1

error_handle_type EEPROM_Write_Byte(software_IIC_Port* port, uint16_t addr_eeprom, uint8_t data);
error_handle_type EEPROM_Read_Byte(software_IIC_Port* port, uint16_t addr_eeprom, uint8_t* rxbuf);

void EEPROM_Init(void);

#endif