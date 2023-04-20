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
#include "sys.h"
u8 Way_Angle=2;                             //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
u8 Flag_front,Flag_back,Flag_Left,Flag_Right,Flag_velocity=2; //����ң����صı���
u8 Flag_Stop=1,Flag_Show=0;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Motor_Left,Motor_Right;                 //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Temperature;                            //��ʾ�¶�
int Voltage;                                //��ص�ѹ������صı���
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
u32 Distance;                               //���������
u8 delay_50,delay_flag,PID_Send; 						//��ʱ�͵��εȱ���
u8 Flag_avoid=0,Flag_follow;								//����/�����־λ
float Acceleration_Z;                       //Z����ٶȼ�  
float Balance_Kp=22500,Balance_Kd=108,Velocity_Kp=16000,Velocity_Ki=80,Turn_Kp=4200,Turn_Kd=0;//PID����(�Ŵ�100��)
int main(void)
{ 
	Stm32_Clock_Init(9);            //ϵͳʱ������
	MY_NVIC_PriorityGroupConfig(2); //���ȼ�����
	delay_init(72);                 //��ʱ��ʼ��
	JTAG_Set(JTAG_SWD_DISABLE);     //�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //��SWD�ӿ� �������������SWD�ӿڵ���
	LED_Init();                     //��ʼ���� LED ���ӵ�Ӳ���ӿ�
	KEY_Init();                     //������ʼ��
	OLED_Init();                    //OLED��ʼ��
	uart_init(72,115200);           //��ʼ������1
  uart3_init(36,9600);            //����3��ʼ��
  MiniBalance_PWM_Init(7199,0);   //��ʼ��PWM 10KHZ������������� �����ʼ������ӿ� ��ΪMiniBalance_PWM_Init(9999,35) 200HZ
	Encoder_Init_TIM2();            //�������ӿ�
	Encoder_Init_TIM4();            //��ʼ��������2 
	Adc_Init();                     //adc��ʼ��
	IIC_Init();                     //ģ��IIC��ʼ��
  MPU6050_initialize();           //MPU6050��ʼ��	
  DMP_Init();                     //��ʼ��DMP     
	TIM3_Cap_Init(0XFFFF,72-1);	    //��������ʼ��
 	EXTI_Init();                    //MPU6050�ڲ� 5ms���ݾ����жϳ�ʼ��  ��Ϊ���ݲɼ�Ƶ����200HZ 
	while(1)
	{     
		if(Flag_Show==0)          	  //ʹ��MiniBalance APP��OLED��ʾ��
		{
				APP_Show();	
				oled_show();          		//��ʾ����
		}
		else                      	  //ʹ��MiniBalance��λ�� ��λ��ʹ�õ�ʱ����Ҫ�ϸ��ʱ�򣬹ʴ�ʱ�ر�app��ز��ֺ�OLED��ʾ��
		{
				DataScope();          	  //����MiniBalance��λ��
		}	
	  delay_flag=1;	
	  delay_50=0;
 	  while(delay_flag);	     			//ͨ��MPU6050��INT�ж�ʵ�ֵ�50ms��׼��ʱ			
	}					

}
