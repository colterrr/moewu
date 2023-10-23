#include "bsp_flash.h"
HAL_StatusTypeDef flash_sta;
void BSP_Flash_Write(uint16_t offset_index, uint8_t data)
{
    //while(__HAL_FLASH_GET_FLAG(FLASH_SR_BSY));
    HAL_FLASH_Unlock();
    flash_sta = HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_BYTE, USED_FLASH_ADDR + offset_index, data);
    HAL_FLASH_Lock();
}

uint8_t BSP_Flash_Read(uint16_t offset_index)
{
    return *(__IO uint8_t*)(USED_FLASH_ADDR + offset_index);
}
