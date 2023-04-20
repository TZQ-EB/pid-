/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��
�޸�ʱ�䣺2021-04-29

 
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:
Update��2021-04-29

All rights reserved
***********************************************/
#include "DataScope_DP.h"
unsigned char DataScope_OutPut_Buffer[42] = {0};	   //���ڷ��ͻ�����
/**************************************************************************
Function: Convert single precision floating-point data into 4-byte data and store it in the specified address
Input   : target:Target single precision data  buf:Array to be written  beg:Specifies which element of the array to write from
Output  : none
�������ܣ��������ȸ�������ת��4�ֽ����ݲ�����ָ����ַ  ����˵�����û�����ֱ�Ӳ����˺���
��ڲ�����target:Ŀ�굥��������  buf:��д������  beg:ָ��������ڼ���Ԫ�ؿ�ʼд��
����  ֵ����
**************************************************************************/
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;	  //�õ�float�ĵ�ַ
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}
/**************************************************************************
Function: Write the single precision floating-point data of the channel to be sent to the send buffer
Input   : Data��Channel data  Channel��Select channel (1-10)
Output  : none
�������ܣ���������ͨ���ĵ����ȸ�������д�뷢�ͻ�����
��ڲ�����Data��ͨ������  Channel��ѡ��ͨ����1-10��
����  ֵ����
**************************************************************************/
void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
{
	if ( (Channel > 10) || (Channel == 0) ) return;  //ͨ����������10�����0��ֱ����������ִ�к���
  else
  {
     switch (Channel)
		{
      case 1:  Float2Byte(&Data,DataScope_OutPut_Buffer,1); break;
      case 2:  Float2Byte(&Data,DataScope_OutPut_Buffer,5); break;
		  case 3:  Float2Byte(&Data,DataScope_OutPut_Buffer,9); break;
		  case 4:  Float2Byte(&Data,DataScope_OutPut_Buffer,13); break;
		  case 5:  Float2Byte(&Data,DataScope_OutPut_Buffer,17); break;
		  case 6:  Float2Byte(&Data,DataScope_OutPut_Buffer,21); break;
		  case 7:  Float2Byte(&Data,DataScope_OutPut_Buffer,25); break;
		  case 8:  Float2Byte(&Data,DataScope_OutPut_Buffer,29); break;
		  case 9:  Float2Byte(&Data,DataScope_OutPut_Buffer,33); break;
		  case 10: Float2Byte(&Data,DataScope_OutPut_Buffer,37); break;
		}
  }	 
}
/**************************************************************************
Function: Generate frame format that datascope v1.0 can recognize correctly
Input   : Channel_Number��Number of channels to send
Output  : Returns the number of send buffer data
�������ܣ����� DataScopeV1.0 ����ȷʶ���֡��ʽ
��ڲ�����Channel_Number����Ҫ���͵�ͨ������
����  ֵ�����ط��ͻ��������ݸ���   ����0��ʾ֡��ʽ����ʧ��
**************************************************************************/
unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
{
	if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //ͨ����������10�����0��ֱ����������ִ�к���
  else
  {	
		DataScope_OutPut_Buffer[0] = '$';  //֡ͷ
		
	  switch(Channel_Number)   
    { 
		  case 1:   DataScope_OutPut_Buffer[5]  =  5; return  6;  
		  case 2:   DataScope_OutPut_Buffer[9]  =  9; return 10;
		  case 3:   DataScope_OutPut_Buffer[13] = 13; return 14; 
		  case 4:   DataScope_OutPut_Buffer[17] = 17; return 18;
		  case 5:   DataScope_OutPut_Buffer[21] = 21; return 22;  
		  case 6:   DataScope_OutPut_Buffer[25] = 25; return 26;
		  case 7:   DataScope_OutPut_Buffer[29] = 29; return 30; 
		  case 8:   DataScope_OutPut_Buffer[33] = 33; return 34; 
		  case 9:   DataScope_OutPut_Buffer[37] = 37; return 38;
      case 10:  DataScope_OutPut_Buffer[41] = 41; return 42; 
    }	 
  }
	return 0;
}










