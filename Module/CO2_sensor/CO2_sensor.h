#ifndef _CO2_SENSOR_H_
#define _CO2_SENSOR_H_

#include "stdint.h"
#include "error_handle.h"

typedef enum handle_step_e
{
    data_recv = 0,
    comd_tran
}handle_step;

#pragma pack(1)
typedef struct CO2_data_s
{
    uint16_t CO2_ppm;
    uint16_t TVOC_ppd;
    handle_step step;
    uint8_t cmd_len;
}CO2_data;
#pragma pack()

void CO2_sensor_Init(void);
void CO2_set_peroid(uint16_t ms);
error_handle_type CO2_sensor_data_handle(CO2_data* data_obj, uint8_t* pdata, uint16_t len);

#endif