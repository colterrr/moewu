#include "SHT_sensor.h"
#include "string.h"
#include "myfunc.h"
#include "stdlib.h"
#include "instance.h"
//周期模式
const uint8_t periodic_set[] = {0x20, 0x32, 0x20, 0x24, 0x20, 0x2F,\
                                0x21, 0x30, 0x21, 0x26, 0x21, 0x2D,\
                                0x22, 0x36, 0x22, 0x20, 0x22, 0x2B,\
                                0x23, 0x34, 0x23, 0x22, 0x23, 0x29,\
                                0x27, 0x37, 0x27, 0x21, 0x27, 0x2A};

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

error_handle_type SHT_sensor_set_periodic(uint8_t iic_index, setting_periodic_mode mode)
{
    memcpy(SHT_txbuffer, periodic_set + mode * 2, 2);
    Master_Transmit(iic_index, SHT_txbuffer, 2);
    if(!BSP_IIC_sta(iic_index)){
        return trans_err;
    }
    else {
        return normal;
    }
}

error_handle_type SHT_sensor_break(uint8_t iic_index, uint8_t ADDR)
{
    memcpy(SHT_txbuffer, periodic_break, 2);
    Master_Transmit(iic_index, SHT_txbuffer, 2);
    if(!BSP_IIC_sta(iic_index)){
        return trans_err;
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

error_handle_type SHT_sensor_data_handle(uint8_t iic_index, temp_humid_data* data_obj)
{
    memcpy(SHT_txbuffer, periodic_fetch, 2);
    Master_Complex(SHT_PORT_INDEX, SHT_txbuffer, 2, SHT_rxbuffer, 6);
    if (!BSP_IIC_sta(iic_index)) return trans_err;

    //(CRC校验?)

    data_obj->temperature = ((uint16_t)SHT_rxbuffer[0] << 8) | SHT_rxbuffer[1];
    data_obj->humidity = ((uint16_t)SHT_rxbuffer[3] << 8) | SHT_rxbuffer[4];

    return normal;
}

void SHT_data_calc(SHT_data* data_obj)
{
    float a = 0,b = 0;
    for (uint8_t i = 0; i < data_obj->num; i++){
        a += (data_obj->pdata_real[i].humidity = ((float)data_obj->pdata[i].humidity / 65535) * 100);
        b += (data_obj->pdata_real[i].temperature = ((float)data_obj->pdata[i].temperature / 65535) * 175 - 45);
    }
    data_obj->aver_data.humidity = a /= data_obj->num;
    data_obj->aver_data.temperature = b /= data_obj->num;
}

void SHT_sensor_Init(void)
{
    database.SHT_data_p = &my_SHT_data;
    my_SHT_data.num = SHT_NUM;
    database.SHT_sta = module_err;
    BSP_IIC_setpara(SHT_PORT_INDEX, GPIOB, GPIO_PIN_6, GPIOB, GPIO_PIN_7, SHT_ADDR);

    SHT_arr_Create(&my_SHT_data);
    database.SHT_sta = SHT_sensor_set_periodic(SHT_PORT_INDEX, Medium_2);
}

void sht_sensor_task(void)
{
    database.SHT_sta = SHT_sensor_data_handle(SHT_PORT_INDEX, my_SHT_data.pdata);
    SHT_data_calc(&my_SHT_data);
}