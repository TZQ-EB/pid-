/***********************************************
公司：轮趣科技（东莞）有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com 
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：
修改时间：2021-04-29

 
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:
Update：2021-04-29

All rights reserved
***********************************************/
#include "exti.h"
/**************************************************************************
Function: External interrupt initialization
Input   : none
Output  : none
函数功能：外部中断初始化
入口参数：无
返回  值：无 
**************************************************************************/
void EXTI_Init(void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟	   	 
	GPIOA->CRH&=0XFFF0FFFF; 
	GPIOA->CRH|=0X00080000;//PA12上拉输入
  GPIOA->ODR|=1<<12;     //PA12上拉	
	Ex_NVIC_Config(GPIO_A,12,FTIR);		//下降沿触发
	MY_NVIC_Init(2,1,EXTI15_10_IRQn,2);  	//抢占2，子优先级1，组2
}










