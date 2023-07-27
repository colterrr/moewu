#include "myfunc.h"
#include "main.h"
#include "tim.h"

//指定数量字符转整型，自带合法检测
uint32_t Str_to_uint(uint8_t* pdata, uint8_t len)
{
    uint32_t num = 0;
    uint8_t k = 0;
    for(k = 1; len > 0; len--, k *= 10){
        num += (pdata[len-1] - '0') * k;
    }
    return num;
}

//微秒级延时
void delay_us(uint16_t us)
{
    __HAL_TIM_DISABLE(&htim6);
    __HAL_TIM_SET_COUNTER(&htim6 ,0);
    __HAL_TIM_ENABLE(&htim6);
    while(__HAL_TIM_GetCounter(&htim6) < us);
}

//毫秒级延时
void delay_ms(uint16_t ms)
{
    __HAL_TIM_DISABLE(&htim7);
    __HAL_TIM_SET_COUNTER(&htim7 ,0);
    __HAL_TIM_ENABLE(&htim7);
    while(__HAL_TIM_GetCounter(&htim7) < ms * 10);
}