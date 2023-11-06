#ifndef _SHT_SENSOR_H_
#define _SHT_SENSOR_H_

#include "stdint.h"
#include "error_handle.h"
#include "bsp_iic.h"

#define SHT_NUM 1 //传感器数量,暂时认为只有一个
#define SHT_PORT_INDEX 0
#define SHT_ADDR 0x45 //从机地址
typedef enum setting_periodic_mode_e
{
    High_05 = 0,
    Medium_05,
    Low_05,

    High_1,
    Medium_1,
    Low_1,

    High_2,
    Medium_2,
    Low_2,
    
    High_4,
    Medium_4,
    Low_4,

    High_10,
    Medium_10,
    Low_10
}setting_periodic_mode;

#pragma pack(1)
typedef struct temp_humid_data_s
{
    uint16_t temperature;
    uint16_t humidity;
}temp_humid_data;

typedef struct  real_data_s
{
   float temperature;
   float humidity;
}real_data;

//所有传感器的数据整合结构体
typedef struct SHT_data_s
{
    temp_humid_data* pdata;
    uint16_t num;
    real_data* pdata_real;
    real_data aver_data;
}SHT_data;
#pragma pack()

// error_handle_type SHT_sensor_data_handle(temp_humid_data* data_obj, uint8_t ADDR);
// error_handle_type SHT_sensor_set_periodic(uint8_t iic_index, setting_periodic_mode mode, uint8_t ADDR);
// error_handle_type SHT_sensor_break(uint8_t ADDR);

void sht_sensor_task(void);
void SHT_sensor_Init(void);
void SHT_data_calc(SHT_data* data_obj);

#endif