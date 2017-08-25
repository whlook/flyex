/***********************************************

	Fly2017  < 2017-1-13 >
	MPU9250 驱动程序 库函数版本

************************************************/
#include "includes.h"


MPU9250_read_data_t mpu_data;

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
static short int GetData(unsigned char slave_address,unsigned char REG_Address)
{
	short int H,L;
	
	H=I2C1_ByteRead_Reg(slave_address,REG_Address);
	L=I2C1_ByteRead_Reg(slave_address,REG_Address+1);
	
	return ((H<<8)+L);
	
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
static short int GetData_L(unsigned char slave_address,unsigned char REG_Address)
{
	short int H,L;
	
	L=I2C1_ByteRead_Reg(slave_address,REG_Address);
	H=I2C1_ByteRead_Reg(slave_address,REG_Address+1);
	
	return ((H<<8)+L);
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
void MPU9250_init(void)
{

	I2C1_ByteWrite_Reg(0xd0,MPU6500_PWR_MGMT_1,0x00);  		 // wake up mpu6500
	delay_ms_soft(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_SMPLRT_DIV,0x07);      // 1000/(7+1) = 125Hz
	delay_ms_soft(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_CONFIG,0x06);          // gyro low pass 5Hz
	delay_ms_soft(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_GYRO_CONFIG,0x18);     // +-2000 dps
	delay_ms_soft(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_ACCEL_CONFIG,0x10);    // +-8g
	delay_ms_soft(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_ACCEL_CONFIG_2,0x06);  // acc low pass 5Hz
	delay_ms_soft(10);
//+----------------------------------------------------+
	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x00);       //  disable master , if open ,0x20
	delay_ms_soft(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x02);     // open passby
	delay_ms_soft(10);
//+----------------------+
	I2C1_ByteWrite_Reg(0x18,0x0a,0x06);                    // open ak's read
	delay_ms_soft(10);
//+----------------------+
	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x20);       //
	delay_ms_soft(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x00);     //
	delay_ms_soft(10);
	
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/

#define CONSTANTS_ONE_G			  9.7950f		/* m/s^2 */
#define PI                    3.141592654
#define SENSOR_MAX_G          8.0f        // g
#define SENSOR_MAX_W          2000.0f     // deg/s
#define ACC_SCALE             (SENSOR_MAX_G/32768.0f)  // turn to g
#define GYRO_SCALE            (SENSOR_MAX_W/32768.0f)  // turn to deg

void   MPU9250_get_data(void)
{
	
	/****  raw data  ****/
	mpu_data.acc_x = GetData(0xd0,MPU6500_ACCEL_XOUT_H);
	mpu_data.acc_y = GetData(0xd0,MPU6500_ACCEL_YOUT_H);
	mpu_data.acc_z = GetData(0xd0,MPU6500_ACCEL_ZOUT_H);
	
	mpu_data.gyro_x = GetData(0xd0,MPU6500_GYRO_XOUT_H);
	mpu_data.gyro_y = GetData(0xd0,MPU6500_GYRO_YOUT_H);
	mpu_data.gyro_z = GetData(0xd0,MPU6500_GYRO_ZOUT_H);
	
	mpu_data.temperature = GetData(0xd0,MPU6500_TEMP_OUT_H);
	
	/****  turn to physical  ****/
	mpu_data.acc_x = (float)mpu_data.acc_x*ACC_SCALE*CONSTANTS_ONE_G;  //g  
	mpu_data.acc_y = (float)mpu_data.acc_y*ACC_SCALE*CONSTANTS_ONE_G;
	mpu_data.acc_z = (float)mpu_data.acc_z*ACC_SCALE*CONSTANTS_ONE_G;
	
	
	mpu_data.gyro_x = (float)mpu_data.gyro_x*GYRO_SCALE*180.f/PI;      // deg/s   
	mpu_data.gyro_y = (float)mpu_data.gyro_y*GYRO_SCALE*180.f/PI;
	mpu_data.gyro_z = (float)mpu_data.gyro_z*GYRO_SCALE*180.f/PI;
	
	mpu_data.temperature = (float)mpu_data.temperature/340 + 36.53;    // ℃
	
	

//	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x00); //  disable master , if open ,0x20
//	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x02); // open passby
//			
//	temp.mag_x = GetData_L(0x18,AK8963_HXL);
//	temp.mag_y = GetData_L(0x18,AK8963_HYL);
//  temp.mag_z = GetData_L(0x18,AK8963_HZL);			
//	
//	I2C1_ByteRead_Reg(0x18,0x09);  // read st2 to finish reading mag, only after this ,data can be reflush!!!!
//			
//	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x20);
//	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x00);
	
}


