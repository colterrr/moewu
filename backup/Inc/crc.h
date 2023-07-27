#ifndef _CRC_H_
#define _CRC_H_

#include "stdint.h"

typedef enum crc_width_e
{
    WID_8 = 1,
    WID_16 = 2,
    WID_32 = 4
}crc_width;

typedef struct crc_type_s
{
    crc_width width;
    uint16_t ploy;
    uint16_t init_val;
    uint16_t xor_out;
    uint8_t refin;
    uint8_t refout;
}crc_type;

uint8_t crc_calc_8(crc_type crc_handle, uint8_t data);

#endif