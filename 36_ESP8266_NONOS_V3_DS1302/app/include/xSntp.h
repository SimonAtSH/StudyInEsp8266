/*
 * xSntp.h
 *
 *  Created on: 2019��4��2��
 *      Author: XuHongYss
 */

#ifndef APP_INCLUDE_XSNTP_H_
#define APP_INCLUDE_XSNTP_H_

//ʹ�ýṹ���������ת���������
typedef  struct sntp_data{
	unsigned char  week;
	unsigned char  month;
	unsigned char  day;
	unsigned char  hour;
	unsigned char  minute;
	unsigned char  second;
	unsigned char  year;
} sntp_data;

sntp_data sntp_get_time_change(char *s);


#endif /* APP_INCLUDE_XSNTP_H_ */
