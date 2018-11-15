
#include "driver/uart.h"  //����0��Ҫ��ͷ�ļ�
#include "osapi.h"  //����1��Ҫ��ͷ�ļ�
#include "user_interface.h" //WIFI������Ҫ��ͷ�ļ�
#include "gpio.h"  //�˿ڿ�����Ҫ��ͷ�ļ�
#include "pwm.h"  //pwm������Ҫ��ͷ�ļ�


os_timer_t timer;
uint8 type,x,y,z;
uint32 duty=0;
void ICACHE_FLASH_ATTR display(void *arg)
{
	for(y=0;y<3;y++)
	{
		for(z=0;z<12;z++)
		{
			duty=z*2000;
			type=y;
			pwm_set_duty(duty,type);//���� PWM ĳ��ͨ���źŵ�ռ�ձ�, duty ռ�ձȵ�ֵ, type��ǰҪ���õ� PWM ͨ��
			pwm_start();//������ɺ���Ҫ���� pwm_start,PWM ��ʼ
		}
	}



}
void user_init()
{
	uint32 pwm_duty_init[3] =
	{ 0 };
	uint32 io_info[][3] =
	{
	{ PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12, 12 },
	{ PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13, 13 },
	{ PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15, 15 }, };
	pwm_init(1000, pwm_duty_init, 3, io_info); //��ʼ�� PWM��1000����,pwm_duty_initռ�ձ�,3ͨ����,io_info��ͨ���� GPIO Ӳ������
	for (x = 0; x < 3; x++)
	{
		 type=x;
	     pwm_set_duty(duty,type);//���� PWM ĳ��ͨ���źŵ�ռ�ձ�, duty ռ�ձȵ�ֵ, type��ǰҪ���õ� PWM ͨ��
		 pwm_start();//������ɺ���Ҫ���� pwm_start,PWM ��ʼ
	}
	os_timer_disarm(&timer);
	os_timer_setfn(&timer,display,NULL);
	os_timer_arm(&timer,1000,1);
}
void user_rf_pre_init()
{

}
