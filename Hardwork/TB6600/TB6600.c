#include "TB6600.h"

void TB6600_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
}
