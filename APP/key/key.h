#ifndef _key_H
#define _key_H


#include "system.h"
 
#define KEY_D_Pin    GPIO_Pin_3    //定义K_D管脚
#define KEY_C_Pin    GPIO_Pin_2    //定义K_C管脚
#define KEY_B_Pin    GPIO_Pin_1   //定义K_B管脚
#define KEY_A_Pin    GPIO_Pin_0  //定义KEY_A管脚
#define EXTI_Pin		 GPIO_Pin_4

#define KEY_Port (GPIOA) //定义端口


//使用位操作定义
#define K_A PAin(0)
#define K_B PAin(1)
#define K_C PAin(2)
#define K_D PAin(3)
#define EXTI_P PAin(4)


//定义各个按键值  
#define KEY_A 1
#define KEY_B 2
#define KEY_C 3
#define KEY_D 4  



void KEY_Init(void);
u8 KEY_Scan(u8 mode);
u8 REST_Scan(void);
#endif


