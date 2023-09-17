#ifndef _LCD_H_
#define _LCD_H_

#include "stdint.h"
#include "font.h"

#define WIDTH_MAX 320
#define HEIGHT_MAX 240

/***IO配置***/
#define GPIOx_lcd GPIOE

#define NSS_pin GPIO_PIN_7
#define LED_pin GPIO_PIN_8
#define RST_pin GPIO_PIN_9
#define DC_pin GPIO_PIN_10

#define LCD_SPI_PORT 0

#define SetLow(pin) HAL_GPIO_WritePin(GPIOx_lcd,pin,0)
#define SetHigh(pin) HAL_GPIO_WritePin(GPIOx_lcd,pin,1)

typedef enum Draw_Mode_e
{
    merge = 0,
    overlay
}Draw_Mode;

void Lcd_Init(void);
void Lcd_DrawRectangle(uint16_t xS, uint16_t xE, uint16_t yS, uint16_t yE, uint16_t color);

void Lcd_DrawChar(uint8_t c, uint16_t x, uint16_t y, Font_Size size, Draw_Mode mode, uint16_t back_color, uint16_t font_color);
void Lcd_DrawChinese(uint16_t c, uint16_t x, uint16_t y);

#endif