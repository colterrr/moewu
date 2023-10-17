#include "ptc.h"
#include "fuzzy_pid.h"
#include "bsp_pwm.h"

fuzzy_pid_type PTC_ctrl;

void PTC_Init(PTC_fdb_type* fdb_data)
{
    
}

void PTC_setpwm(int freq, float D_ratio)
{
    BSP_PWM_Stop(PTC_PWM_PORT);
    BSP_PWM_SetARR(PTC_PWM_PORT, (int)1e5 / freq - 1);
    BSP_PWM_SetCCR(PTC_PWM_PORT, 1e5 * D_ratio / (float)freq);
    BSP_PWM_Start(PTC_PWM_PORT);
}