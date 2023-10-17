#include "fuzzy_pid.h"
#include "myfunc.h"
//模糊规则库
//横轴为E 竖轴为EC
static const float ruleKp[7][7]={
	PB,	PB,	PM,	PM,	PS,	PS,	ZO,
	PB,	PB,	PM,	PM,	PS,	ZO,	ZO,
	PM,	PM,	PM,	PS,	ZO,	NS,	NM,
	PM,	PS,	PS,	ZO,	NS,	NM,	NM,
	PS,	PS,	ZO,	NS,	NS,	NM,	NM,
	ZO,	ZO,	NS,	NM,	NM,	NM,	NB,
	ZO,	NS,	NS,	NM,	NM,	NB,	NB 
};
 
static const float ruleKi[7][7]={
	NB,	NB,	NB,	NM,	NM,	ZO,	ZO,
	NB,	NB,	NM,	NM,	NS,	ZO,	ZO,
	NM,	NM,	NS,	NS,	ZO,	PS,	PS,
	NM,	NS,	NS,	ZO,	PS,	PS,	PM,
	NS,	NS,	ZO,	PS,	PS,	PM,	PM,
	ZO,	ZO,	PS,	PM,	PM,	PB,	PB,
	ZO,	ZO,	PS,	PM,	PB,	PB,	PB 
};
 
static const float ruleKd[7][7]={
	PS,	PS,	ZO,	ZO,	ZO,	PB,	PB,
	NS,	NS,	NS,	NS,	ZO,	NS,	PM,
	NB,	NB,	NM,	NS,	ZO,	PS,	PM,
	NB,	NM,	NM,	NS,	ZO,	PS,	PM,
	NB,	NM,	NS,	NS,	ZO,	PS,	PS,
	NM,	NS,	NS,	NS,	ZO,	PS,	PS,
	PS,	ZO,	ZO,	ZO,	ZO,	PB,	PB
};

#define ms_calc(val,l_val,r_val) (val - l_val)/(r_val - l_val)

/**
 * @brief 隶属度计算函数
 * @param val 反馈值
 * @param ms 隶属值 (ms[0] + ms[1] == 1)
 * @param index 规则表下标
 * @param discource 论域分界参数
 */
void Calc_MemberShip(float val, float *ms, uint8_t* index, float* discource)
{
    if (val <= NB_){
        ms[0] = 0;
        ms[1] = 1;
        index[0] = 0;
        index[0] = 0;
    }
    else if (val > NB_ && val <= NM_){
        ms[0] = ms_calc(val, NB_, NM_);
        ms[1] = 1 - ms[0];
        index[0] = 0;
        index[1] = 1;
    }
    else if (val > NM_ && val <= NS_){
        ms[0] = ms_calc(val, NM_, NS_);
        ms[1] = 1 - ms[0];
        index[0] = 1;
        index[1] = 2;
    }
    else if (val > NS_ && val <= ZO_){
        ms[0] = ms_calc(val, NS_, ZO_);
        ms[1] = 1 - ms[0];
        index[0] = 2;
        index[1] = 3;
    }
    else if (val > ZO_ && val <= PS_){
        ms[0] = ms_calc(val, ZO_, PS_);
        ms[1] = 1 - ms[0];
        index[0] = 3;
        index[1] = 4;
    }
    else if (val > PS_ && val <= PM_){
        ms[0] = ms_calc(val, PS_, PM_);
        ms[1] = 1 - ms[0];
        index[0] = 4;
        index[1] = 5;
    }
    else if (val > PM_ && val <= PB_){
        ms[0] = ms_calc(val, PM_, PB_);
        ms[1] = 1 - ms[0];
        index[0] = 5;
        index[1] = 6;
    }
    else if (val > PB_){
        ms[0] = 1;
        ms[1] = 0;
        index[0] = 6;
        index[0] = 6;
    }
}

void Linear_Quantization()
{

}

void Calc_FuzzyPID(fuzzy_pid_type* obj)
{
    obj->err[2] = obj->err[1];
    obj->err[1] = obj->err[0];
    obj->err[0] = *obj->fdb_source - obj->ref;

    obj->E = obj->err[0];
    obj->EC = obj->err[0] - obj->err[1];

    float ms_E[2], ms_EC[2];         //隶属值
    uint8_t index_E[2], index_EC[2]; //规则表下标

    //计算隶属值
    Calc_MemberShip(obj->E, ms_E, index_E, obj->discourse);
    Calc_MemberShip(obj->EC, ms_EC, index_EC, obj->discourse);

    //去模糊化
    obj->delta_Kp = ms_E[0] * (ms_EC[0] *  ruleKp[index_E[0]][index_EC[0]] + ms_EC[1] * ruleKp[index_E[0]][index_EC[1]]) + \
                    ms_E[1] * (ms_EC[0] *  ruleKp[index_E[1]][index_EC[0]] + ms_EC[1] * ruleKp[index_E[1]][index_EC[1]]);
    obj->delta_Ki = ms_E[0] * (ms_EC[0] *  ruleKi[index_E[0]][index_EC[0]] + ms_EC[1] * ruleKi[index_E[0]][index_EC[1]]) + \
                    ms_E[1] * (ms_EC[0] *  ruleKi[index_E[1]][index_EC[0]] + ms_EC[1] * ruleKi[index_E[1]][index_EC[1]]);
    obj->delta_Kd = ms_E[0] * (ms_EC[0] *  ruleKd[index_E[0]][index_EC[0]] + ms_EC[1] * ruleKd[index_E[0]][index_EC[1]]) + \
                    ms_E[1] * (ms_EC[0] *  ruleKd[index_E[1]][index_EC[0]] + ms_EC[1] * ruleKd[index_E[1]][index_EC[1]]);

    obj->Kp += obj->delta_Kp * obj->qKp;
    obj->Ki += obj->delta_Ki * obj->qKi;
    obj->Kd += obj->delta_Kd * obj->qKd;
    obj->err_sum += obj->err[0];
    //积分限幅
    obj->err_sum = min(obj->err_sum, obj->i_max);
    obj->err_sum = max(obj->err_sum, obj->i_min); 

    #if FUZZY_PID_DELTA
    obj->output += obj->Kp * (obj->err[0] - obj->err[1]) + \
                   obj->Ki * obj->err[0] + \
                   obj->Kp * (obj->err[2] + obj->err[0] - 2 * obj->err[2]);
    #elif FUZZY_PID_POS
    obj->output = obj->Kp * obj->err[0] + \
                  obj->Ki * obj->err_sum + \
                  obj->Kp * (obj->err[0] - obj->err[1]);
    #endif
    //输出限幅
    obj->output = min(obj->output, obj->output_max);
    obj->output = max(obj->output, obj->output_min);
}