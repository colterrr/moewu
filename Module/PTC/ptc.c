#include "ptc.h"
#include "fuzzy_pid.h"
#include "bsp_pwm.h"
#include "stdlib.h"
#include "instance.h"

#define Freq 1000

fuzzy_pid_type PTC_ctrl;
PTC_fdb_type fdb_data;

void PTC_Init()
{
    fdb_data.p_surf_arr = (float**)malloc(NUM_SURF * sizeof(float*));
    fdb_data.p_atmo_arr = (float**)malloc(NUM_ATMO * sizeof(float*));
    fdb_data.p_atmo_arr[0] = &(database.SHT_data_p->aver_data.temperature);
    for(uint8_t i = 0; i < 4; i++){
        BSP_PWM_SetARR(i, 1e5 / Freq - 1);
    }  
    PTC_startpwm();
    PTC_setDratio(0);
}

void PTC_startpwm(void)
{
    for(uint8_t i = 0; i < 4; i++){
        BSP_PWM_Start(i);
    }  
}

void PTC_stoppwm(void)
{
    for(uint8_t i = 0; i < 4; i++){
        BSP_PWM_Stop(i);
    }  
}

void PTC_setDratio(uint8_t D_ratio)
{
    for(uint8_t i = 0; i < 4; i++){
        BSP_PWM_SetCCR(i, D_ratio);
    } 
} 

void PTC_update()
{
    //PTC_setDratio(PTC_ctrl.output);
    //PTC_setDratio(50);
}
