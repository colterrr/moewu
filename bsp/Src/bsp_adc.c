#include "bsp_adc.h"
#include "adc.h"
#include "stdlib.h"

uint16_t* adc_pdata;
extern ADC_HandleTypeDef hadc1;
void BSP_ADC_Init()
{
    adc_pdata = (uint16_t*)malloc(sizeof(uint16_t) * CHANNEL_NUM);
    HAL_ADC_Start_DMA(&hadc1, adc_pdata, CHANNEL_NUM);
}

uint16_t* BSP_GET_Pdata(void)
{
    return adc_pdata;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    uint8_t ad;
    ad= 1;
}