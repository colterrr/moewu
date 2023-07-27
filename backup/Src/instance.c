#include "instance.h"
#include "CO2_sensor.h"
#include "SHT_sensor.h"
#include "UV_sensor.h"
#include "ESP_01s.h"

#include "bsp_adc.h"
#include "bsp_uart.h"

instance database;

void Instance_Init(void)
{
    BSP_UART_Init();
    
    SHT_sensor_Init();
    UV_sensor_Init();
    CO2_sensor_Init();
    ESP_Init();
}