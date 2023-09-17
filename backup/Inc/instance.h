#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include "stdint.h"
#include "main.h"

#include "SHT_sensor.h"
#include "UV_sensor.h"
#include "CO2_sensor.h"
#include "eeprom.h"

#include "error_handle.h"

// 接口配置
// IIC_SCL PB6
// IIC_SDA PB7

// ADC1_IN4 PA4

// UART2 TX PA2
// UART2 RX PA3

// UART1 TX PA9
// UART1 RX PA10

//SPI1 SCK PA5
//SPI1 MISO PA6
//SPI1 MOSI PA7
//SPI1 NSS PE7

// 参数配置
//SPI1  MSB_first 8_bit_frame

typedef struct instance_s
{
    SHT_data* SHT_data_p;
    UV_data* UV_data_p;
    CO2_data* CO2_data_p;

    error_handle_type SHT_sta;
    error_handle_type UV_sta;
    error_handle_type CO2_sta;
}instance;

extern instance database;

void Instance_Init(void);

#endif