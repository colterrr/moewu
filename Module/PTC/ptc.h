#ifndef _PTC_H_
#define _PTC_H_

#define PTC_PWM_PORT 0
#define NUM_ATMO 1
#define NUM_SURF 1

#include "stdint.h"

typedef struct PTC_fdb_type_s
{
    float** p_atmo_arr;
    float** p_surf_arr;
}PTC_fdb_type;

void PTC_Init(void);
void PTC_startpwm(void);
void PTC_startpwm(void);
void PTC_setDratio(uint8_t D_ratio);
void PTC_update();

#endif