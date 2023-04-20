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
#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif

////////////////////////////////////////////////////////////////////////////////// 	 

static u8  fac_us=0;					//us��ʱ������			   
static u16 fac_ms=0;					//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

#ifdef OS_CRITICAL_METHOD 		//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
/**************************************************************************
Function: SYSTICK interrupts the service function for use with ucos
Input   : none
Output  : none
�������ܣ�systick�жϷ�����,ʹ��ucosʱ�õ�
��ڲ�������	
����  ֵ����
**************************************************************************/
void SysTick_Handler(void)
{				   
	  OSIntEnter();								//�����ж�
    OSTimeTick();       			//����ucos��ʱ�ӷ������               
    OSIntExit();        			//���������л����ж�
}
#endif
			   
/**************************************************************************
Function: Initialize the delay function
Input   : SYSCLK��System clock
Output  : none
�������ܣ���ʼ���ӳٺ���
��ڲ�����SYSCLK:ϵͳʱ��	
����  ֵ����
**************************************************************************/
//��ʹ��ucos��ʱ��,�˺������ʼ��ucos��ʱ�ӽ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
void delay_init(u8 SYSCLK)
{
#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
	u32 reload;
#endif
 	SysTick->CTRL&=~(1<<2);		//SYSTICKʹ���ⲿʱ��Դ	 
	fac_us=SYSCLK/8;					//�����Ƿ�ʹ��ucos,fac_us����Ҫʹ��
	    
#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
	reload=SYSCLK/8;					//ÿ���ӵļ������� ��λΪK	   
	reload*=1000000/OS_TICKS_PER_SEC;//����OS_TICKS_PER_SEC�趨���ʱ��
														//reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��1.86s����	
	fac_ms=1000/OS_TICKS_PER_SEC;//����ucos������ʱ�����ٵ�λ	   
	SysTick->CTRL|=1<<1;   		//����SYSTICK�ж�
	SysTick->LOAD=reload; 		//ÿ1/OS_TICKS_PER_SEC���ж�һ��	
	SysTick->CTRL|=1<<0;   		//����SYSTICK    
#else
	fac_ms=(u16)fac_us*1000;	//��ucos��,����ÿ��ms��Ҫ��systickʱ����   
#endif
}								    

#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
/**************************************************************************
Function: Delay function��us��
Input   : nus��The number of us to delay
Output  : none
�������ܣ���ʱ������us��
��ڲ�����nus��Ҫ��ʱ��us��	
����  ֵ����
**************************************************************************/
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;		//LOAD��ֵ	    	 
	ticks=nus*fac_us; 					//��Ҫ�Ľ�����	  		 
	tcnt=0;
	OSSchedLock();							//��ֹucos���ȣ���ֹ���us��ʱ
	told=SysTick->VAL;        	//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;		//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	};
	OSSchedUnlock();						//����ucos���� 									    
}
/**************************************************************************
Function: Delay function��ms��
Input   : mus��The number of ms to delay
Output  : none
�������ܣ���ʱ������us��
��ڲ�����mus��Ҫ��ʱ��ms��	
����  ֵ����
**************************************************************************/
void delay_ms(u16 nms)
{	
	if(OSRunning==OS_TRUE)			//���os�Ѿ�������	    
	{		  
		if(nms>=fac_ms)						//��ʱ��ʱ�����ucos������ʱ������ 
		{
   		OSTimeDly(nms/fac_ms);//ucos��ʱ
		}
		nms%=fac_ms;							//ucos�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
	}
	delay_us((u32)(nms*1000));	//��ͨ��ʽ��ʱ 
}
#else
//����ucosʱ
/**************************************************************************
Function: Delay function��us��
Input   : nus��The number of us to delay
Output  : none
�������ܣ���ʱ������us��
��ڲ�����nus��Ҫ��ʱ��us��	
����  ֵ����
**************************************************************************/		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL=0x01 ;      					//��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       					//�رռ�����
	SysTick->VAL =0X00;       					//��ռ�����	 
}
 
/**************************************************************************
Function: Delay function��ms��
Input   : mus��The number of ms to delay
Output  : none
�������ܣ���ʱ������us��
��ڲ�����mus��Ҫ��ʱ��ms��	
����  ֵ����
**************************************************************************/
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       					//�رռ�����
	SysTick->VAL =0X00;      						//��ռ�����	  	    
} 
#endif
			 




