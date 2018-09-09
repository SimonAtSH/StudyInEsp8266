
#include "driver/uart.h"  //����0��Ҫ��ͷ�ļ�
#include "osapi.h"  //����1��Ҫ��ͷ�ļ�
#include "user_interface.h"  //����1��Ҫ��ͷ�ļ�



os_timer_t checkTimer;



void user_rf_pre_init(void)
{

}


LOCAL void checkWifiStation() {

	//��ѯ ESP8266 WiFi station �ӿ����� AP ��״̬
	if (wifi_station_get_connect_status() == STATION_GOT_IP) {
		sntp_setservername(0, "0.cn.pool.ntp.org");
		sntp_setservername(1, "1.cn.pool.ntp.org");
		sntp_setservername(2, "2.cn.pool.ntp.org");
		sntp_init();
		udpwificfgg_init();
		gpioctr_init();
		os_timer_disarm(&checkTimer); //ȡ����ʱ����ʱ
	}
}



void user_init(void) {

	os_printf("\r\n\r\n");
	os_printf("SDK version:%s\n", system_get_sdk_version());
	os_printf("\r\n\r\n");

	uart_init(115200, 115200);
	wifi_set_opmode(STATIONAP_MODE);

	os_timer_disarm(&checkTimer);   //ȡ����ʱ����ʱ
	os_timer_setfn(&checkTimer, (os_timer_func_t *) checkWifiStation,
	NULL);    //���ö�ʱ���ص�����
	os_timer_arm(&checkTimer, 500, 1);      //������ʱ������λ������

}

