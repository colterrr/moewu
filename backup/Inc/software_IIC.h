#ifndef _SOFTWARE_IIC_H_
#define _SOFTWARE_IIC_H_

#include "stdint.h"
#include "main.h"

// 默认设置：
// 从机地址7bit
// 时钟周期8us
// 时序参数如下
// t_HIGH = t_LOW = 4us
// t_HD-DAT = t_SU-DAT = t_HD-STA = t_SU-STA = t_HD-STO = t_SU-STO = 2us
// t_R_SDA, t_F_SDA, t_R_SCL, t_F_SCL 忽略不计

/***软件IIC的GPIO在这里配置***/

#define GPIOx_CL GPIOB
#define GPIOx_DA GPIOB
#define GPIO_Pin_CL GPIO_PIN_6
#define GPIO_Pin_DA GPIO_PIN_7

/***----------------------***/

#define H_SCL HAL_GPIO_WritePin(GPIOx_CL,GPIO_Pin_CL,GPIO_PIN_SET)
#define L_SCL HAL_GPIO_WritePin(GPIOx_CL,GPIO_Pin_CL,GPIO_PIN_RESET)

#define H_SDA HAL_GPIO_WritePin(GPIOx_DA,GPIO_Pin_DA,GPIO_PIN_SET)
#define L_SDA HAL_GPIO_WritePin(GPIOx_DA,GPIO_Pin_DA,GPIO_PIN_RESET)

#define READ_DA HAL_GPIO_ReadPin(GPIOx_DA,GPIO_Pin_DA)

//software_IIC_Port结构体下表示传输状态的枚举变量
typedef enum IIC_comu_status_e
{
    IIC_ERR = 0,  //并没有发完或收完要求规模的数据，传输被接收方叫停
    IIC_OK
}IIC_comu_status;

typedef enum ACK_value_e
{
    ACK = 0,
    NACK
}ACK_value;

typedef struct software_IIC_Port_s
{
    //uint16_t speed_kHZ;
    uint8_t slave_ADDR;        //7位从机地址，最高位无意义
    IIC_comu_status status;
}software_IIC_Port;

void Master_Transmit(software_IIC_Port* port, uint8_t* pdata, uint16_t len);
void Master_Receive(software_IIC_Port* port, uint8_t* rxbuf, uint16_t len);
void Master_Complex(software_IIC_Port* port, uint8_t* pdata, uint16_t len_t, uint8_t* rxbuf, uint16_t len_r);

void Master_Transmit_Byte(uint8_t Byte);
uint8_t Master_Receive_Byte();

void Master_Start();
void Master_Stop();

uint8_t Master_wait_ACK();
void Master_N_ACK(ACK_value sig);

#endif
