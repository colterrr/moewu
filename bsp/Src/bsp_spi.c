#include "bsp_spi.h"
#include "string.h"
#include "myfunc.h"

#if HARDWARE_SPI
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

    #elif SOFTWARE_SPI
    for (uint8_t i = 0; i < MAX_SPI_NUM; i++){
        //时钟空闲为低电平
        HAL_GPIO_WritePin(SPI_Port[i].IOx_SCK, SPI_Port->Pin_SCK, 0);
    }

    #endif
}

void BSP_SPI_Transmit_Byte(uint8_t port_index, uint8_t* pdata)
{
    #if HARDWARE_SPI
    uint32_t now_time = HAL_GetTick();
    while (__HAL_SPI_GET_FLAG(SPI_Port[port_index].hspi,SPI_FLAG_TXE) == RESET)
        if(HAL_GetTick() - now_time > SPI_WAIT_TIME)
            break;
    __HAL_SPI_CLEAR_FLAG(SPI_Port[port_index].hspi,SPI_FLAG_TXE);
    HAL_SPI_Transmit(SPI_Port[port_index].hspi, pdata, 1, SPI_WAIT_TIME);

    SPI_Port[port_index].hspi->Instance->DR = *pdata;
    #elif SOFTWARE_SPI
    GPIOx_SCK = SPI_Port[port_index].IOx_SCK;
    GPIOx_MOSI = SPI_Port[port_index].IOx_MOSI;
    GPIO_Pin_SCK = SPI_Port[port_index].Pin_SCK;
    GPIO_Pin_MOSI = SPI_Port[port_index].Pin_MOSI;

    uint8_t data = *pdata;
    for (uint8_t i = 0; i < 8; i++){
        L_SCK;
        if (data & 0x80){
            H_MOSI;
        }
        else {
            L_MOSI;
        }
        H_SCK;
        delay_us(5);
    }
    #endif
}

void BSP_SPI_Receive(uint8_t port_index, uint8_t* rxbuf, uint8_t len)
{
    #if HARDWARE_SPI
    //HAL_SPI_Receive_IT(SPI_Port[port_index].hspi, rxbuf, len);

    #elif SOFTWARE_SPI
    GPIOx_SCK = SPI_Port[port_index].IOx_SCK;
    GPIOx_MISO = SPI_Port[port_index].IOx_MISO;
    GPIO_Pin_SCK = SPI_Port[port_index].Pin_SCK;
    GPIO_Pin_MISO = SPI_Port[port_index].Pin_MISO;

    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++){
        L_SCK;
        if (READ_MISO);
    }
    
    #endif
}
