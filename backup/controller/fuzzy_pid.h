#ifndef _FUZZY_H_
#define _FUZZY_H_

#include "stdint.h"

//模糊规则表的参数
#define NB   -8
#define NM	 -5
#define NS	 -2
#define ZO	 0
#define PS	 2
#define PM	 5
#define PB	 8

//论域划分的参数
#define NB_ discource[2]*-1.0
#define NM_ discource[1]*-1.0
#define NS_ discource[0]*-1.0
#define ZO_ 0
#define PS_ discource[0]
#define PM_ discource[1]
#define PB_ discource[2]

#define FUZZY_PID_DELTA 1
#define FUZZY_PID_POS !FUZZY_PID_DELTA

typedef struct fuzzy_pid_type_s
{
    float* fdb_source; //反馈值来源
    float err[3];     //误差原始数据
    float ref;        //目标值
    float E;        
    float EC;  

    float discourse[3]; //论域的三个分界参数

    float delta_Kp; //系数增量
    float delta_Ki;
    float delta_Kd;
    float qKp;      //增益系数
    float qKi;
    float qKd;

    float Kp;
    float Ki;
    float Kd;

    float err_sum;

    float output;
    float output_max; //输出限幅
    float output_min;
    float i_max;      //积分限幅
    float i_min;
}fuzzy_pid_type;

void Calc_FuzzyPID(fuzzy_pid_type* obj);

#endif