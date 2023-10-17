#ifndef _LCD_H_
#define _LCD_H_

#include "stdint.h"
#include "font.h"

#define WIDTH_MAX 480
#define HEIGHT_MAX 320

/***IO配置***/
#define GPIOx_lcd GPIOE

#define NSS_pin GPIO_PIN_7
#define LED_pin GPIO_PIN_8
#define RST_pin GPIO_PIN_9
#define DC_pin GPIO_PIN_10

#define LCD_SPI_PORT 0

#define SetLow(pin) HAL_GPIO_WritePin(GPIOx_lcd,pin,GPIO_PIN_RESET)
#define SetHigh(pin) HAL_GPIO_WritePin(GPIOx_lcd,pin,GPIO_PIN_SET)

#define NSS_PICK SetLow(NSS_pin)
#define NSS_ABORT SetHigh(NSS_pin)
#define DATA_MODE SetHigh(DC_pin)
#define COMD_MODE SetLow(DC_pin)

//颜色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色

#define DEFAULT_COLOR WHITE 
//命令
#define NOP 0x00 //空命令，用于终止RAMWR和RAMRD
#define SOFT_RST 0x01
#define NORMAL_DISPLAY 0x13 //lcd恢复到普通显示模式
#define INVER_OFF 0x20 //反转关
#define INVER_ON 0x21 //反转开
#define ALL_BLACK 0x22 //显示全黑
#define ALL_WHITE 0x23 //显示全白
#define DISPLAY_OFF 0x28
#define DISPLAY_ON 0x29
#define COLUMN_SET 0x2A
#define PAGE_SET 0x2B
#define RAMWR 0x2C
#define RAMRD 0x2E
#define PARTIAL_AREA 0x30
#define VERTICAL_SCRO 0x33
#define TEARING_OFF 0x34
#define TEARING_ON 0x35
#define MEMORY_ACCESS 0x36
#define VERTICAL_SCRO_START_ADDR 0x37
#define IDLE_OFF 0x38 //空闲关
#define IDLE_ON 0x39 //空闲开
#define PIXEL_FORMAT 0x3A
#define WR_CONTINUE 0x3C
#define RD_CONTINUE 0x3E
#define INTERFACE_SET 0xB0

typedef enum Draw_Mode_e
{
    merge = 0,
    overlay
}Draw_Mode;

void Lcd_Init(void);
void Lcd_DrawRectangle(uint16_t xS, uint16_t yS, uint16_t xE, uint16_t yE, uint16_t color);
void Lcd_Fill(uint16_t color);
void Lcd_DrawChar(uint8_t c, uint16_t x, uint16_t y, Font_Size size, Draw_Mode mode, uint16_t back_color, uint16_t font_color);
void Lcd_DrawStr(uint8_t* str, uint8_t len, uint16_t x, uint16_t y, Font_Size size, Draw_Mode mode, uint16_t back_color, uint16_t font_color);
void Lcd_DrawStrMiddle(uint8_t* str, uint8_t len, uint16_t x_middle, uint16_t y_middle, Font_Size size, Draw_Mode mode, uint16_t back_color, uint16_t font_color);


void Lcd_ReadDisplaySta();
void Lcd_ReadDisplayPwrMode();
void Lcd_ReadIDinfo();
#endif