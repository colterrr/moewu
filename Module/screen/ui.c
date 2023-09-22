#include "ui.h"
#include "touch.h"
#include "lcd.h"

void UI_task(void)
{
    Lcd_DrawRectangle(100,100,150,150, 0xFFFF);
    //Lcd_ReadDisplaySta();
}