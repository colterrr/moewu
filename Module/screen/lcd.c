#include "lcd.h"

#include "gpio.h"
#include "bsp_spi.h"
#include "myfunc.h"

/***发送数据***/
void send_8bit_data(uint8_t data)
{
    SetLow(NSS_pin);
    SetHigh(DC_pin);
    BSP_SPI_Transmit(LCD_SPI_PORT, &data, 1);
    SetHigh(NSS_pin);
}

void send_16bit_data(uint16_t data)
{
    SetLow(NSS_pin);
    SetHigh(DC_pin);
    BSP_SPI_Transmit(LCD_SPI_PORT, &data, 2);
    SetHigh(NSS_pin);
}

/***发送指令***/
void send_comd(uint8_t comd)
{
    SetLow(NSS_pin);
    SetLow(DC_pin);
    BSP_SPI_Transmit(LCD_SPI_PORT, &comd, 1);
    SetHigh(NSS_pin);
}

/***lcd复位***/
void lcd_reset(void)
{
    SetLow(RST_pin);
    delay_ms(30);
    SetHigh(RST_pin);
    delay_ms(30);
}

void set_window(uint16_t xS, uint16_t yS, uint16_t xE, uint16_t yE)
{
    send_comd(0x2A);
    send_16bit_data(xS);
    send_16bit_data(xE);

    send_comd(0x2B);
    send_16bit_data(yS);
    send_16bit_data(yE);

    send_comd(0x2C);
}

void set_cursor(uint16_t x, uint16_t y)
{
    set_window(x, y, x, y);
}

/***lcd初始化***/
void Lcd_Init(void)
{
    //关闭片选
    SetHigh(NSS_pin);
    //开启背光
    SetHigh(LED_pin);

    lcd_reset();

    //电源控制B类设置
    send_comd(0xCF);
    send_8bit_data(0x00);
    send_8bit_data(0xC1);
    send_8bit_data(0x30);

    //开机顺序设置
    send_comd(0xED);
    send_8bit_data(0x54);
    send_8bit_data(0x03);
    send_8bit_data(0x12);
    send_8bit_data(0x81);

    //像素格式选择
    send_comd(0x3A);
    send_8bit_data(0x55); //16bit模式

    //液晶屏扫描模式设置
    send_comd(0x36);
    send_8bit_data(0x60);

    //伽马设置
    send_comd(0x26);
    send_8bit_data(0x01);

    //positive伽马校对
    send_comd(0xE0);
    send_8bit_data(0x0F);
    send_8bit_data(0x17);
    send_8bit_data(0x14);
    send_8bit_data(0x09);
    send_8bit_data(0x0C);
    send_8bit_data(0x06);
    send_8bit_data(0x43);
    send_8bit_data(0x75);
    send_8bit_data(0x36);
    send_8bit_data(0x08);
    send_8bit_data(0x13);
    send_8bit_data(0x05);
    send_8bit_data(0x10);
    send_8bit_data(0x0B);
    send_8bit_data(0x08);

    //negetive伽马校对
    send_comd(0xE1);
    send_8bit_data(0x00);
    send_8bit_data(0x1F);
    send_8bit_data(0x23);
    send_8bit_data(0x03);
    send_8bit_data(0x0E);
    send_8bit_data(0x04);
    send_8bit_data(0x39);
    send_8bit_data(0x25);
    send_8bit_data(0x4D);
    send_8bit_data(0x06);
    send_8bit_data(0x0D);
    send_8bit_data(0x0B);
    send_8bit_data(0x33);
    send_8bit_data(0x37);
    send_8bit_data(0x0F);

    //display on
    send_comd(0x29);
}

void Lcd_DrawRectangle(uint16_t xS, uint16_t yS, uint16_t xE, uint16_t yE, uint16_t color)
{
    set_window(xS, yS, xE, yE);
    for (uint8_t i = 0; i <= xE - xS; i++){
        for (uint8_t j = 0; j <= yE - yS; j++){
            send_16bit_data(color);
        }
    }
}

void Lcd_DrawChar(uint8_t c, uint16_t x, uint16_t y, Font_Size size, Draw_Mode mode, uint16_t back_color, uint16_t font_color)
{
    uint16_t x_max = 8*size - 1;
    uint16_t y_max = 16*size - 1;
    uint8_t tem = 0;
    set_window(x, y, x_max, y + y_max);
    for (uint8_t j = 0; j <= y_max; j++){
        if(size == c16) 
            tem = char_16[c - ASCII_OFFSET][j];
        else if(size == c32)
            //tem = 
        for (uint8_t i = 0; i <= x_max; i++){
            if(tem & 0x80){
                send_16bit_data(font_color);
            }
            else {
                if(mode) send_16bit_data(back_color); //overlay模式，底色也写入
            }
        }
    }

}

void Lcd_DrawChinese(uint16_t c, uint16_t x, uint16_t y)
{

}