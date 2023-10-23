#include "ui.h"
#include "touch.h"
#include "lcd.h"

void UI_InitDraw(void)
{
    Lcd_Fill(WHITE);
    Lcd_DrawRectangle(0, 0, 480, 32, GRAY);
    Lcd_DrawStrMiddle("moewu猫屋主控", 17, 240, 16, c32, overlay, BLACK, GRAY);
}

void UI_task(void)
{
    
}
