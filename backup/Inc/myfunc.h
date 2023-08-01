#ifndef _MY_FUNC_H_
#define _MY_FUNC_H_

#include "math.h"
#include "stdint.h"

#define p(__base__, __index__) (uint32_t)pow(__base__, __index__) 

#define max(x,y)  ({ \
typeof(x) _x = (x); \
typeof(y) _y = (y); \
_x > _y ? _x : _y; \
})

#define min(x,y)  ({ \
typeof(x) _x = (x); \
typeof(y) _y = (y); \
_x > _y ? _y : _x; \
})

uint8_t Uint_to_Str(uint32_t num, uint8_t* place);
uint32_t Str_to_uint(uint8_t* pdata, uint8_t len);

void delay_us(uint16_t us);
void delay_ms(uint16_t ms);
#endif
