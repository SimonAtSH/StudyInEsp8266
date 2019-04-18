#include "c_types.h"

#ifndef APP_INCLUDE_DRIVER_DS1302_H_
#define APP_INCLUDE_DRIVER_DS1302_H_

/**********************����ѡ��*******************/
#define DS1302_MASTER_IO_MUX PERIPHS_IO_MUX_MTDI_U
#define DS1302_MASTER_SCLK_MUX PERIPHS_IO_MUX_MTMS_U
#define DS1302_MASTER_RST_MUX PERIPHS_IO_MUX_MTCK_U
#define DS1302_MASTER_IO_GPIO 12
#define DS1302_MASTER_SCLK_GPIO 14
#define DS1302_MASTER_RST_GPIO 13
#define DS1302_MASTER_IO_FUNC FUNC_GPIO12
#define DS1302_MASTER_SCLK_FUNC FUNC_GPIO14
#define DS1302_MASTER_RST_FUNC FUNC_GPIO13
/**********************end*******************/

#define DS1302_MASTER_SCLK_LOW_RST_LOW()  \
    gpio_output_set(0, 1<<DS1302_MASTER_SCLK_GPIO | 1<<DS1302_MASTER_RST_GPIO, 1<<DS1302_MASTER_SCLK_GPIO | 1<<DS1302_MASTER_RST_GPIO, 0)



#define ds1302_sec_add 0x80 //�����ݵ�ַ
#define ds1302_min_add 0x82 //�����ݵ�ַ
#define ds1302_hr_add 0x84 //ʱ���ݵ�ַ
#define ds1302_date_add 0x86 //�����ݵ�ַ
#define ds1302_month_add 0x88 //�����ݵ�ַ
#define ds1302_day_add 0x8a //�������ݵ�ַ
#define ds1302_year_add 0x8c //�����ݵ�ַ
#define ds1302_control_add 0x8e //�������ݵ�ַ
#define ds1302_charger_add 0x90
#define ds1302_clkburst_add 0xbe

void DS1302_master_gpio_init(void);
//��Vcc=2.0vʱ�����ʱ��Ƶ��Ϊ0.5MHz����Vcc=5.0vʱ�����ʱ��Ƶ��Ϊ2.0MHz.

void DS1302_master_writeByte(uint8 addr,uint8 wrdata); //��DS1302д��һ�ֽ�����

uint8 DS1302_master_readByte(uint8 addr);//��DS1302����һ�ֽ�����

void DS1302_Clock_init(unsigned char *pDate);//��ʼ��ʱ������

#endif /* APP_INCLUDE_DRIVER_DS1302_H_ */
