#include "eeprom.h"
#include "string.h"

uint8_t EEP_txbuffer[10];
uint8_t EEP_rxbuffer[10];

error_handle_type EEPROM_Write_Byte(software_IIC_Port* port, uint16_t addr, uint8_t data)
{
    EEP_txbuffer[0] = addr >> 8;
    EEP_txbuffer[1] = addr | 0xFF00;
    EEP_txbuffer[2] = data;
    Master_Transmit(EEPROM_PORT_INDEX, EEP_txbuffer, 3);
    if (!BSP_IIC_sta(EEPROM_PORT_INDEX))return trans_err;
    return normal;
}

error_handle_type EEPROM_Read_Byte(software_IIC_Port* port, uint16_t addr, uint8_t* rxbuf)
{
    EEP_txbuffer[0] = addr >> 8;
    EEP_txbuffer[1] = addr | 0xFF00;
    Master_Complex(EEPROM_PORT_INDEX, EEP_txbuffer, 2, rxbuf, 1);
    if(!BSP_IIC_sta(EEPROM_PORT_INDEX))return trans_err;
    return normal;
}

error_handle_type EEPROM_Write(uint16_t addr_head, uint8_t* pdata, uint16_t len)
{
    
}

error_handle_type EEPROM_Read(uint16_t addr_head, uint8_t* rxbuf, uint16_t len)
{
    
}

void EEPROM_Init(void)
{
    BSP_IIC_setpara(EEPROM_PORT_INDEX, GPIOB, GPIO_PIN_10, GPIOB, GPIO_PIN_11, EEPROM_ADDR); //接口待定
}