#ifndef _EEPROM_H_
#define _EEPROM_H_

#define EEPROM_ADDR 0x50 //1010000

#include "software_IIC.h"
#include "error_handle.h"

error_handle_type EEPROM_Write_Byte(software_IIC_Port* port, uint16_t addr_eeprom, uint8_t data);
error_handle_type EEPROM_Read_Byte(software_IIC_Port* port, uint16_t addr_eeprom, uint8_t* rxbuf);
#endif