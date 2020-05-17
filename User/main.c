
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "pwm.h"
#include "key.h"
#include "TB6600.h"
#include "exti.h"


u8 flag=0;//步进电机转动标志
u16 count=0;

int main()
{
	u16 i=0; 
	u8 key=0,rest_key=0;//键值
	u8 fx=0;//舵机方向标志
	u16 pwm=150;//舵机PWM值（中值）
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	KEY_Init();
	My_EXTI_Init();  //外部中断初始化
	TB6600_Init(); 
	TIM3_CH2_PWM_Init(2000,72-1);
	TIM4_CH2_PWM_Init(2000,720-1); 
	Direction=0;
	Enable=0;
	M1=1;
	M2=1;
	M3=1;
	TIM_SetCompare2(TIM3,0);  //步进待机
	TIM_SetCompare2(TIM4,pwm);  //舵机待机
//	delay_ms(2000);
	
	while(1)
	{
		rest_key=REST_Scan();
		if(rest_key==0)
		{
			key=KEY_Scan(0);   //扫描按键
			if(key==KEY_C&&flag==0)
			{
				Direction=1;
				Enable=0;
				flag=1;
			}
			if(key==KEY_D&&flag==0)
			{
				Direction=0;
				Enable=0;
				flag=1;
			}			
			if(flag==0)
			{
				TIM_Cmd(TIM3,DISABLE); //关定时器
				TIM3_CH2_PWM_Init(4000,72-1);
				TIM_Cmd(TIM3,ENABLE); //开定时器
				TIM_SetCompare2(TIM3,0);  //步进待机
//				Enable=1;
				count=0;
			}
			if(flag!=0)
			{
				TIM_Cmd(TIM3,DISABLE); //关定时器
				TIM3_CH2_PWM_Init(2000,72-1);
				TIM_Cmd(TIM3,ENABLE); //开定时器
				TIM_SetCompare2(TIM3,1500); //步进转动
//				j++;
//				if(j>=320)
//				{
//					flag=0;
//					j=0;
//				}
			}
		}
		else 
		{
			if(rest_key==KEY_A)//复位
			{
				Direction=0;
				Enable=0;
				flag=0;
				TIM_Cmd(TIM3,DISABLE); //关定时器
				TIM3_CH2_PWM_Init(2000,72-1);
				TIM_Cmd(TIM3,ENABLE); //开定时器
				TIM_SetCompare2(TIM3,1500); //步进转动
			}
			if(rest_key==KEY_B)//退球
			{
				Direction=1;
				Enable=0;
				flag=0;
				TIM_Cmd(TIM3,DISABLE); //关定时器
				TIM3_CH2_PWM_Init(2000,72-1);
				TIM_Cmd(TIM3,ENABLE); //开定时器
				TIM_SetCompare2(TIM3,1500); //步进转动
			}
		}
		
/***************舵机摆动************/
		if(fx==0)
		{
			pwm=pwm+1;
			if(pwm==200)
			{
				fx=1;
				TIM_SetCompare2(TIM4,190);	
			}
		}
		else
		{
			pwm=pwm-1;
			if(pwm==100)
			{
				fx=0;
				TIM_SetCompare2(TIM4,110);
			}
		}
//		TIM_SetCompare2(TIM4,pwm);	
/*************系统提示灯************/
		i++;
		if(i%20==0)
		{
			led1=!led1;      //LED1状态取反
		}
		delay_ms(10);	
	}
}


