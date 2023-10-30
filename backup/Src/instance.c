#include "instance.h"
#include "CO2_sensor.h"
#include "SHT_sensor.h"
#include "UV_sensor.h"
#include "ESP_01s.h"
#include "lcd.h"
#include "touch.h"
#include "ui.h"

#include "bsp_adc.h"
#include "bsp_uart.h"
#include "bsp_spi.h"

instance database;

void Instance_Init(void)
{
    BSP_SPI_Init();
    BSP_UART_Init();
    BSP_IIC_Init();
    BSP_ADC_Init();

    SHT_sensor_Init();
    UV_sensor_Init();
    CO2_sensor_Init();
    ESP_Init();
    Lcd_Init();
    UI_InitDraw();
    //Touch_Init();
}