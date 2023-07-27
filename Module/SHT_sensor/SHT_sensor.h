#ifndef _SHT_SENSOR_H_
#define _SHT_SENSOR_H_

#include "stdint.h"
#include "error_handle.h"
#include "software_IIC.h"

extern const uint8_t periodic_set_high[2];   //10Hz
extern const uint8_t periodic_set_medium[2]; //4Hz
extern const uint8_t periodic_set_low[2];    //2Hz
extern const uint8_t periodic_fetch[2];

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

typedef struct SHT_data_s
{
    temp_humid_data* pdata;
    uint16_t num;
    real_data* pdata_real;
    real_data aver_data;
}SHT_data;
#pragma pack()

error_handle_type SHT_sensor_data_handle(software_IIC_Port* port, temp_humid_data* data_obj);
error_handle_type SHT_sensor_set_high(software_IIC_Port* port);
error_handle_type SHT_sensor_break(software_IIC_Port* port);

void SHT_sensor_Init(void);
void SHT_data_calc(SHT_data* data_obj);

#endif