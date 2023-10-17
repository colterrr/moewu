#include "lcd.h"

#include "gpio.h"
#include "bsp_spi.h"
#include "myfunc.h"

uint8_t Lcd_txbuffer[10] = {};
uint8_t Lcd_rxbuffer[10] = {};

extern uint8_t char_32[][16];
/***发送数据***/
void send_data(uint8_t data)
{
    NSS_PICK;
    DATA_MODE;
    Lcd_txbuffer[0] = data;
    BSP_SPI_Transmit(LCD_SPI_PORT, Lcd_txbuffer, 1);
    NSS_ABORT;
}

void send_16bit_color(uint16_t color)
{
    Lcd_txbuffer[0] = (color >> 8) & 0xF8;
    Lcd_txbuffer[1] = (color >> 3) & 0xFF;
    Lcd_txbuffer[2] = color << 3;
    BSP_SPI_Transmit(LCD_SPI_PORT, Lcd_txbuffer, 3);
}

/*发送指令*/
void send_comd(uint8_t comd)
{
    NSS_PICK;
    COMD_MODE;
    Lcd_txbuffer[0] = comd;
    BSP_SPI_Transmit(LCD_SPI_PORT, Lcd_txbuffer, 1);
    NSS_ABORT;
}

/*lcd复位*/
void lcd_reset(void)
{
    SetLow(RST_pin);
    delay_ms(50);
    SetHigh(RST_pin);
    delay_ms(50);
}

void set_window(uint16_t xS, uint16_t yS, uint16_t xE, uint16_t yE)
{
    send_comd(0x2A);
    send_data(xS>>8);
    send_data(xS & 0x00FF);
    send_data(xE>>8);
    send_data(xE & 0x00FF);

    send_comd(0x2B);
    send_data(yS>>8);
    send_data(yS & 0x00FF);
    send_data(yE>>8);
    send_data(yE & 0x00FF);

}

void set_cursor(uint16_t x, uint16_t y)
{
    set_window(x, y, x, y);
}

/***lcd初始化***/
void Lcd_Init(void)
{
    //先关闭片选
    NSS_ABORT;
    //开启背光
    SetHigh(LED_pin);

    lcd_reset();

    // //退出睡眠模式 sleep out
    // send_comd(0x11);
    // delay_ms(100);

    // //电源控制B类设置
    // send_comd(0xCF);
    // send_8bit_data(0x00);
    // send_8bit_data(0x81);
    // send_8bit_data(0x30);

    // //开机顺序设置
    // send_comd(0xED);
    // send_8bit_data(0x64);
    // send_8bit_data(0x03);
    // send_8bit_data(0x12);
    // send_8bit_data(0x81);

    // //驱动定时器设置A
    // send_comd(0xE8);
    // send_8bit_data(0x85);
    // send_8bit_data(0x10);
    // send_8bit_data(0x78);

    // //电压控制设置
    // send_comd(0xCB);
    // send_8bit_data(0x39);
    // send_8bit_data(0x2C);
    // send_8bit_data(0x00);
    // send_8bit_data(0x34);
    // send_8bit_data(0x02);


    // //泵比控制
    // send_comd(0xF7);
    // send_8bit_data(0x20);

    // //驱动定时器设置B
    // send_comd(0xEA);
    // send_8bit_data(0x00);
    // send_8bit_data(0x00);

    // //帧速率设置
    // send_comd(0xB1);
    // send_8bit_data(0x00);
    // send_8bit_data(0x1B);

    // //显示功能设置
    // send_comd(0xB6);
    // send_8bit_data(0x0A);
    // send_8bit_data(0xA2);

    // //功耗设置1
    // send_comd(0xC0);
    // send_8bit_data(0x2B);

    // //功耗设置2
    // send_comd(0xC1);
    // send_8bit_data(0x01);

    // //显示接口设置
    // send_comd(0xF6);
    // send_8bit_data(0x01);
    // send_8bit_data(0x30);
    // send_8bit_data(0x00);

    // //VCOM控制1
    // send_comd(0xC5);
    // send_8bit_data(0x45);
    // send_8bit_data(0x45);

    // //VCOM控制2
    // send_comd(0xC7);
    // send_8bit_data(0xA2);

    // //使能3gamma
    // send_comd(0xF2);
    // send_8bit_data(0x02);

    // //伽马设置
    // send_comd(0x26);
    // send_8bit_data(0x01);

    // //positive伽马校对
    // send_comd(0xE0);
    // send_8bit_data(0x0F);
    // send_8bit_data(0x17);
    // send_8bit_data(0x14);
    // send_8bit_data(0x09);
    // send_8bit_data(0x0C);
    // send_8bit_data(0x06);
    // send_8bit_data(0x43);
    // send_8bit_data(0x75);
    // send_8bit_data(0x36);
    // send_8bit_data(0x08);
    // send_8bit_data(0x13);
    // send_8bit_data(0x05);
    // send_8bit_data(0x10);
    // send_8bit_data(0x0B);
    // send_8bit_data(0x08);

    // //negetive伽马校对
    // send_comd(0xE1);
    // send_8bit_data(0x00);
    // send_8bit_data(0x1F);
    // send_8bit_data(0x23);
    // send_8bit_data(0x03);
    // send_8bit_data(0x0E);
    // send_8bit_data(0x04);
    // send_8bit_data(0x39);
    // send_8bit_data(0x25);
    // send_8bit_data(0x4D);
    // send_8bit_data(0x06);
    // send_8bit_data(0x0D);
    // send_8bit_data(0x0B);
    // send_8bit_data(0x33);
    // send_8bit_data(0x37);
    // send_8bit_data(0x0F);

    // //接口设置
    // send_comd(INTERFACE_SET);
    // send_8bit_data(0x00);

    // //像素格式选择
    // send_comd(0x3A);
    // send_8bit_data(0x06); //18bit模式
    // delay_ms(50);

    // //液晶屏扫描模式设置
    // send_comd(MEMORY_ACCESS);
    // send_8bit_data(0x68);

    // //display on
    // send_comd(0x29);
    // send_comd(NORMAL_DISPLAY);
    // send_comd(ALL_WHITE);
    // //Lcd_DrawRectangle(100,100,150,150, GREEN);

    send_comd(0XF7);
	send_data(0xA9);
	send_data(0x51);
	send_data(0x2C);
	send_data(0x82);

	send_comd(0xC0);
	send_data(0x11);
	send_data(0x09);

	send_comd(0xC1);
	send_data(0x41);

	send_comd(0XC5);
	send_data(0x00);
	send_data(0x0A);
	send_data(0x80);

	send_comd(0xB1);
	send_data(0xB0);
	send_data(0x11);

	send_comd(0xB4);
	send_data(0x02);

	send_comd(0xB6);
	send_data(0x02);
	send_data(0x42);

	send_comd(0xB7);
	send_data(0xc6);

	send_comd(0xBE);
	send_data(0x00);
	send_data(0x04);

	send_comd(0xE9);
	send_data(0x00);

	send_comd(0x36);
	send_data((1<<3)|(1<<7)|(0<<6)|(1<<5)|(0<<4)|(0<<2));

	send_comd(0x3A);
	send_data(0x66);

	send_comd(0xE0);
	send_data(0x00);
	send_data(0x07);
	send_data(0x10);
	send_data(0x09);
	send_data(0x17);
	send_data(0x0B);
	send_data(0x41);
	send_data(0x89);
	send_data(0x4B);
	send_data(0x0A);
	send_data(0x0C);
	send_data(0x0E);
	send_data(0x18);
	send_data(0x1B);
	send_data(0x0F);

	send_comd(0XE1);
	send_data(0x00);
	send_data(0x17);
	send_data(0x1A);
	send_data(0x04);
	send_data(0x0E);
	send_data(0x06);
	send_data(0x2F);
	send_data(0x45);
	send_data(0x43);
	send_data(0x02);
	send_data(0x0A);
	send_data(0x09);
	send_data(0x32);
	send_data(0x36);
	send_data(0x0F);

	send_comd(0x11);
	delay_ms(120);
	send_comd(0x29);

    Lcd_Fill(WHITE);
    Lcd_DrawRectangle(0, 0, 50, 100, RED);
    //Lcd_DrawChar('F', 50, 100, c16, merge, WHITE, BLACK);
    //Lcd_DrawStrMiddle("ABCDE!!!", 8, 240, 160, c16, overlay, YELLOW, BLACK);
    Lcd_rxbuffer[5] = char_32[14][10];
    Lcd_DrawChar('!', 50, 100, c32, merge, WHITE, BLACK);
}

uint16_t access_char32(uint8_t c, uint8_t j)
{
    uint8_t index = c - ASCII_OFFSET;
    uint16_t ans = char_32[index * 4 + j/8][(j - j % 8)*2];
    ans <<= 8;
    ans &= char_32[index * 4 + j/8][(j - j % 8)*2 + 1];
    return ans;
}

void Lcd_Fill(uint16_t color)
{
    Lcd_DrawRectangle(0, 0, WIDTH_MAX - 1, HEIGHT_MAX - 1, color);
}

void Lcd_DrawRectangle(uint16_t xS, uint16_t yS, uint16_t xE, uint16_t yE, uint16_t color)
{
    set_window(xS, yS, xE, yE);
    send_comd(0x2C);
    NSS_PICK;
    DATA_MODE;
    for (uint16_t i = 0; i <= xE - xS; i++){
        for (uint16_t j = 0; j <= yE - yS; j++){
            send_16bit_color(color);
        }
    }
    NSS_ABORT;
}

void Lcd_DrawChar(uint8_t c, uint16_t x, uint16_t y, Font_Size size, Draw_Mode mode, uint16_t back_color, uint16_t font_color)
{
    uint16_t x_max = 8*size - 1;
    uint16_t y_max = 16*size - 1;
    uint16_t tem = 0;
    set_window(x, y, x + x_max, y + y_max);
    send_comd(0x2C);
    NSS_PICK;
    DATA_MODE;

    if(size == c16)
        for (uint8_t j = 0; j <= y_max; j++){
            tem = char_16[c - ASCII_OFFSET][j];
            for (uint8_t i = 0; i <= x_max; i++){
                if(tem & 0x01){
                    send_16bit_color(font_color);
                }
                else {
                    if(mode) send_16bit_color(back_color); //overlay模式，底色也写入
                    else {
                        //跳过一个像素
                        // send_comd(0x3C);
                        // NSS_PICK;
                        // DATA_MODE;
                        send_16bit_color(DEFAULT_COLOR);
                    };//merge模式，不管底色
                }
                tem >>= 1;
            }
        }
    else if(size == c32){
        uint8_t* pt;
        for (uint8_t j = 0; j <= y_max; j++){
            // pt = (uint8_t*)char_32;
            // tem = pt[(c - ASCII_OFFSET) * 64 + j*2];
            // tem = (tem << 8) & pt[(c - ASCII_OFFSET) * 64 + j*2 + 1];
            tem = char_32[11][11];
            tem = access_char32(c, j);
            for (uint8_t i = 0; i <= x_max; i++){
                if (tem & 0x8000){
                    send_16bit_color(font_color);
                }
                else {
                    if(mode) send_16bit_color(back_color);
                    else {
                        send_16bit_color(DEFAULT_COLOR);
                    }
                }
                tem <<= 1;
            }
        }
    }
    NSS_ABORT;
}

void Lcd_DrawStr(uint8_t* str, uint8_t len, uint16_t x, uint16_t y, Font_Size size, Draw_Mode mode, uint16_t back_color, uint16_t font_color)
{
    uint16_t c_xlen = 8 * size;
    for (uint8_t i = 0; i < len; i++){
        Lcd_DrawChar(str[i], x + i * c_xlen, y, size, mode, back_color, font_color);
    }
}

void Lcd_DrawStrMiddle(uint8_t* str, uint8_t len, uint16_t x_middle, uint16_t y_middle, Font_Size size, Draw_Mode mode, uint16_t back_color, uint16_t font_color)
{
    uint16_t pixel_len = 8 * size * len;
    uint16_t c_xlen = 8 * size;
    uint16_t c_ypos = y_middle - 8 * size;
    for (uint8_t i = 0; i < len; i++){
        Lcd_DrawChar(str[i], x_middle - pixel_len / 2 + i * c_xlen, c_ypos, size, mode, back_color, font_color);
    }
}

void Lcd_DrawChinese(uint16_t c, uint16_t x, uint16_t y)
{
    
}

void Lcd_ReadDisplaySta()
{
    send_comd(0x09);
    BSP_SPI_Receive(LCD_SPI_PORT, Lcd_rxbuffer, 3);
}

void Lcd_ReadDisplayPwrMode()
{
    Lcd_txbuffer[0] = 0x0c;
    COMD_MODE;
    NSS_PICK;
    BSP_SPI_Transmit(LCD_SPI_PORT, Lcd_txbuffer, 1);
    DATA_MODE;
    BSP_SPI_Receive(LCD_SPI_PORT, Lcd_rxbuffer, 2);
    NSS_ABORT; 
}

void Lcd_ReadIDinfo()
{
    Lcd_txbuffer[0] = 0x04;
    COMD_MODE;
    NSS_PICK;
    BSP_SPI_Transmit(LCD_SPI_PORT, Lcd_txbuffer, 1);
    DATA_MODE;
    BSP_SPI_Receive(LCD_SPI_PORT, Lcd_rxbuffer, 3);
    //NSS_ABORT;    
}