#include "bsp_spi.h"

BSP_SPI_Type SPI_Port[MAX_SPI_NUM];

void BSP_SPI_Init(void)
{
    SPI_Port[0].hspi = &hspi1;
}

void BSP_SPI_Transmit(uint8_t port_index, uint8_t* pdata, uint16_t len)
{
    HAL_SPI_Transmit_DMA(SPI_Port[port_index].hspi, pdata, len);
}

