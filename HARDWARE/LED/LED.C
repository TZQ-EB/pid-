/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��5.7
�޸�ʱ�䣺2021-04-29

 
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:5.7
Update��2021-04-29

All rights reserved
***********************************************/
#include "led.h"
/**************************************************************************
Function: Led initialization
Input   : none
Output  : none
�������ܣ� LED��ʼ��
��ڲ�������	
����  ֵ����
**************************************************************************/
void LED_Init(void)
{
RCC->APB2ENR|=1<<2; 					//ʹ�� PORTA ʱ��  
GPIOA->CRL&=0XFFF00FFF;
GPIOA->CRL|=0X00033000;				//PA4 �������
GPIOA->ODR|=1<<4; 						//PA4 �����
}
/**************************************************************************
Function: Led flashing
Input   : time��Flicker frequency
Output  : none
�������ܣ�LED��˸
��ڲ�����time	����˸Ƶ��
����  ֵ����
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
	  if(0==time) LED=0;
	  else 	if(++temp==time)	LED=~LED,temp=0;
}