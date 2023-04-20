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
#ifndef __SHOW_H
#define __SHOW_H
#include "sys.h"
#define Encoder_to_Velocity 0.5397						//每脉冲多少毫米,车轮直径为67mm，转一圈输出390个脉冲，四倍频后为1560
extern float Velocity_Left,Velocity_Right;				//左轮速度、右轮速度
void oled_show(void);
void APP_Show(void);
void DataScope(void);
#endif
