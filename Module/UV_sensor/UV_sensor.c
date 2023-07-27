#include "UV_sensor.h"
#include "stdlib.h"
#include "instance.h"

UV_data my_UV_data;

void UV_arr_Create(UV_data* data)
{
    data->UV_pdata = (UV_index*)malloc(data->num * sizeof(UV_index));
}

UV_index judge_index(uint16_t v_now)
{
    UV_index tem_index;
    if (v_now < 50)tem_index = lv_0;
    else if (v_now < 227)tem_index = lv_1;
    else if (v_now < 318)tem_index = lv_2;
    else if (v_now < 408)tem_index = lv_3;
    else if (v_now < 503)tem_index = lv_4;
    else if (v_now < 606)tem_index = lv_5;
    else if (v_now < 696)tem_index = lv_6;
    else if (v_now < 795)tem_index = lv_7;
    else if (v_now < 881)tem_index = lv_8;
    else if (v_now < 976)tem_index = lv_9;
    else if (v_now < 1079)tem_index = lv_10;
    else if (v_now < 1170)tem_index = lv_11;
    else tem_index = lv_11pls;
    return tem_index;
}

error_handle_type UV_sensor_data_handle(uint16_t* adc_data, UV_data* data_obj)
{
    uint16_t i = 0;
    uint16_t num = data_obj->num;
    uint32_t sum_v = 0;
    UV_index* pdata = data_obj->UV_pdata;

    for (i = 0; i < num; i++){
        uint16_t v_now = VCC_ref * adc_data[i] / 4096;
        pdata[i] = judge_index(v_now);
        sum_v += v_now;
    }
    data_obj->aver_lv = judge_index(sum_v);

    return normal;
}

void UV_sensor_Init(void)
{
    database.UV_data_p = &my_UV_data;
    UV_arr_Create(&my_UV_data);
}