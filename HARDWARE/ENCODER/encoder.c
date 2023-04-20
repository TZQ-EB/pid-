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
#include "encoder.h"

/**************************************************************************
Function: Initialize TIM2 to encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM2��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM2(void)
{
	RCC->APB1ENR|=1<<0;     //TIM2ʱ��ʹ��
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
	GPIOA->CRL&=0XFFFFFF00;//PA0 PA1
	GPIOA->CRL|=0X00000044;//��������
	TIM2->DIER|=1<<0;   //���������ж�				
	TIM2->DIER|=1<<6;   //���������ж�
	MY_NVIC_Init(1,3,TIM2_IRQn,1);
	TIM2->PSC = 0x0;//Ԥ��Ƶ��
	TIM2->ARR = ENCODER_TIM_PERIOD;//�趨�������Զ���װֵ 
	TIM2->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM2->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
		
	TIM2->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
	TIM2->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
	TIM2->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM2->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
	TIM2->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
	TIM2->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
	TIM2->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
}
/**************************************************************************
Function: Initialize TIM4 to encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM4(void)
{
	RCC->APB1ENR|=1<<2;     //TIM4ʱ��ʹ��
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��
	GPIOB->CRL&=0X00FFFFFF; //PB6 PB7
	GPIOB->CRL|=0X44000000; //��������
	TIM4->DIER|=1<<0;   //���������ж�				
	TIM4->DIER|=1<<6;   //���������ж�
	MY_NVIC_Init(1,3,TIM4_IRQn,1);
	TIM4->PSC = 0x0;//Ԥ��Ƶ��
	TIM4->ARR = ENCODER_TIM_PERIOD;//�趨�������Զ���װֵ 
	TIM4->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM4->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
		
	TIM4->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
	TIM4->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
	TIM4->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM4->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
	TIM4->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
	TIM4->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
	TIM4->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
}
/**************************************************************************
Function: Read encoder count per unit time
Input   : TIMX��Timer
Output  : none
�������ܣ���λʱ���ȡ����������
��ڲ�����TIMX����ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
/**************************************************************************
Function: TIM4 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM4�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}
/**************************************************************************
Function: TIM2 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM2�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}
