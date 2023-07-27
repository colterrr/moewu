#ifndef _UV_SENSOR_H_
#define _UV_SENSOR_H_

#include "stdint.h"
#include "error_handle.h"

//参考电压 单位mV
#define VCC_ref (3300) 

typedef enum UV_index_e
{
    lv_0 = 0,
    lv_1,
    lv_2,
    lv_3,
    lv_4,
    lv_5,
    lv_6,
    lv_7,
    lv_8,
    lv_9,
    lv_10,
    lv_11,
    lv_11pls
}UV_index;

#pragma pack(1)
typedef struct UV_data_s
{
    UV_index* UV_pdata;
    uint16_t num;
    UV_index aver_lv;
}UV_data;
#pragma pack()

void UV_sensor_Init(void);
error_handle_type UV_sensor_data_handle(uint16_t* adc_data, UV_data* data_obj);

#endif