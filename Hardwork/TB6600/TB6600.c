#include "TB6600.h"

void TB6600_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	
	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* 初始化GPIO */
}
