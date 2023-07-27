#include "SHT_sensor.h"
#include "string.h"
#include "myfunc.h"
#include "stdlib.h"
#include "instance.h"
//周期模式
const uint8_t periodic_set_high[2] = {0x27, 0x37};   //10Hz
const uint8_t periodic_set_medium[2] = {0x23, 0x22}; //4Hz
const uint8_t periodic_set_low[2] = {0x22, 0x2B};    //2Hz
const uint8_t periodic_fetch[2] = {0xE0, 0x00};
const uint8_t periodic_break[2] = {0x30, 0x93};

//单次模式
//时钟拉伸不选用
const uint8_t single_set_high[2] = {0x2C, 0x06};
const uint8_t single_set_medium[2] = {0x24, 0x0B};
const uint8_t single_set_low[2] = {0x24, 0x16};

//周期停止命令
const uint8_t break_command[2] = {0x30, 0x93};

SHT_data my_SHT_data;

uint8_t SHT_txbuffer[10] = {};
uint8_t SHT_rxbuffer[10] = {};

error_handle_type SHT_sensor_set_high(software_IIC_Port* port)
{
    port->slave_ADDR = 0x45;
    memcpy(SHT_txbuffer, periodic_set_high, 2);
    Master_Transmit(port, SHT_txbuffer, 2);
    if(port->status == IIC_ERR){
        return trans_error;
    }
    else {
        return normal;
    }
}

error_handle_type SHT_sensor_break(software_IIC_Port* port)
{
    port->slave_ADDR = 0x45;
    memcpy(SHT_txbuffer, periodic_break, 2);
    Master_Transmit(port, SHT_txbuffer, 2);
    if(port->status == IIC_ERR){
        return trans_error;
    }
    else {
        return normal;
    }
}

//根据num这一变量创建数组
void SHT_arr_Create(SHT_data* data_obj)
{
    uint16_t num = data_obj->num;
    data_obj->pdata = malloc(num * sizeof(temp_humid_data));
    data_obj->pdata_real = malloc(num * sizeof(real_data));
}

error_handle_type SHT_sensor_data_handle(software_IIC_Port* port, temp_humid_data* data_obj)
{
    port->slave_ADDR = 0x45;
    Master_Complex(port, SHT_txbuffer, 2, SHT_rxbuffer, 6);
    if (port->status == IIC_ERR) return trans_error;

    //(CRC校验?)

    data_obj->temperature = ((uint16_t)SHT_rxbuffer[0] << 8) | SHT_rxbuffer[1];
    data_obj->humidity = ((uint16_t)SHT_rxbuffer[3] << 8) | SHT_rxbuffer[4];

    return normal;
}

void SHT_data_calc(SHT_data* data_obj)
{
    for (uint8_t i = 0; i < data_obj->num; i++){
        data_obj->aver_data.humidity += (data_obj->pdata_real[i].humidity = ((float)data_obj->pdata[i].humidity / 65535) * 100);
        data_obj->aver_data.humidity += (data_obj->pdata_real[i].temperature = ((float)data_obj->pdata[i].temperature / 65535) * 175 - 45);
    }
    data_obj->aver_data.humidity /= data_obj->num;
    data_obj->aver_data.temperature /= data_obj->num;
}

void SHT_sensor_Init(void)
{
    database.SHT_data_p = &my_SHT_data;
    SHT_arr_Create(&my_SHT_data);
}