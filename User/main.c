
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "pwm.h"
#include "key.h"
#include "TB6600.h"
#include "exti.h"


u8 flag=0;//�������ת����־
u16 count=0;

int main()
{
	u16 i=0; 
	u8 key=0,rest_key=0;//��ֵ
	u8 fx=0;//��������־
	u16 pwm=150;//���PWMֵ����ֵ��
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_Init();
	KEY_Init();
	My_EXTI_Init();  //�ⲿ�жϳ�ʼ��
	TB6600_Init(); 
	TIM3_CH2_PWM_Init(2000,72-1);
	TIM4_CH2_PWM_Init(2000,720-1); 
	Direction=0;
	Enable=0;
	M1=1;
	M2=1;
	M3=1;
	TIM_SetCompare2(TIM3,0);  //��������
	TIM_SetCompare2(TIM4,pwm);  //�������
//	delay_ms(2000);
	
	while(1)
	{
		rest_key=REST_Scan();
		if(rest_key==0)
		{
			key=KEY_Scan(0);   //ɨ�谴��
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
				TIM_Cmd(TIM3,DISABLE); //�ض�ʱ��
				TIM3_CH2_PWM_Init(4000,72-1);
				TIM_Cmd(TIM3,ENABLE); //����ʱ��
				TIM_SetCompare2(TIM3,0);  //��������
//				Enable=1;
				count=0;
			}
			if(flag!=0)
			{
				TIM_Cmd(TIM3,DISABLE); //�ض�ʱ��
				TIM3_CH2_PWM_Init(2000,72-1);
				TIM_Cmd(TIM3,ENABLE); //����ʱ��
				TIM_SetCompare2(TIM3,1500); //����ת��
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
			if(rest_key==KEY_A)//��λ
			{
				Direction=0;
				Enable=0;
				flag=0;
				TIM_Cmd(TIM3,DISABLE); //�ض�ʱ��
				TIM3_CH2_PWM_Init(2000,72-1);
				TIM_Cmd(TIM3,ENABLE); //����ʱ��
				TIM_SetCompare2(TIM3,1500); //����ת��
			}
			if(rest_key==KEY_B)//����
			{
				Direction=1;
				Enable=0;
				flag=0;
				TIM_Cmd(TIM3,DISABLE); //�ض�ʱ��
				TIM3_CH2_PWM_Init(2000,72-1);
				TIM_Cmd(TIM3,ENABLE); //����ʱ��
				TIM_SetCompare2(TIM3,1500); //����ת��
			}
		}
		
/***************����ڶ�************/
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
/*************ϵͳ��ʾ��************/
		i++;
		if(i%20==0)
		{
			led1=!led1;      //LED1״̬ȡ��
		}
		delay_ms(10);	
	}
}


