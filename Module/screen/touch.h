//T_SIN  PC3
//T_SOUT PC2
//T_NSS  PC1
//T_SCK  PB10
//T_IRQ  PC0

#include "stdint.h"
#include "gpio.h"
#include "bsp_spi.h"

#ifndef __TOUCH_H__
#define __TOUCH_H__

#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 	  
										    
//������������
typedef struct
{
	uint8_t (*init)(void);			//��ʼ��������������
	uint8_t (*scan)(uint8_t);				//ɨ�败����.0,��Ļɨ��;1,��������;	 
	void (*adjust)(void);		//������У׼
	uint16_t x0;						//ԭʼ����(��һ�ΰ���ʱ������)
	uint16_t y0;
	uint16_t x; 						//��ǰ����(�˴�ɨ��ʱ,����������)
	uint16_t y;						   	    
	uint8_t  sta;					//�ʵ�״̬ 
								//b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������.         			  
////////////////////////������У׼����/////////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//touchtype=0��ʱ��,�ʺ�����ΪX����,����ΪY�����TP.
//touchtype=1��ʱ��,�ʺ�����ΪY����,����ΪX�����TP.
	uint8_t touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��

//�봥����оƬ��������	   
//�봥����оƬ��������	  
   
void TP_Write_Byte(uint8_t num);						//�����оƬд��һ������
uint16_t TP_Read_AD(uint8_t CMD);							//��ȡADת��ֵ
uint16_t TP_Read_XOY(uint8_t xy);							//���˲��������ȡ(X/Y)
uint8_t TP_Read_XY(uint16_t *x,uint16_t *y);					//˫�����ȡ(X+Y)
uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y);					//����ǿ�˲���˫���������ȡ
void TP_Drow_Touch_Point(uint16_t x,uint16_t y,uint16_t color);//��һ������У׼��
void TP_Draw_Big_Point(uint16_t x,uint16_t y,uint16_t color);	//��һ�����
uint8_t TP_Scan(uint8_t tp);								//ɨ��
void TP_Save_Adjdata(void);						//����У׼����
uint8_t TP_Get_Adjdata(void);						//��ȡУ׼����
void TP_Adjust(void);							//������У׼
uint8_t Touch_Init(void);							//��ʼ��
																 
void TP_Adj_Info_Show(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t fac);//��ʾУ׼��Ϣ
 		  

void TouchIRQhandle(void);

#endif

















