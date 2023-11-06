#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_

#include "stdint.h"

#define CHANNEL_NUM 1

void BSP_ADC_Init();
uint16_t* BSP_GET_Pdata(void);

#endif