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
#ifndef __SHOW_H
#define __SHOW_H
#include "sys.h"
#define Encoder_to_Velocity 0.5397						//ÿ������ٺ���,����ֱ��Ϊ67mm��תһȦ���390�����壬�ı�Ƶ��Ϊ1560
extern float Velocity_Left,Velocity_Right;				//�����ٶȡ������ٶ�
void oled_show(void);
void APP_Show(void);
void DataScope(void);
#endif
