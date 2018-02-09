/*********************************************************************************************
�������� ����������LED����ȡGPIO�ڵ�״̬��
��д�ˣ� ���� ��
��дʱ�䣺����
Ӳ��֧�֣�����
�ӿ�˵��������
�޸���־������
����NO.1-								
/*********************************************************************************************
˵����

/*********************************************************************************************/
#include "driver/uart.h"  //����0��Ҫ��ͷ�ļ�
#include "osapi.h"  //����1��Ҫ��ͷ�ļ�
#include "user_interface.h" //WIFI������Ҫ��ͷ�ļ�
#include "gpio.h"  //�˿ڿ�����Ҫ��ͷ�ļ�

void delay_ms(uint16 x)
{
	for(;x>0;x--)
	{
	  os_delay_us(1000);
	}
}

void  user_init()//��ʼ��
{
	uint8 bz=0;

    uart_init(74880, 74880);//���ô���0�ʹ���1�Ĳ�����

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14);//ѡ��GPIO14
    GPIO_OUTPUT_SET(GPIO_ID_PIN(14), 1);//GPIO14Ϊ��

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2);//ѡ��GPIO2
    GPIO_DIS_OUTPUT(GPIO_ID_PIN(2)) ; // ����GPIO2Ϊ����

    while(1)
    {
    	system_soft_wdt_feed();//��������ι�¿��Ź�  �����ÿ��Ź���λ

	    if(GPIO_INPUT_GET(GPIO_ID_PIN(2))==0x00)//��ȡGPIO2��ֵ����������Ϊ0
	    {
			delay_ms(20); //��ʱ20MS��ȥ��
			if(GPIO_INPUT_GET(GPIO_ID_PIN(2))==0x00)
			{
				bz++;
				if(bz==2)bz=0;
				if(bz==1)GPIO_OUTPUT_SET(GPIO_ID_PIN(14), 0);           //GPIO14Ϊ��
				if(bz==0)GPIO_OUTPUT_SET(GPIO_ID_PIN(14), 1);			//GPIO14Ϊ��

				while(GPIO_INPUT_GET(GPIO_ID_PIN(2))==0x00);           //�ȴ������ͷ�
			}
		}

    }

}

void user_rf_pre_init()
{

}
