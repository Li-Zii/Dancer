#include "exti.h"
#include "SysTick.h"
#include "key.h"
#include "TB6600.h"

/*******************************************************************************
* 函 数 名         : My_EXTI_Init
* 函数功能		   : 外部中断初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);//选择GPIO管脚用作外部中断线路

	
	
	//EXTI0 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//EXTI4中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
}

extern u8 flag;
extern u16 count;
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)==1&&flag!=0)
	{
		if(EXTI_P==1)
		{
			count++;
			if(Direction==1&&count==500)
			{
				Direction=!Direction;
				count=1100;
			}
				
			else if(count==1600)
			{
				count=0;
				flag=0;
			}
		}	
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}



