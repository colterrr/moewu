#ifndef _RESPI_SEND_H_
#define _RESPI_SEND_H_

#include "stdint.h"

#pragma pack(1)
typedef struct Respi_sendpack_s
{
    uint32_t temp;
    uint32_t humid;   
    uint16_t CO2;
    uint8_t UV;
}Respi_sendpack;
#pragma pack()

void respi_send(void);

#endif