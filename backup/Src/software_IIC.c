#include "software_IIC.h"
#include "stdlib.h"
#include "string.h"
#include "myfunc.h"
#include "instance.h"

software_IIC_Port my_port;
/***SDA输出输入模式改变***/

void SDA_Set_Output()
{
    GPIO_InitTypeDef config ={0};
    config.Mode = GPIO_MODE_OUTPUT_PP;
    config.Pin = GPIO_Pin_DA;
    config.Pull = GPIO_NOPULL;
    config.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_DeInit(GPIOx_DA, GPIO_Pin_DA);
    HAL_GPIO_Init(GPIOx_DA, &config);
}

void SDA_Set_Input()
{
    GPIO_InitTypeDef config = {0};
    config.Mode = GPIO_MODE_INPUT;
    config.Pin = GPIO_Pin_DA;
    config.Pull = GPIO_NOPULL;
    config.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_DeInit(GPIOx_DA, GPIO_Pin_DA);
    HAL_GPIO_Init(GPIOx_DA, &config);
}

/***-------------------***/


/***开始信号S和结束信号P***/

void Master_Start()
{
    SDA_Set_Output();
    H_SCL;
    H_SDA;
    delay_us(2);//t_SU-STA 2
    L_SDA;
    delay_us(2);//t_HD-STA 2
    L_SCL; //拉低SCL，利于SDA电平变化
}

void Master_Stop()
{
    SDA_Set_Output();
    L_SCL;
    L_SDA;
    delay_us(4);//t_LOW 4
    H_SCL;
    delay_us(2);//t_SU-STO 2
    H_SDA;
}

/***---------------------***/


/***接收应答和发送应答***/

void Master_N_ACK(ACK_value sig)
{
    SDA_Set_Output();
    L_SCL;
    delay_us(2);
    if(sig)
        H_SDA;
    else 
        L_SDA;
    delay_us(2);
    H_SCL;
    delay_us(4);
    L_SCL;
}

uint8_t Master_wait_ACK()
{
    L_SCL;
    SDA_Set_Input();
    uint16_t outtime = 10000;
    delay_us(4);
    H_SCL;
    delay_us(4);
    while(READ_DA)
    {
        if(--outtime)
        {
            Master_Stop();
            return 0xff; //表示err
        }
    }
    L_SCL;
    return 0;
}

/***------------------***/


/***发送和接收一个字节数据***/

void Master_Transmit_Byte(uint8_t Byte)
{
    SDA_Set_Output();
    uint8_t i = 8;
    L_SCL;
    //发最高位，每次左移一位替换最高位
    while(i-- > 0){
        delay_us(2);//t_HD-DAT
        if (Byte & 0x80) H_SDA;
        else L_SDA;
        Byte<<=1;
        delay_us(2);//t_SU-DAT
        H_SCL;
        delay_us(4);//t_HIGH
        L_SCL;
    }
}

uint8_t Master_Receive_Byte()
{
    SDA_Set_Input();
    uint8_t i = 0;
    uint8_t Byte = 0;
    while(i++ < 8){
        Byte<<=1;    
        L_SCL;
        delay_us(4);//t_LOW
        H_SCL;
        if (READ_DA) Byte++;  
        delay_us(4);//t_HIGH
    }
    L_SCL;
    return Byte;
}

/***-------------------------***/



/***发送和接收多字节数据***/

void Master_Transmit(software_IIC_Port* port, uint8_t* pdata, uint16_t len)
{
    uint8_t ADDR = port->slave_ADDR;
    uint8_t i = 0;

    Master_Start();
    Master_Transmit_Byte(ADDR << 1);//从机地址 + W
    if(Master_wait_ACK() == 0xff){
        //收到NACK
        Master_Stop();
        port->status = IIC_ERR;
        return;
    }

    for(i = 0; i < len; i++){
        Master_Transmit_Byte(pdata[i]);
        if(Master_wait_ACK() == 0xff){
            //收到NACK
            Master_Stop();
            port->status = IIC_ERR;
            return;
        }
    }

    Master_Stop();
    port->status = IIC_OK;
    return;
}

void Master_Receive(software_IIC_Port* port, uint8_t* rxbuf, uint16_t len)
{
    uint8_t ADDR = port->slave_ADDR;
    uint8_t i = 0;

    Master_Start();
    Master_Transmit_Byte((ADDR << 1 )| 1);//从机地址 + R
    if (Master_wait_ACK() == 0xff) {
        //收到从机的NACK，停止接收
        Master_Stop();
        port->status = IIC_ERR;
        return;
    } 
    for(i = 0; i < len; i++){
        rxbuf[i] = Master_Receive_Byte();
        Master_N_ACK(!(len - i - 1)); //根据是否收完足够的数据来发送ACK或NACK
    }

    Master_Stop();
    port->status = IIC_OK;
    return;
}

void Master_Complex(software_IIC_Port* port, uint8_t* pdata, uint16_t len_t, uint8_t* rxbuf, uint16_t len_r)
{
    uint8_t ADDR = port->slave_ADDR;
    uint8_t i = 0;

    Master_Start();
    Master_Transmit_Byte(ADDR << 1);//从机地址 + W
    if(Master_wait_ACK() == 0xff){
        //收到从机的NACK，停止发送
        Master_Stop();
        port->status = IIC_ERR;
        return;
    }
   for(i = 0; i < len_t; i++){
        Master_Transmit_Byte(pdata[i]);
        if(Master_wait_ACK() == 0xff){
            //收到从机的NACK，停止发送
            Master_Stop();
            port->status = IIC_ERR;
            return;
        }
    }

    Master_Start();//复合格式二次起始信号
    delay_ms(1);   //?????为什么要等一会?????
    Master_Transmit_Byte((ADDR << 1 )| 1);//从机地址 + R
    if (Master_wait_ACK() == 0xff) {
        //收到从机的NACK，停止接收
        Master_Stop();
        port->status = IIC_ERR;
        return;
    } 
    for(i = 0; i < len_r; i++){
        rxbuf[i] = Master_Receive_Byte();
        Master_N_ACK(!(len_r - i - 1)); //根据是否收完足够的数据来发送ACK或NACK
    }

    Master_Stop();
    port->status = IIC_OK;
    return;
}

/***-----------------------------------------------***/

void soft_IIC_Init(void)
{
    database.IIC_Port_p = &my_port;
}