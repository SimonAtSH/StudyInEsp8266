/*
 * user_esp_now.c
 *
 *  Created on: 2017��7��8��
 *      Author: Administrator
 */

#include "ets_sys.h"
#include "osapi.h"
#include "user_interface.h"
#include "espnow.h"

//#define CONTROLLER
#define SLAVE

// �Ƿ�ʹ�ü���
#define SECURITY	0

#if SECURITY
u8 g_key[16]= {0x12, 0x34, 0x56, 0x78,
			0x12, 0x34, 0x56, 0x78,
			0x12, 0x34, 0x56, 0x78,
			0x12, 0x34, 0x56, 0x78};
#endif

// ʹ�������MAC��ַ��station����MAC�ƺ�����
u8 controller_mac[6] = {0xA0, 0x20, 0xA6, 0xAA, 0xAA, 0xAA};
u8 slave_mac[6] = {0xA2, 0x20, 0xA6, 0x55, 0x55, 0x55};


#define ESP_NOW_SEND_INTERVAL	3000
static os_timer_t g_esp_now_timer;

/*
 * ������user_esp_now_recv_cb
 * ˵����ESP-NOW���ջص�����
 */
static void ICACHE_FLASH_ATTR
user_esp_now_recv_cb(u8 *macaddr, u8 *data, u8 len)
{
	int i;
	static u16 ack_count=0;
	u8 ack_buf[16];
	u8 recv_buf[17];
	os_printf("now from[");

	for(i = 0; i < 6; i++){
		os_printf("%02X ", macaddr[i]);
	}
	os_printf(" len: %d]:", len);

	os_bzero(recv_buf, 17);
	os_memcpy(recv_buf, data, len<17?len:16);
	os_printf(recv_buf);
	os_printf("\r\n");

	if (os_strncmp(data, "ACK", 3) == 0){
		return;
	}else{

	}

	os_sprintf(ack_buf, "ACK[%08x]", ack_count++);
	esp_now_send(macaddr, ack_buf, os_strlen(ack_buf));
}

/*
 * ������user_esp_now_send_cb
 * ˵����ESP-NOW���ͻص�����
 */
void ICACHE_FLASH_ATTR
user_esp_now_send_cb(u8 *mac_addr, u8 status)
{
	int i;
	for(i = 0; i < 6; i++){
		os_printf("%02X ", mac_addr[i]);
	}

	if(1==status){
		os_printf("SEND FAIL!\r\n");
	}else if(0==status){
		os_printf("SEND SUCCESSFUL!\r\n");
	}
}

/*
 * ������user_esp_now_send
 * ˵����ESP-NOW���ݷ���
 */
void ICACHE_FLASH_ATTR
user_esp_now_send(u8 *mac_addr, u8 *data, u8 len)
{
	/* the demo will send to two devices which added by esp_now_add_peer() */
	//u8 result = esp_now_send(NULL, data, len);

	/* send to the specified mac_addr */
	u8 result = esp_now_send(mac_addr, data, len);
}

/*
 * ������user_esp_now_timer_cb
 * ˵������ʱ���ص�����
 */
static void ICACHE_FLASH_ATTR
user_esp_now_timer_cb(void* arg)
{
	u8 *mac = arg;
	u8* send_data = "Hello World!";
	int result = esp_now_is_peer_exist(mac);
	//os_printf("peer_exist = %d\r\n", result);
	user_esp_now_send(mac, send_data, os_strlen(send_data));
}

/*
 * ������user_esp_now_timer_init
 * ˵������ʱ���� ESP_NOW ���ݰ�
 */
void ICACHE_FLASH_ATTR
user_esp_now_timer_init(u8 *mac)
{
	os_timer_disarm(&g_esp_now_timer);
	os_timer_setfn(&g_esp_now_timer, (os_timer_func_t *)user_esp_now_timer_cb, mac);
	os_timer_arm(&g_esp_now_timer, ESP_NOW_SEND_INTERVAL, 1);
}

/*
 * ������user_esp_now_init
 * ˵����ESP-NOW��ʼ��
 */
void ICACHE_FLASH_ATTR
user_esp_now_init(void)
{
	int result;

	if (esp_now_init()==0) {
		os_printf("esp_now init ok\n");

		// ע�� ESP-NOW �հ��Ļص�����
		esp_now_register_recv_cb(user_esp_now_recv_cb);
		// ע�ᷢ���ص�����
		esp_now_register_send_cb(user_esp_now_send_cb);

#if SECURITY
		// ��������Կ
		//esp_now_set_kok(g_key, 16);
#endif

		/* role
		 * ESP_NOW_ROLE_IDLE - ����
		 * ESP_NOW_ROLE_CONTROLLER - ����
		 * ESP_NOW_ROLE_SLAVE - �ӻ�
		 * ESP_NOW_ROLE_COMBO - ��/�ӻ�
		 */
#if defined(SLAVE)
		os_printf("==================\r\n");
		os_printf("SLAVE\r\n");
		os_printf("==================\r\n");
		esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
		//esp_now_add_peer(controller_mac, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 16);
#if SECURITY
		esp_now_set_peer_key(controller_mac, g_key, 16);
#endif


#elif defined(CONTROLLER)
		os_printf("==================\r\n");
		os_printf("CONTROLLER\r\n");
		os_printf("==================\r\n");
		esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
		esp_now_add_peer(slave_mac, ESP_NOW_ROLE_SLAVE, 1, NULL, 16);

#if SECURITY
		esp_now_set_peer_key(slave_mac, g_key, 16);
#endif

		// ����Ҫ����Wi-Fi
		wifi_station_disconnect();
		//wifi_station_connect();
		user_esp_now_timer_init(slave_mac);

#endif

	} else {
		os_printf("esp_now init failed\n");
	}
}

/************************************************************************/

/*
 * ������user_esp_now_set_mac_current
 * ˵������������MAC��ַ
 */
void ICACHE_FLASH_ATTR
user_esp_now_set_mac_current(void)
{
#if defined(SLAVE)
	wifi_set_macaddr(SOFTAP_IF, slave_mac);
	wifi_set_opmode_current(SOFTAP_MODE);
#elif defined(CONTROLLER)
	// ����station MAC��ַ
	wifi_set_macaddr(STATION_IF, controller_mac);
	// ����Ϊstationģʽ
	wifi_set_opmode_current(STATION_MODE);
#endif
}

