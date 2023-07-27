#include "crc.h"
#include "stdlib.h"
#include "string.h"

//按位反转
void reverse(uint8_t* pdata, crc_width width)
{   
    uint8_t* temp = (uint8_t*)malloc(width);
    memset(temp, 0, width);
    for (uint8_t i = width; i > 0; i--){
        for (uint8_t k = 0; k < 8; k++){
            *(temp + width - i) |= ((*(pdata + i - 1) >> (7 - k)) & 1) << k;
        }
    }
    for (uint8_t i = 0; i < width; i++){
        pdata[i] = temp[i];
    }
    free(temp);
    return;
}

uint8_t crc_calc_8(crc_type crc_handle, uint8_t data)
{
    if (crc_handle.refin) reverse(&data, WID_8); //输入反转
    uint8_t crc = data ^ crc_handle.init_val; //初始值
    for (uint8_t i = 0;i < 8; i++){
        if (crc & 0x80){
            crc = (crc << 1) ^ crc_handle.ploy;
        }
        else {
            crc <<= 1;
        }
    }
    if (crc_handle.refout) reverse(&crc, WID_8); //输出反转
    crc ^= crc_handle.xor_out; //输出异或
    return crc;
}

//！！
//待修改
//！！
uint16_t crc_calc_16(crc_type crc_handle, uint16_t data)
{
    if (crc_handle.refin) reverse((uint8_t*)&data, WID_16); //输入反转
    uint16_t crc = data ^ crc_handle.init_val; //初始值
    for (uint8_t i = 0;i < 8; i++){
        if (crc & 0x8000){
            crc = (crc << 1) ^ crc_handle.ploy;
        }
        else {
            crc <<= 1;
        }
    }
    if (crc_handle.refout) reverse((uint8_t*)&crc, WID_16); //输出反转
    crc ^= crc_handle.xor_out; //输出异或
    return crc;
}