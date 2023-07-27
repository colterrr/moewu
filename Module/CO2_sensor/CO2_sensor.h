#ifndef _CO2_SENSOR_H_
#define _CO2_SENSOR_H_

#include "stdint.h"
#include "error_handle.h"


#pragma pack(1)
typedef struct CO2_data_s
{
    uint16_t CO2_ppm;
    uint16_t TVOC_ppd;
}CO2_data;
#pragma pack()

void CO2_sensor_Init(void);
error_handle_type CO2_sensor_data_handle(CO2_data* data_obj, uint8_t* pdata, uint16_t len);

#endif