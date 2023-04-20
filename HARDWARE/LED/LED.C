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
#include "led.h"
/**************************************************************************
Function: Led initialization
Input   : none
Output  : none
函数功能： LED初始化
入口参数：无	
返回  值：无
**************************************************************************/
void LED_Init(void)
{
RCC->APB2ENR|=1<<2; 					//使能 PORTA 时钟  
GPIOA->CRL&=0XFFF00FFF;
GPIOA->CRL|=0X00033000;				//PA4 推挽输出
GPIOA->ODR|=1<<4; 						//PA4 输出高
}
/**************************************************************************
Function: Led flashing
Input   : time：Flicker frequency
Output  : none
函数功能：LED闪烁
入口参数：time	：闪烁频率
返回  值：无
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
	  if(0==time) LED=0;
	  else 	if(++temp==time)	LED=~LED,temp=0;
}
