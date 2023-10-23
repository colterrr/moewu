#ifndef FLASH_H_
#define FLASH_H_

#include "main.h"
#include "stdint.h"

#define USED_FLASH_ADDR 0x08030000//用来存储的flash首地址
#define USED_FLASH_LEN 256        //用来存储的flash空间总长度s

void BSP_Flash_Write(uint16_t offset_index, uint8_t data);
uint8_t BSP_Flash_Read(uint16_t offset_index);
#endif