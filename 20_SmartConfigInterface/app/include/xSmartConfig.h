#ifndef MSMARTCONFIG_H_INCLUDED
#define MSMARTCONFIG_H_INCLUDED

typedef enum {
	xSmartConfig_Status_Succeed = 0, //���ӳɹ�
	xSmartConfig_Status_Failed = 1,  //����ʧ��
	xSmartConfig_Status_Get_Pas = 3, //�ɹ��õ��ֻ����������ص��ʺź�������Ϣ
	xSmartConfig_Status_Connectting_GateWay = 4,  //������������
	xSmartConfig_Status_Connectting_Early = 5,  //δ��ʼ����
} xSmartConfig_Status_Code;

typedef void (*xSmartConfig_CallBack)(xSmartConfig_Status_Code statusCode);

//��ʼһ������
void xSmartConfig_Start();
//ע��ص�����
void register_xSmartConfigCallBack(xSmartConfig_CallBack callBack);

#endif
