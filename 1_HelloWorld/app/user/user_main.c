/*
 * user_main.c
 *
 *  Created on: Jan 2, 2018
 *      Author: DingSn
 */

#include "driver/uart.h"  //����0��Ҫ��ͷ�ļ�
#include "osapi.h"  //����1��Ҫ��ͷ�ļ�
#include "user_interface.h" //WIFI������Ҫ��ͷ�ļ�
#include "gpio.h"  //�˿ڿ�����Ҫ��ͷ�ļ�
#include "ets_sys.h"
#include "user_devicefind.h"
#include "user_webserver.h"
#if ESP_PLATFORM
#include "user_esp_platform.h"
#endif

void user_init(void)
{
    uart_init(115200, 115200);//���ô���0�ʹ���1�Ĳ�����
    uart0_sendStr("\r\nSDK version:");
    uart0_sendStr(system_get_sdk_version());
	char buf[64]={0};
	os_sprintf(buf, "\r\nHello world, compiled time:%s %s", __DATE__, __TIME__);
	uart0_sendStr(buf);
	uart0_sendStr("\r\nUart init ok.\r\n");
}

void user_rf_pre_init()
{

}
