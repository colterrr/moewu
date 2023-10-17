#ifndef _FONT_H_
#define _FONT_H_

#include "stdint.h"

#define ASCII_OFFSET 32 //字体库编号到ascii码的偏移量
typedef enum Font_Size_e{
    c16 = 1,
    c32,
}Font_Size;

extern uint8_t char_16[][16];
extern uint8_t char_32[][16];

#endif