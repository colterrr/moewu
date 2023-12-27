#ifndef _BSP_PWM_H_
#define _BSP_PWM_H_

#include "stdint.h"
#include "tim.h"

//tim3
//PSC 840-1
//f_in 1e5

#define PWM_MAX_NUM 4

typedef struct BSP_PWM_Type_s
{
    uint8_t channel;
    TIM_HandleTypeDef* htim;
}BSP_PWM_Type;

void BSP_PWM_SetARR(uint8_t index, uint16_t ARR_val);
void BSP_PWM_SetCCR(uint8_t index, uint16_t CCR_val);
void BSP_PWM_Start(uint8_t index);
void BSP_PWM_Stop(uint8_t index);

#endif