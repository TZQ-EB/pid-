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
#include "sys.h"
u8 Way_Angle=2;                             //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波 
u8 Flag_front,Flag_back,Flag_Left,Flag_Right,Flag_velocity=2; //蓝牙遥控相关的变量
u8 Flag_Stop=1,Flag_Show=0;                 //停止标志位和 显示标志位 默认停止 显示打开
int Motor_Left,Motor_Right;                 //电机PWM变量 应是Motor的 向Moto致敬	
int Temperature;                            //显示温度
int Voltage;                                //电池电压采样相关的变量
float Angle_Balance,Gyro_Balance,Gyro_Turn; //平衡倾角 平衡陀螺仪 转向陀螺仪
u32 Distance;                               //超声波测距
u8 delay_50,delay_flag,PID_Send; 						//延时和调参等变量
u8 Flag_avoid=0,Flag_follow;								//避障/跟随标志位
float Acceleration_Z;                       //Z轴加速度计  
float Balance_Kp=22500,Balance_Kd=108,Velocity_Kp=16000,Velocity_Ki=80,Turn_Kp=4200,Turn_Kd=0;//PID参数(放大100倍)
int main(void)
{ 
	Stm32_Clock_Init(9);            //系统时钟设置
	MY_NVIC_PriorityGroupConfig(2); //优先级设置
	delay_init(72);                 //延时初始化
	JTAG_Set(JTAG_SWD_DISABLE);     //关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //打开SWD接口 可以利用主板的SWD接口调试
	LED_Init();                     //初始化与 LED 连接的硬件接口
	KEY_Init();                     //按键初始化
	OLED_Init();                    //OLED初始化
	uart_init(72,115200);           //初始化串口1
  uart3_init(36,9600);            //串口3初始化
  MiniBalance_PWM_Init(7199,0);   //初始化PWM 10KHZ，用于驱动电机 如需初始化电调接口 改为MiniBalance_PWM_Init(9999,35) 200HZ
	Encoder_Init_TIM2();            //编码器接口
	Encoder_Init_TIM4();            //初始化编码器2 
	Adc_Init();                     //adc初始化
	IIC_Init();                     //模拟IIC初始化
  MPU6050_initialize();           //MPU6050初始化	
  DMP_Init();                     //初始化DMP     
	TIM3_Cap_Init(0XFFFF,72-1);	    //超声波初始化
 	EXTI_Init();                    //MPU6050内部 5ms数据就绪中断初始化  因为数据采集频率是200HZ 
	while(1)
	{     
		if(Flag_Show==0)          	  //使用MiniBalance APP和OLED显示屏
		{
				APP_Show();	
				oled_show();          		//显示屏打开
		}
		else                      	  //使用MiniBalance上位机 上位机使用的时候需要严格的时序，故此时关闭app监控部分和OLED显示屏
		{
				DataScope();          	  //开启MiniBalance上位机
		}	
	  delay_flag=1;	
	  delay_50=0;
 	  while(delay_flag);	     			//通过MPU6050的INT中断实现的50ms精准延时			
	}					

}
