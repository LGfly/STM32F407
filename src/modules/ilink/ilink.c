#include "ilink.h"
#include "inf_typedef.h"

//extern volatile S_INT16_XYZ MPU6500_Acc;
//extern volatile S_INT16_XYZ MPU6500_Gyro;
//extern volatile S_FLOAT_XYZ Angle;  						//Angle of pilot
//extern volatile float mpu6500_tempreature;
//extern vs32 ultrasonic_height;

//extern volatile S_FLOAT_XYZ Position;    				//Position of pilot
//extern volatile S_FLOAT_XYZ Velocity;    				//Velocity of pilot
//extern volatile S_FLOAT_XYZ Acceleration;    		//Acceleration of pilot

//extern u8 rc_id;																//RC ID	
//extern u16 Rc_Channel_Val[14];									//RC channel value

//extern volatile u16 motor[5];										//motor pwm

//extern u32 system_time;													//Unit:ms
//extern float battery_voltage;										//Battery voltage
//float battery_current;										//Battery current

/*
 * Function Name:Anchor_Data_Frame
 * Description	:Information of location
 * Input  			:None
 * Output  			:Data frame
 */
u8 * Anchor_Data_Frame(float dis[])
{
	static u8 data_frame[DATA_FRAME_LENGTH_24];				//Define data frame
	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
	u8 data_frame_sum = 0x00;
	int i = 0;

	static s16 dis0,dis1,dis2,dis3;
	dis0=(s16)(dis[0] * 100);
	dis1=(s16)(dis[1] * 100);
	dis2=(s16)(dis[2] * 100);
	dis3=(s16)(dis[3] * 100);
	
	data_frame[0] = 0x55;  //Frame Header
	data_frame[1] = 0x08;	 //Function Mark
	
	data_frame[2] = BYTE1(dis0);
	data_frame[3] = BYTE0(dis0);
	data_frame[4] = BYTE1(dis1);
	data_frame[5] = BYTE0(dis1);
	data_frame[6] = BYTE1(dis2);
	data_frame[7] = BYTE0(dis2);
	
	data_frame[8] = BYTE1(dis3);
	data_frame[9] = BYTE0(dis3);
//	data_frame[10] = BYTE1(Velocity_.Y);
//	data_frame[11] = BYTE0(Velocity_.Y);
//	data_frame[12] = BYTE1(Velocity_.Z);
//  data_frame[13] = BYTE0(Velocity_.Z);

//	data_frame[14] = BYTE1(Position_.X);
//	data_frame[15] = BYTE0(Position_.X);
//	data_frame[16] = BYTE1(Position_.Y);
//	data_frame[17] = BYTE0(Position_.Y);
//	data_frame[18] = BYTE1(Position_.Z);
//  data_frame[19] = BYTE0(Position_.Z);
	
	for(i = 0;i < (data_frame_length - 1);i++)
	{
		data_frame_sum+= data_frame[i];//Sum check
  }
	data_frame[data_frame_length - 1] = data_frame_sum;
	
	return data_frame;
}


extern double tag_position[3];

/*
 * Function Name:I_UWB_LPS_Data_Frame
 * Description	:tag position
 * Input  			:None
 * Output  			:Data frame
 */
u8 * I_UWB_LPS_Data_Frame(u16 id,double position[3],float velocity[3])
{
	static S_INT32_XYZ tag_position,tag_velocity;
	static u8 data_frame[DATA_FRAME_LENGTH_32];				//Define data frame
	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
	u8 data_frame_sum = 0x00;
	u8 i = 0;

	tag_position.x = (s16)(position[0] * 1000);
	tag_position.y = (s16)(position[1] * 1000);
	tag_position.z = (s16)(position[2] * 1000);
	
	tag_velocity.x = (s16)(velocity[0] * 10000);
	tag_velocity.y = (s16)(velocity[1] * 10000);
	tag_velocity.z = (s16)(velocity[2] * 10000);
	
	data_frame[0] = 0x55;  //Frame Header
	data_frame[1] = 0x08;	 //Function Mark

	data_frame[2] = id;
	data_frame[3] = 0x00;
	
	data_frame[4] = BYTE2(tag_position.x);
	data_frame[5] = BYTE1(tag_position.x);
	data_frame[6] = BYTE0(tag_position.x);
	data_frame[7] = BYTE2(tag_position.y);
	data_frame[8] = BYTE1(tag_position.y);
	data_frame[9] = BYTE0(tag_position.y);
	data_frame[10] = BYTE2(tag_position.z);
	data_frame[11] = BYTE1(tag_position.z);
	data_frame[12] = BYTE0(tag_position.z);	

	data_frame[13] = BYTE2(tag_velocity.x);
	data_frame[14] = BYTE1(tag_velocity.x);
	data_frame[15] = BYTE0(tag_velocity.x);
	data_frame[16] = BYTE2(tag_velocity.y);
	data_frame[17] = BYTE1(tag_velocity.y);
	data_frame[18] = BYTE0(tag_velocity.y);
	data_frame[19] = BYTE2(tag_velocity.z);
	data_frame[20] = BYTE1(tag_velocity.z);
	data_frame[21] = BYTE0(tag_velocity.z);

	for(i = 0;i < (data_frame_length - 1);i++)
	{
		data_frame_sum+= data_frame[i];//Sum check
  }
	data_frame[data_frame_length - 1] = data_frame_sum;

	return data_frame;
}



/*
 * Function Name:I_UWB_AM_Data_Frame
 * Description	:tag position
 * Input  			:None
 * Output  			:Data frame
 */
u8 * I_UWB_AM_PC_Frame(u8 data_frame[128])
{
	static u16 data_frame_length = 128;//Get data frame length,define static to avoid everytime bliud sizeof() function
	u8 data_frame_sum = 0x00;
	u8 i = 0;

	data_frame[0] = 0x55;  //Frame Header
	data_frame[1] = 0x09;	 //Function Mark

	for(i = 0;i < (data_frame_length - 1);i++)
	{
		data_frame_sum+= data_frame[i];//Sum check
  }
	data_frame[data_frame_length - 1] = data_frame_sum;

	return data_frame;
}

///*
// * Function Name:Version_Data_Frame
// * Description	:Information of pilot version
// * Input  			:None
// * Output  			:Data frame
// */
//u8 * Version_Data_Frame(void)
//{
//	static u8 data_frame[DATA_FRAME_LENGTH_24];				//Define data frame
//	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
//	u8 data_frame_sum = 0x00;
//	int i = 0;

//	data_frame[0] = 0x55;  //Frame Header
//	data_frame[1] = 0x00;	 //Function Mark

//	for(i = 0;i < (data_frame_length - 1);i++)
//	{
//		data_frame_sum+= data_frame[i];//Sum check
//  }
//	data_frame[data_frame_length - 1] = data_frame_sum;
//	
//	return data_frame;
//}

#include "bsp\mpu6500\mpu6500.h"
#include "bsp\ak8975\ak8975.h"
#include "modules\ahrs\ahrs_init.h"

/*
 * Function Name:AHRS_Data_Frame
 * Description	:Information of ahrs
 * Input  			:None
 * Output  			:Data frame
 */
u8 * AHRS_Data_Frame(void)
{
	static u8 data_frame[DATA_FRAME_LENGTH_32];				//Define data frame
//	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
//	u8 data_frame_sum = 0x00;
//	int i = 0;

//	S_INT16_XYZ Angle_;
//  s16 mpu6500_tempreature_;
//	
//	Angle_.x=(s16)(ahrs_param.angle.x * 100);
//	Angle_.y=(s16)(ahrs_param.angle.y * 100);
//	Angle_.z=(s16)(ahrs_param.angle.z * 100);
//	
////	mpu6500_tempreature_ = (s16)(mpu6500_tempreature * 100);
//	
//	data_frame[0] = 0x55;  //Frame Header
//	data_frame[1] = 0x01;	 //Function Mark
//	
//	data_frame[2] = BYTE1(mpu6500_param.gyro.x);
//	data_frame[3] = BYTE0(mpu6500_param.gyro.x);
//	data_frame[4] = BYTE1(mpu6500_param.gyro.y);
//	data_frame[5] = BYTE0(mpu6500_param.gyro.y);
//	data_frame[6] = BYTE1(mpu6500_param.gyro.z);
//	data_frame[7] = BYTE0(mpu6500_param.gyro.z);
//	
//	data_frame[8] = BYTE1(mpu6500_param.acc.x);
//	data_frame[9] = BYTE0(mpu6500_param.acc.x);
//	data_frame[10] = BYTE1(mpu6500_param.acc.y);
//	data_frame[11] = BYTE0(mpu6500_param.acc.y);
//	data_frame[12] = BYTE1(mpu6500_param.acc.z);
//  data_frame[13] = BYTE0(mpu6500_param.acc.z);

//	data_frame[14] = BYTE1(ak8975_param.mag.x);
//	data_frame[15] = BYTE0(ak8975_param.mag.x);
//	data_frame[16] = BYTE1(ak8975_param.mag.y);
//	data_frame[17] = BYTE0(ak8975_param.mag.y);
//	data_frame[18] = BYTE1(ak8975_param.mag.z);
//  data_frame[19] = BYTE0(ak8975_param.mag.z);
//	
//	data_frame[20] = BYTE1(Angle_.x);
//	data_frame[21] = BYTE0(Angle_.x);
//	data_frame[22] = BYTE1(Angle_.y);
//	data_frame[23] = BYTE0(Angle_.y);
//	data_frame[24] = BYTE1(Angle_.z);
//  data_frame[25] = BYTE0(Angle_.z);
//	
////	data_frame[26] = BYTE1(mpu6500_tempreature_);
////	data_frame[27] = BYTE0(mpu6500_tempreature_);
//	
//	for(i = 0;i < (data_frame_length - 1);i++)
//	{
//		data_frame_sum+= data_frame[i];//Sum check
//  }
//	data_frame[data_frame_length - 1] = data_frame_sum;
//	
	return data_frame;
}


///*
// * Function Name:Location_Data_Frame
// * Description	:Information of location
// * Input  			:None
// * Output  			:Data frame
// */
//u8 * Location_Data_Frame(void)
//{
//	static u8 data_frame[DATA_FRAME_LENGTH_24];				//Define data frame
//	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
//	u8 data_frame_sum = 0x00;
//	int i = 0;

//	S_INT16_XYZ Acceleration_;
//	S_INT16_XYZ Velocity_;
//	S_INT16_XYZ Position_;
//	
//	Acceleration_.X = (s16)(Acceleration.X * 1000);
//	Acceleration_.Y = (s16)(Acceleration.Y * 1000);
//	Acceleration_.Z = (s16)(Acceleration.Z * 1000);
//	
//	Velocity_.X = (s16)(Velocity.X * 1000);
//	Velocity_.Y = (s16)(Velocity.Y * 1000);
//	Velocity_.Z = (s16)(Velocity.Z * 1000);
//	
//	Position_.X = (s16)(Position.X * 1000);
//	Position_.Y = (s16)(Position.Y * 1000);
//	Position_.Z = (s16)(ultrasonic_height);//ultrasonic_height unit is mm
//	
//	data_frame[0] = 0x55;  //Frame Header
//	data_frame[1] = 0x02;	 //Function Mark
//	
//	data_frame[2] = BYTE1(Acceleration_.X);
//	data_frame[3] = BYTE0(Acceleration_.X);
//	data_frame[4] = BYTE1(Acceleration_.Y);
//	data_frame[5] = BYTE0(Acceleration_.Y);
//	data_frame[6] = BYTE1(Acceleration_.Z);
//	data_frame[7] = BYTE0(Acceleration_.Z);
//	
//	data_frame[8] = BYTE1(Velocity_.X);
//	data_frame[9] = BYTE0(Velocity_.X);
//	data_frame[10] = BYTE1(Velocity_.Y);
//	data_frame[11] = BYTE0(Velocity_.Y);
//	data_frame[12] = BYTE1(Velocity_.Z);
//  data_frame[13] = BYTE0(Velocity_.Z);

//	data_frame[14] = BYTE1(Position_.X);
//	data_frame[15] = BYTE0(Position_.X);
//	data_frame[16] = BYTE1(Position_.Y);
//	data_frame[17] = BYTE0(Position_.Y);
//	data_frame[18] = BYTE1(Position_.Z);
//  data_frame[19] = BYTE0(Position_.Z);
//	
//	for(i = 0;i < (data_frame_length - 1);i++)
//	{
//		data_frame_sum+= data_frame[i];//Sum check
//  }
//	data_frame[data_frame_length - 1] = data_frame_sum;
//	
//	return data_frame;
//}


///*
// * Function Name:Receiver_Data_Frame
// * Description	:Information of Receiver
// * Input  			:None
// * Output  			:Data frame
// */
//u8 * Receiver_Data_Frame(void)
//{
//	static u8 data_frame[DATA_FRAME_LENGTH_32];				//Define data frame
//	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
//	u8 data_frame_sum = 0x00;
//	int i = 0;

//	data_frame[0] = 0x55;  //Frame Header
//	data_frame[1] = 0x03;	 //Function Mark
//	
//	data_frame[2] = rc_id; //Only on RC,on pilot is none,default value:0
//	
//	data_frame[3] = BYTE1(Rc_Channel_Val[0]);
//	data_frame[4] = BYTE0(Rc_Channel_Val[0]);
//	data_frame[5] = BYTE1(Rc_Channel_Val[1]);
//	data_frame[6] = BYTE0(Rc_Channel_Val[1]);
//	data_frame[7] = BYTE1(Rc_Channel_Val[2]);
//	data_frame[8] = BYTE0(Rc_Channel_Val[2]);
//	data_frame[9] = BYTE1(Rc_Channel_Val[3]);
//	data_frame[10] = BYTE0(Rc_Channel_Val[3]);
//	data_frame[11] = BYTE1(Rc_Channel_Val[4]);
//	data_frame[12] = BYTE0(Rc_Channel_Val[4]);	
//	data_frame[13] = BYTE1(Rc_Channel_Val[5]);
//	data_frame[14] = BYTE0(Rc_Channel_Val[5]);
//	data_frame[15] = BYTE1(Rc_Channel_Val[6]);
//	data_frame[16] = BYTE0(Rc_Channel_Val[6]);
//	data_frame[17] = BYTE1(Rc_Channel_Val[7]);
//	data_frame[18] = BYTE0(Rc_Channel_Val[7]);
//	data_frame[19] = BYTE1(Rc_Channel_Val[8]);
//	data_frame[20] = BYTE0(Rc_Channel_Val[8]);
//	data_frame[21] = BYTE1(Rc_Channel_Val[9]);
//	data_frame[22] = BYTE0(Rc_Channel_Val[9]);
//	data_frame[23] = BYTE1(Rc_Channel_Val[10]);
//	data_frame[24] = BYTE0(Rc_Channel_Val[10]);	
//	data_frame[25] = BYTE1(Rc_Channel_Val[11]);
//	data_frame[26] = BYTE0(Rc_Channel_Val[11]);
//	data_frame[27] = BYTE1(Rc_Channel_Val[12]);
//	data_frame[28] = BYTE0(Rc_Channel_Val[12]);
//	data_frame[29] = BYTE1(Rc_Channel_Val[13]);
//	data_frame[30] = BYTE0(Rc_Channel_Val[13]);
//	
//	for(i = 0;i < (data_frame_length - 1);i++)
//	{
//		data_frame_sum+= data_frame[i];//Sum check
//  }
//	data_frame[data_frame_length - 1] = data_frame_sum;
//	
//	return data_frame;
//}

///*
// * Function Name:Motor_Data_Frame
// * Description	:Information of location
// * Input  			:None
// * Output  			:Data frame
// */
//u8 * Motor_Data_Frame(void)
//{
//	static u8 data_frame[DATA_FRAME_LENGTH_24];				//Define data frame
//	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
//	u8 data_frame_sum = 0x00;
//	int i = 0;

//	data_frame[0] = 0x55;  //Frame Header
//	data_frame[1] = 0x04;	 //Function Mark
//	
//	data_frame[2] = BYTE1(motor[1]);
//	data_frame[3] = BYTE0(motor[1]);
//	data_frame[4] = BYTE1(motor[2]);
//	data_frame[5] = BYTE0(motor[2]);
//	data_frame[6] = BYTE1(motor[3]);
//	data_frame[7] = BYTE0(motor[3]);
//	data_frame[8] = BYTE1(motor[4]);
//	data_frame[9] = BYTE0(motor[4]);
//	
////	data_frame[10] = BYTE1(motor[5]);
////	data_frame[11] = BYTE0(motor[5]);
////	data_frame[12] = BYTE1(motor[6]);
////  data_frame[13] = BYTE0(motor[6]);
////	data_frame[14] = BYTE1(motor[7]);
////	data_frame[15] = BYTE0(motor[7]);
////	data_frame[16] = BYTE1(motor[8]);
////	data_frame[17] = BYTE0(motor[8]);

//	for(i = 0;i < (data_frame_length - 1);i++)
//	{
//		data_frame_sum += data_frame[i];//Sum check
//  }
//	data_frame[data_frame_length - 1] = data_frame_sum;
//	
//	return data_frame;
//}

///*
// * Function Name:Rest_Data_Frame
// * Description	:Rest information of pilot
// * Input  			:None
// * Output  			:Data frame
// */
//u8 * Rest_Data_Frame(void)
//{
//	static u8 data_frame[DATA_FRAME_LENGTH_24];				//Define data frame
//	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
//	u8 data_frame_sum = 0x00;
//	int i = 0;
//	
//  s16 battery_voltage_,battery_current_;

//	battery_voltage_ = (s16)(battery_voltage * 1000);
//	battery_current_ = (s16)(battery_current * 1000);
//	
//	data_frame[0] = 0x55;  //Frame Header
//	data_frame[1] = 0x05;	 //Function Mark
//	
//	data_frame[2] = BYTE3(system_time);
//	data_frame[3] = BYTE2(system_time);
//	data_frame[4] = BYTE1(system_time);
//	data_frame[5] = BYTE0(system_time);
//	data_frame[6] = BYTE1(battery_voltage_);
//	data_frame[7] = BYTE0(battery_voltage_);
//	data_frame[8] = BYTE1(battery_current_);
//	data_frame[9] = BYTE0(battery_current_);
//	
////	data_frame[10] = BYTE1(motor[5]);
////	data_frame[11] = BYTE0(motor[5]);
////	data_frame[12] = BYTE1(motor[6]);
////  data_frame[13] = BYTE0(motor[6]);
////	data_frame[14] = BYTE1(motor[7]);
////	data_frame[15] = BYTE0(motor[7]);
////	data_frame[16] = BYTE1(motor[8]);
////	data_frame[17] = BYTE0(motor[8]);

//	for(i = 0;i < (data_frame_length - 1);i++)
//	{
//		data_frame_sum += data_frame[i];//Sum check
//  }
//	data_frame[data_frame_length - 1] = data_frame_sum;
//	
//	return data_frame;
//}

///*
// * Function Name:GPS_Data_Frame
// * Description	:Information of GPS
// * Input  			:None
// * Output  			:Data frame
// */
//u8 * GPS_Data_Frame(void)
//{
//	static u8 data_frame[DATA_FRAME_LENGTH_24];				//Define data frame
//	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
//	u8 data_frame_sum = 0x00;
//	int i = 0;
//	
//	data_frame[0] = 0x55;  //Frame Header
//	data_frame[1] = 0x06;	 //Function Mark
//	
//	for(i = 0;i < (data_frame_length - 1);i++)
//	{
//		data_frame_sum += data_frame[i];//Sum check
//  }
//	data_frame[data_frame_length - 1] = data_frame_sum;
//	
//	return data_frame;
//}

///*
// * Function Name:Custom_Data_Frame
// * Description	:Custom information
// * Input  			:None
// * Output  			:Data frame
// */
//u8 * Custom_Data_Frame(void)
//{
//	static u8 data_frame[DATA_FRAME_LENGTH_24];				//Define data frame
//	static u16 data_frame_length = sizeof(data_frame);//Get data frame length,define static to avoid everytime bliud sizeof() function
//	u8 data_frame_sum = 0x00;
//	int i = 0;
//	
//	data_frame[0] = 0x55;  //Frame Header
//	data_frame[1] = 0x07;	 //Function Mark
//	
//	
//	for(i = 0;i < (data_frame_length - 1);i++)
//	{
//		data_frame_sum += data_frame[i];//Sum check
//  }
//	data_frame[data_frame_length - 1] = data_frame_sum;
//	
//	return data_frame;
//}

///****************************************************************************/

//void Device_To_Host_Send_Data(unsigned char *usart1_send_buf,int length)
//{
//  int i;
//	for(i = 0;i< length;i++)
//	{
//    USART_Rx_Buffer[USART_Rx_ptr_in] = usart1_send_buf[i];
//    USART_Rx_ptr_in++;
//	
//		/* To avoid buffer overflow */
//		if(USART_Rx_ptr_in == USART_RX_DATA_SIZE)
//		{
//			USART_Rx_ptr_in = 0;
//		}
//	}
//}





