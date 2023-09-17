#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#include "stdint.h"
#include "spi.h"

#define MAX_SPI_NUM 1

typedef struct BSP_SPI_Type_s
{
    SPI_HandleTypeDef* hspi;
}BSP_SPI_Type;

void BSP_SPI_Transmit(uint8_t port_index, uint8_t* pdata, uint16_t len);
void BSP_SPI_Init(void);

#endif