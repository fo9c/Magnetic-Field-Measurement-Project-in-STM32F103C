#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  * ��    ����������ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void Key_Init(void)
{
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//����GPIOB��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//��PB1��PB11���ų�ʼ��Ϊ��������
}

/**
  * ��    ����������ȡ����
  * ��    ������
  * �� �� ֵ�����°����ļ���ֵ����Χ��0~2������0����û�а�������
  * ע������˺���������ʽ��������������ס����ʱ�������Ῠס��ֱ����������
  */
int Key_GetNum(void)
{
	uint8_t KeyNum = 0;		//���������Ĭ�ϼ���ֵΪ0
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0)			//��PB1����Ĵ�����״̬�����Ϊ0�����������1����
	{
		Delay_ms(20);											//��ʱ����
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0);	//�ȴ���������
		Delay_ms(20);											//��ʱ����
		KeyNum = 1;												//�ü���Ϊ1
	}
	
	/*
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)			//��PB11����Ĵ�����״̬�����Ϊ0�����������2����
	{
		Delay_ms(20);											//��ʱ����
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);	//�ȴ���������
		Delay_ms(20);											//��ʱ����
		KeyNum = 2;												//�ü���Ϊ2
	}
	*/
	return KeyNum;			//���ؼ���ֵ�����û�а������£�����if���������������ΪĬ��ֵ0
}
