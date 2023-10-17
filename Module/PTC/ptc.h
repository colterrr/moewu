#ifndef _PTC_H_
#define _PTC_H_

#define PTC_PWM_PORT 0

#include "stdint.h"

typedef struct PTC_fdb_type_s
{
    float* atmo_temperature;
    float* surface_temprature;
    uint8_t num_atmo;
    uint8_t num_surf;
}PTC_fdb_type;

//void PTC_setpwm();

#endif