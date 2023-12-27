#include "bsp_spi.h"
#include "string.h"
#include "myfunc.h"

#if HARDWARE_SPI
#include "stm32f4xx_hal_spi.h"
BSP_SPI_Type SPI_Port[MAX_SPI_NUM];
#elif SOFTWARE_SPI
software_SPI_Port SPI_Port[MAX_SPI_NUM];
GPIO_TypeDef* GPIOx_SCK;
GPIO_TypeDef* GPIOx_MOSI;
GPIO_TypeDef* GPIOx_MISO;
GPIO_TypeDef* GPIOx_NSS;
uint16_t GPIO_Pin_SCK;
uint16_t GPIO_Pin_MOSI;
uint16_t GPIO_Pin_MISO;
uint16_t GPIO_Pin_NSS;
#endif

void BSP_SPI_Init(void)
{
    #if HARDWARE_SPI
    SPI_Port[0].hspi = &hspi1;
    SPI_Port[1].hspi = &hspi2;
    #elif SOFTWARE_SPI
    SPI_Port[0].IOx_SCK = GPIOA;
    SPI_Port[0].Pin_SCK = GPIO_PIN_5;
    SPI_Port[0].IOx_MISO = GPIOA;
    SPI_Port[0].Pin_MISO = GPIO_PIN_6;
    SPI_Port[0].IOx_MOSI = GPIOA;
    SPI_Port[0].Pin_MOSI = GPIO_PIN_7;


    for (uint8_t i = 0; i < MAX_SPI_NUM; i++){
        //时钟空闲为低电平
        HAL_GPIO_WritePin(SPI_Port[i].IOx_SCK, SPI_Port->Pin_SCK, 0);
    }

    #endif
}

#if SOFTWARE_SPI
void BSP_SPI_TransmitByte(uint8_t port_index, uint8_t data)
{
    GPIOx_SCK = SPI_Port[port_index].IOx_SCK;
    GPIOx_MOSI = SPI_Port[port_index].IOx_MOSI;
    GPIO_Pin_SCK = SPI_Port[port_index].Pin_SCK;
    GPIO_Pin_MOSI = SPI_Port[port_index].Pin_MOSI;

    for (uint8_t i = 0; i < 8; i++){
        L_SCK;
        if (data & 0x80){
            H_MOSI;
        }
        else {
            L_MOSI;
        }
        H_SCK;
        delay_us(1);
        data<<=1;
    }
    L_SCK;
}
uint8_t BSP_SPI_ReceiveByte(uint8_t port_index)
{
    GPIOx_SCK = SPI_Port[port_index].IOx_SCK;
    GPIOx_MOSI = SPI_Port[port_index].IOx_MOSI;
    GPIO_Pin_SCK = SPI_Port[port_index].Pin_SCK;
    GPIO_Pin_MOSI = SPI_Port[port_index].Pin_MOSI;

    uint8_t data = 0;
    L_SCK;
    for (uint8_t i = 0; i < 8; i++){
        delay_us(1);
        H_SCK;
        data <<= 1;
        if (READ_MISO)
            data++;
        L_SCK;
    }
    return data;
}
#endif

void BSP_SPI_Transmit(uint8_t port_index, uint8_t* pdata, uint8_t len){
    #if HARDWARE_SPI
    HAL_SPI_Transmit_DMA(SPI_Port->hspi, pdata, len);
    #elif SOFTWARE_SPI
    for (uint8_t i = 0; i < len; i++){
        BSP_SPI_TransmitByte(port_index, pdata[i]);
    }
    #endif
}

void BSP_SPI_Receive(uint8_t port_index, uint8_t* rxbuf, uint8_t len)
{
    #if HARDWARE_SPI
    // uint32_t now_time = HAL_GetTick();
    // while (__HAL_SPI_GET_FLAG(SPI_Port[port_index].hspi,SPI_FLAG_RXNE) == RESET)
    //     if(HAL_GetTick() - now_time > SPI_WAIT_TIME)
    //         return;
    HAL_SPI_Receive_DMA(SPI_Port[port_index].hspi, rxbuf, len);

    #elif SOFTWARE_SPI
    for (uint8_t i = 0; i < len; i++){
        rxbuf[i] = BSP_SPI_ReceiveByte(port_index);
    }
    
    #endif
}

void BSP_SPI_TransmitReceive(uint8_t port_index, uint8_t* pTxdata, uint8_t* pRxdata, uint8_t len){
    #if HARDWARE_SPI
    HAL_SPI_TransmitReceive(SPI_Port->hspi, pTxdata, pRxdata, len, SPI_WAIT_TIME);
    #endif
}
