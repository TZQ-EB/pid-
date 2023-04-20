/***********************************************
公司：轮趣科技（东莞）有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com 
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：5.7
修改时间：2021-04-29

 
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:5.7
Update：2021-04-29

All rights reserved
***********************************************/
#include "motor.h"
/**************************************************************************
Function: Initialize Motor Interface
Input   : none
Output  : none
函数功能：初始化电机接口
入口参数：无
返回  值：无
**************************************************************************/
void MiniBalance_Motor_Init(void)
{
	RCC->APB2ENR|=1<<3;       //PORTB时钟使能   
	GPIOB->CRH&=0X0000FFFF;   //PORTB12 13 14 15推挽输出
	GPIOB->CRH|=0X22220000;   //PORTB12 13 14 15推挽输出
}
/**************************************************************************
Function: Initialize PWM to drive motor
Input   : arr：Auto reload value；psc：Prescaler coefficient
Output  : none
函数功能：初始化PWM，用于驱动电机 
入口参数：arr：自动重装值；psc：预分频系数
返回  值：无
**************************************************************************/
void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		 					 
	MiniBalance_Motor_Init();  //初始化电机控制所需IO
	RCC->APB2ENR|=1<<11;       //使能TIM1时钟    
	RCC->APB2ENR|=1<<2;        //PORTA时钟使能     
	GPIOA->CRH&=0XFFFF0FF0;    //PORTA8 11复用输出
	GPIOA->CRH|=0X0000B00B;    //PORTA8 11复用输出
	TIM1->ARR=arr;             //设定计数器自动重装值 
	TIM1->PSC=psc;             //预分频器不分频
	TIM1->CCMR2|=6<<12;        //CH4 PWM1模式	
	TIM1->CCMR1|=6<<4;         //CH1 PWM1模式	
	TIM1->CCMR2|=1<<11;        //CH4预装载使能	 
	TIM1->CCMR1|=1<<3;         //CH1预装载使能	  
	TIM1->CCER|=1<<12;         //CH4输出使能	   
	TIM1->CCER|=1<<0;          //CH1输出使能	
	TIM1->BDTR |= 1<<15;       //TIM1必须要这句话才能输出PWM
	TIM1->CR1 = 0x80;           //ARPE使能 
	TIM1->CR1|=0x01;          //使能定时器1 			
} 

