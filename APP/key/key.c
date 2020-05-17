#include "key.h"
#include "SysTick.h"

/*******************************************************************************
* 函 数 名         : KEY_Init
* 函数功能		   : 按键初始化
*******************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=KEY_A_Pin|KEY_B_Pin|KEY_C_Pin|KEY_D_Pin|EXTI_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_Port,&GPIO_InitStructure);
}

/*******************************************************************************
* 函 数 名         : KEY_Scan
* 函数功能		   : 按键扫描检测
*******************************************************************************/
u8 KEY_Scan(u8 mode)
{
	static u8 key=1;
	if(key==1&&(K_C==0||K_D==0)) //任意一个按键按下
	{
		delay_ms(10);  //消抖
		key=0;
		if(K_C==0)
		{
			return KEY_C; 
		}
		else if(K_D==0)
		{
			return KEY_D; 
		}
	}
	else if(K_C==1&&K_D==1)    //无按键按下
	{
		key=1;
	}
	if(mode==1) //连续按键按下
	{
		key=1;
	}
	return 0;
}


u8 REST_Scan()
{
	if(K_A==0||K_B==0)
	{
		delay_ms(10);
		if(K_A==0)
		{
			return KEY_A; 
		}
		else if(K_B==0)
		{
			return KEY_B; 
		}
	}
	return 0;
}

