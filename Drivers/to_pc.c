/***********************************************

	Flyex  < 2017-8-9 >

************************************************/
#include "includes.h"

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
	
u8 data_to_send[33];

void Send_Status(float roll,float pitch,float yaw)
{
	u8 _cnt = 0;
	u8 sum = 0;
	u8 i;
  volatile short int  _temp;

  data_to_send[_cnt++] = 0xAA;
  data_to_send[_cnt++] = 0xAA;
  data_to_send[_cnt++] = 0x01;
  data_to_send[_cnt++] = 12;

  _temp = (int)(roll * 100);
  data_to_send[_cnt++] = BYTE1(_temp);
  data_to_send[_cnt++] = BYTE0(_temp);
  _temp = (int)(pitch * 100);
  data_to_send[_cnt++] = BYTE1(_temp);
  data_to_send[_cnt++] = BYTE0(_temp);
  _temp =(int)( yaw * 100);
  data_to_send[_cnt++] = BYTE1(_temp);
  data_to_send[_cnt++] = BYTE0(_temp);

  _temp = 0 ;
  data_to_send[_cnt++] = BYTE3(_temp);
  data_to_send[_cnt++] = BYTE2(_temp);
  data_to_send[_cnt++] = BYTE1(_temp);
  data_to_send[_cnt++] = BYTE0(_temp);
  _temp = 0;
  data_to_send[_cnt++] = BYTE0(_temp);
  _temp = 0;
  data_to_send[_cnt++] = BYTE0(_temp);

  // data_to_send[3] = _cnt - 4;
 //    u8 sum = 0;
 
  for ( i = 0; i < _cnt; i++)
    sum += data_to_send[i];
  data_to_send[_cnt++] = sum;

  USART1_sendData(data_to_send, _cnt);

}
