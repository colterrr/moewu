#include "instance.h"
#include "respi_send.h"
#include "bsp_uart.h"

Respi_sendpack sendpack; 

void respi_send(void)
{
    sendpack.humid = *(uint32_t*)&database.SHT_data_p->aver_data.humidity;
    sendpack.temp = *(uint32_t*)&database.SHT_data_p->aver_data.temperature;
    sendpack.CO2 = database.CO2_data_p->CO2_ppm;
    sendpack.UV = database.UV_data_p->aver_lv;
    BSP_UART_send(RPI_PORT, &sendpack, sizeof(sendpack));
}