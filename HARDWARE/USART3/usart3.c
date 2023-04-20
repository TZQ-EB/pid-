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
#include "usart3.h"
u8 Usart3_Receive;
/**************************************************************************
Function: Usart3 initialization
Input   : pclk2:PCLK2 clock frequency(MHz)�� bound:Baud rate
Output  : none
�������ܣ�����3��ʼ��
��ڲ�����pclk2:PCLK2 ʱ��Ƶ��(Mhz)�� bound:������
����  ֵ����
**************************************************************************/
void uart3_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<3;   //ʹ��PORTB��ʱ��  
	RCC->APB1ENR|=1<<18;  //ʹ�ܴ���ʱ�� 
	GPIOB->CRH&=0XFFFF00FF; 
	GPIOB->CRH|=0X00008B00;//IO״̬����
	GPIOB->ODR|=1<<10;	  
	RCC->APB1RSTR|=1<<18;   //��λ����1
	RCC->APB1RSTR&=~(1<<18);//ֹͣ��λ	   	   
	//����������
 	USART3->BRR=mantissa; // ����������	 
	USART3->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж�
	USART3->CR1|=1<<8;    //PE�ж�ʹ��
	USART3->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(0,1,USART3_IRQn,2);//��2
}
/**************************************************************************
Function: Receive interrupt function
Input   : none
Output  : none
�������ܣ�����3�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART3_IRQHandler(void)
{	
		if(USART3->SR&(1<<5))  //���յ�����
	  {	  
			static	int uart_receive=0;//����������ر���
			static u8 Flag_PID,i,j,Receive[50];
			static float Data;
			uart_receive=USART3->DR; 
			Usart3_Receive=uart_receive;

			if(uart_receive==0x59)  Flag_velocity=2;  //���ٵ���Ĭ��ֵ��
			if(uart_receive==0x58)  Flag_velocity=1;  //���ٵ�
			
			if(uart_receive>10)  //Ĭ��ʹ��
			{			//ascii�룬��Ӧapp�ϵ�A~H,Z
				if(uart_receive==0x5A)	Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=0;//ɲ��
				else if(uart_receive==0x41)	Flag_front=1,Flag_back=0,Flag_Left=0,Flag_Right=0;//ǰ
				else if(uart_receive==0x45)	Flag_front=0,Flag_back=1,Flag_Left=0,Flag_Right=0;//��
				else if(uart_receive==0x42||uart_receive==0x43||uart_receive==0x44)	
															Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=1;  //��
				else if(uart_receive==0x46||uart_receive==0x47||uart_receive==0x48)	    //��
															Flag_front=0,Flag_back=0,Flag_Left=1,Flag_Right=0;
				else Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=0;//ɲ��
			}
			if(uart_receive<10)     //����appΪ��MiniBalanceV1.0  ��ΪMiniBalanceV1.0��ң��ָ��ΪA~H ��HEX��С��10
			{			
				Flag_velocity=1;//�л������ٵ�
				if(uart_receive==0x00)	Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=0;//ɲ��
				else if(uart_receive==0x01)	Flag_front=1,Flag_back=0,Flag_Left=0,Flag_Right=0;//ǰ
				else if(uart_receive==0x05)	Flag_front=0,Flag_back=1,Flag_Left=0,Flag_Right=0;//��
				else if(uart_receive==0x02||uart_receive==0x03||uart_receive==0x04)	
															Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=1;  //��
				else if(uart_receive==0x06||uart_receive==0x07||uart_receive==0x08)	    //��
															Flag_front=0,Flag_back=0,Flag_Left=1,Flag_Right=0;
				else Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=0;//ɲ��
			}	
			if(Usart3_Receive==0x7B)  Flag_PID=1;   //APP����ָ����ʼλ
			if(Usart3_Receive==0x7D)  Flag_PID=2;   //APP����ָ��ֹͣλ

			 if(Flag_PID==1)  //�ɼ�����
			 {
				 Receive[i]=Usart3_Receive;
				 i++;
			 }
			 if(Flag_PID==2)  //��������
			 {
					if(Receive[3]==0x50) 	 PID_Send=1;
					else  if(Receive[1]!=0x23) 
					{								
						for(j=i;j>=4;j--)
						{
							Data+=(Receive[j-1]-48)*pow(10,i-j);
						}
						switch(Receive[1])
						{
							case 0x30:  Balance_Kp=Data;break;
							case 0x31:  Balance_Kd=Data;break;
							case 0x32:  Velocity_Kp=Data;break;
							case 0x33:  Velocity_Ki=Data;break;
							case 0x34:  Turn_Kp=Data;break; 
							case 0x35:  Turn_Kd=Data;break; 
							case 0x36:  break; //Ԥ��
							case 0x37:  break; //Ԥ��
							case 0x38:  break; //Ԥ��
						}
				  }				 
					Flag_PID=0;
					i=0;
					j=0;
					Data=0;
					memset(Receive, 0, sizeof(u8)*50);//��������
			 } 
	 }  											 
} 

