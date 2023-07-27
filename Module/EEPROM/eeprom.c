#include "eeprom.h"
#include "string.h"

uint8_t EEP_txbuffer[10];
uint8_t EEP_rxbuffer[10];

error_handle_type EEPROM_Write_Byte(software_IIC_Port* port, uint16_t addr, uint8_t data)
{
    port->slave_ADDR = EEPROM_ADDR;
    EEP_txbuffer[0] = addr >> 8;
    EEP_txbuffer[1] = addr | 0xFF00;
    EEP_txbuffer[2] = data;
    Master_Transmit(port, EEP_txbuffer, 3);
    if (port->status == IIC_ERR)return trans_error;
    return normal;
}

error_handle_type EEPROM_Read_Byte(software_IIC_Port* port, uint16_t addr, uint8_t* rxbuf)
{
    port->slave_ADDR = EEPROM_ADDR;
    EEP_txbuffer[0] = addr >> 8;
    EEP_txbuffer[1] = addr | 0xFF00;
    Master_Complex(port, EEP_txbuffer, 2, rxbuf, 1);
    if(port->status == IIC_ERR)return trans_error;
    return normal;
}

error_handle_type EEPROM_Write(uint16_t addr_head, uint8_t* pdata, uint16_t len)
{
    
}

error_handle_type EEPROM_Read(uint16_t addr_head, uint8_t* rxbuf, uint16_t len)
{
    
}