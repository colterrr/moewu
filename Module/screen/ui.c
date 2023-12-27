#include "ui.h"
#include "touch.h"
#include "lcd.h"
#include "instance.h"

extern instance database;
interface now_mode;
error_handle_type last_sta_CO2;
void BasicData_Show(void)
{
    //SHT sensor
    Lcd_DrawStr("温度:", 7, 60, 65, c32, merge, BLACK, WHITE);
    if (database.SHT_sta == normal){
        Lcd_DrawFloat(database.SHT_data_p->pdata_real->temperature, 140, 65, c32, merge, BLACK, DEFAULT_COLOR);
    }
    else {
        Lcd_DrawStr("ERROR", 5, 140, 65, c32, merge, RED, DEFAULT_COLOR);
    }
    Lcd_DrawStr("湿度:", 7, 240, 65, c32, merge, BLACK, WHITE);
    if (database.SHT_sta == normal){
        Lcd_DrawFloat(database.SHT_data_p->pdata_real->humidity, 320, 65, c32, merge, BLACK, DEFAULT_COLOR);
    }
    else {
        Lcd_DrawStr("ERROR", 5, 320, 65, c32, merge, RED, DEFAULT_COLOR);
    }

    //CO2 sensor
    Lcd_DrawStr("CO2浓度(ppm):", 15, 60, 145, c32, merge, BLACK, WHITE);
    if (database.CO2_sta == normal){
        if(last_sta_CO2 != normal) Lcd_DrawRectangle(268, 145, 268 + 80, 145 + 32, WHITE);
        Lcd_DrawUint(database.CO2_data_p->CO2_ppm, 268, 145, c32, merge, BLACK, DEFAULT_COLOR);
        last_sta_CO2 = normal;
    }
    else {
        Lcd_DrawStr("ERROR", 5, 268, 145, c32, merge, RED, DEFAULT_COLOR);
        last_sta_CO2 = database.CO2_sta;
    }

    //UV sensor
    Lcd_DrawStr("紫外线指数:lv", 18, 60, 225, c32, merge, BLACK, WHITE);
    if (database.UV_sta == normal){
        uint8_t tem = database.UV_data_p->aver_lv;
        if (tem >= 10 && tem <=11){
            uint8_t str[2];
            str[0] = '1';tem -= 10;str[1] = tem + '0';
            Lcd_DrawStr(str, 2, 272, 225, c32, merge, BLACK, DEFAULT_COLOR);
        }
        else if (tem == 12){
            uint8_t str[] = "11+";
            Lcd_DrawStr(str, 3, 272, 225, c32, merge, BLACK, DEFAULT_COLOR);
        }
        else {
            Lcd_DrawChar(tem + '0', 272, 225, c32, merge, BLACK, WHITE);
            Lcd_DrawRectangle(272+16, 225, 272+48, 225+32, WHITE);
        }
    }
    else {
        Lcd_DrawStr("ERROR", 5, 272, 225, c32, merge, RED, DEFAULT_COLOR);
    }
}

void UI_InitDraw(void)
{
    Lcd_Fill(WHITE);
    Lcd_DrawRectangle(0, 0, 480, 32, GRAY);
    Lcd_DrawStrMiddle("moewu猫屋主控", 17, 240, 16, c32, overlay, BLACK, GRAY);
    //Lcd_DrawStrMiddle("初始化中......", 18, WIDTH_MAX/2, HEIGHT_MAX/2, c32, merge, RED, WHITE);
    now_mode = BASIC_DATA;
}

void UI_task(void)
{
    if (now_mode == BASIC_DATA) BasicData_Show();
}
