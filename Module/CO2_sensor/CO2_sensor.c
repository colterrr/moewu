#include "CO2_sensor.h"
#include "myfunc.h"
#include "bsp_uart.h"
#include "instance.h"

#include "string.h"

//量程
//CO2: 400~60000 ppm
//TVOC:  0~60000 ppb

//上传频率
//1HZ

//电压
//4-5V

//功耗
//<60mA
//有微弱发热现象

//例示
//43 4F 32 3A   34 30 30   70 70 6D 2C 54 56 4F 53 3A    32   70 70 64    0D 0A 
//    CO2:        400             ppm,TVOS:              2       ppd      行尾符

const uint8_t    head[4] = {0x43, 0x4F, 0x32, 0x3A};                                    //CO2:
const uint8_t  middle[9] = {0x70, 0x70, 0x6D, 0x2C, 0x54, 0x56, 0x4F, 0x53, 0x3A};      //ppm,TVOS:
const uint8_t    tail[3] = {0x70, 0x70, 0x64};                                          //ppd

uint8_t command[20] = {};
uint8_t lost_num = 0;
CO2_data my_CO2_data;

error_handle_type CO2_sensor_data_handle(CO2_data* data_obj, uint8_t* pdata, uint16_t len)
{
    uint16_t i = 0;
    uint16_t count1 = 0; uint8_t p1 = 0;
    uint16_t count2 = 0; uint8_t p2 = 0;

    //头部校对
    for (uint8_t k = 0; i < len && k < 4; k++, i++){
        if (pdata[i] != head[k])
            return data_err;
    }
    //ppm数据
    p1 = i;
    while (i < len && pdata[i] >= '0' && pdata[i] <= '9'){
        i++;
        count1++;
    }
    //中部校对
    for (uint8_t k = 0; i < len &&  k < 9; k++, i++){
        if (pdata[i] != middle[k])
            return data_err;
    }
    //ppd数据
    p2 = i;
    while (i < len && pdata[i] >= '0' && pdata[i] <= '9'){
        i++;
        count2++;
    }
    //尾部校对
    for (uint8_t k = 0; i < len && k < 3; k++, i++){
        if (pdata[i] != tail[k])
            return data_err;
    }
    //数据长度校对
    if (i == len && pdata[i-1] != 'd'){
        return data_err;
    }

    data_obj->CO2_ppm  = Str_to_uint(pdata + p1, count1);
    data_obj->TVOC_ppd = Str_to_uint(pdata + p2, count2);

    return normal;
}

void CO2_callback(UART_HandleTypeDef* huart, uint8_t* pdata, uint16_t len)
{
    lost_num = 0;
    if (my_CO2_data.step){
        if (memcmp(pdata, "OK", 2) == 0){
            database.CO2_sta = normal;
            my_CO2_data.step = data_recv;
        }
        else {
            database.CO2_sta = module_err;
            BSP_UART_send(CO2_PORT, command, my_CO2_data.cmd_len);
        }
    }
    else {
        database.CO2_sta = CO2_sensor_data_handle(&my_CO2_data, pdata, len);
    }
}

void CO2_set_peroid(uint16_t ms)
{
    memcpy(command, "AT+PRATE=", 9);
    uint8_t len = Uint_to_Str((uint32_t)ms, command + 9);
    memcpy(command + 9 + len, "\r\n", 2);
    my_CO2_data.step = comd_tran;
    my_CO2_data.cmd_len = len + 11;
    BSP_UART_send(CO2_PORT, command, my_CO2_data.cmd_len);
}

void CO2_sensor_Init(void)
{
    database.CO2_data_p = &my_CO2_data;
    database.CO2_sta = module_err;
    my_CO2_data.step = data_recv;
    BSP_UART_registerfunc(CO2_callback ,CO2_PORT);
}

void CO2_monitor(void)
{
    lost_num += 1;
    if (lost_num == 3)database.CO2_sta = module_err;
}