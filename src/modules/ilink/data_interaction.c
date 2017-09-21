#include "data_interaction.h"
#include "ilink.h"
#include "bsp\usart\usart1.h"
#include "bsp\usart\usart.h"
#include "bsp\usart\uart4.h"


extern u8 usart1_send_buf[USART1_SEND_BUF_LENGTH];
extern u16 system_time;//��λ��S
s16 Angle_X,Angle_Y,Angle_Z;

//extern volatile S_FLOAT_XYZ Acceleration;    					//�ɻ���ǰ���ٶ�
void Data_Send(void)
{
//	int i = 0;
//	u8 send_buf_sum = 0;//У��λ
//	
//	Angle_X=(s16)(Angle.X * 100);
//	Angle_Y=(s16)(Angle.Y * 100);
//	Angle_Z=(s16)(Angle.Z * 100);
//	send_buf[0] = 0x55;//֡ͷ 
//	send_buf[1] = 0x01;//��ͷ

//	send_buf[2] = BYTEH(MPU6500_Gyro.X);
//	send_buf[3] = BYTEL(MPU6500_Gyro.X);
//	send_buf[4] = BYTEH(MPU6500_Gyro.Y);
//	send_buf[5] = BYTEL(MPU6500_Gyro.Y);
//	send_buf[6] = BYTEH(MPU6500_Gyro.Z);
//	send_buf[7] = BYTEL(MPU6500_Gyro.Z);
//	
//	send_buf[8] = BYTEH(MPU6500_Acc.X);
//	send_buf[9] = BYTEL(MPU6500_Acc.X);
//	send_buf[10] = BYTEH(MPU6500_Acc.Y);
//	send_buf[11] = BYTEL(MPU6500_Acc.Y);
//	send_buf[12] = BYTEH(MPU6500_Acc.Z);
//  send_buf[13] = BYTEL(MPU6500_Acc.Z);

//	send_buf[14] = BYTEH(Angle_X);
//	send_buf[15] = BYTEL(Angle_X);
////	send_buf[16] = BYTEH(Angle_Y);
////	send_buf[17] = BYTEL(Angle_Y);
////	send_buf[18] = BYTEH(Angle_Z);
////  send_buf[19] = BYTEL(Angle_Z);
//	
////	send_buf[20] = BYTEH(_dis[2]);
////	send_buf[21] = BYTEL(_dis[2]);
//	
//	for(i = 0;i < (SEND_BUF_LENGTH - 1);i++)//����ֽ�ΪУ���
//	{
//		send_buf_sum += send_buf[i];
//  }
//	send_buf[SEND_BUF_LENGTH - 1] = send_buf_sum;
//	
//	DMA_Cmd(DMA2_Stream7,ENABLE); //����DMA
//	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
}

#define ANO_OUT_DATA_LENGTH 32
u8 ANO_out_date[ANO_OUT_DATA_LENGTH];

void ANO_Data_Send(void)
{
//	u8 _cnt=0;
//	int i = 0;
//	//static int j = 0;

//	u8 ANO_out_date_sum = 0;//У��λ	

//	Angle_X=(s16)(Angle.X * 100);
//	Angle_Y=(s16)(Angle.Y * 100);
//	Angle_Z=(s16)(Angle.Z * 100);
//	
//	send_buf[_cnt++]  = 0xAA;//֡ͷ
//	send_buf[_cnt++]  = 0xAA;//��ͷ
//	send_buf[_cnt++]  = 0x01;//����
//	send_buf[_cnt++] = 0;
//	
//	send_buf[_cnt++] = BYTEH(Angle_X);
//	send_buf[_cnt++] = BYTEL(Angle_X);
//	send_buf[_cnt++] = BYTEH(Angle_Y);
//	send_buf[_cnt++] = BYTEL(Angle_Y);
//	send_buf[_cnt++] = BYTEH(Angle_Z);
//	send_buf[_cnt++] = BYTEL(Angle_Z);
//	
//	send_buf[_cnt++] = 0;
//	send_buf[_cnt++] = 0;
//	send_buf[_cnt++] = 0;
//	send_buf[_cnt++] = 0;
//	
//	send_buf[_cnt++] = 0;
//	
//  send_buf[_cnt++] = 0;
//	
//	send_buf[3] = _cnt - 4;


////	for(i = 0;i < (ANO_OUT_DATA_LENGTH - 1);i++)//����ֽ�ΪУ���
////	{
////		ANO_out_date_sum += ANO_out_date[i];
////  }
////	ANO_out_date[ANO_OUT_DATA_LENGTH - 1] = ANO_out_date_sum;
//	
//	for(i = 0;i < (_cnt - 1);i++)//����ֽ�ΪУ���
//	{
//		ANO_out_date_sum += send_buf[i];
//  }
//	send_buf[SEND_BUF_LENGTH - 1] = ANO_out_date_sum;
//		
//	DMA_Cmd(DMA2_Stream7,ENABLE); //����DMA
//	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
}



void Pilot_Status_USART_Data_Send(void)
{
	static u8 cnt = 0;
	
	//USART3_Data_Send(AHRS_Data_Frame(),32);
	
//	if(cnt == 1)	USART3_Data_Send(Version_Data_Frame(),24);
	
//	if(cnt == 0)	USART3_Data_Send(Version_Data_Frame(),24);
//	else if(cnt == 1)	USART3_Data_Send(AHRS_Data_Frame(),32);
//	else if(cnt == 2)	USART3_Data_Send(Location_Data_Frame(),24);
//	else if(cnt == 3)	USART3_Data_Send(Receiver_Data_Frame(),32);
//	else if(cnt == 4)	USART3_Data_Send(Motor_Data_Frame(),24);
//	else if(cnt == 5)	USART3_Data_Send(Rest_Data_Frame(),24);
	
//	else if(cnt == 6)	USART3_Data_Send(GPS_Data_Frame(),24);
//	else if(cnt == 7)	USART3_Data_Send(Custom_Data_Frame(),24);
	
	cnt++;
	if(cnt >= 5) cnt = 1;//Version_Data_Frame send once time
}


//extern volatile S_FLOAT_XYZ Position;    							//�ɻ���ǰλ��
//extern volatile S_FLOAT_XYZ Velocity;    							//�ɻ���ǰ�ٶ�
//extern volatile S_FLOAT_XYZ Acceleration;    					//�ɻ���ǰ���ٶ�

//extern volatile S_FLOAT_XYZ Exp_Position;    					//�ɻ�����λ��

void Plane_Position_Data_Send(void)
{ 
//	static volatile S_INT16_XYZ _Position;    							//�ɻ���ǰλ��
//	static volatile S_INT16_XYZ _Velocity;    							//�ɻ���ǰ�ٶ�
//	static volatile S_INT16_XYZ _Acceleration;    					//�ɻ���ǰ���ٶ�
//	
//	static s16 _target_x,_target_y;//�˲�ǰĿ��λ��
//	
//	int i = 0;
//	u8 send_buf_sum = 0;//У��λ
//	
//	_Position.X = Position.X * 100;
//	_Position.Y = Position.Y * 100;
//	_Position.Z = Position.Z * 100;
//	
//	_Velocity.X = Velocity.X * 100;
//	_Velocity.Y = Velocity.Y * 100;
//	_Velocity.Z = Velocity.Z * 100;
//	
//	_Acceleration.X = Acceleration.X * 100;
//	_Acceleration.Y = Acceleration.Y * 100;
//	_Acceleration.Z = Acceleration.Z * 100;
//	
//	_target_x = Exp_Position.X  * 100;
//	_target_y = Exp_Position.Y  * 100;
//	
//	send_buf[0] = 0x58;//֡ͷ
//	send_buf[1] = 0x01;//��ͷ

//	send_buf[2] = BYTEH(_Position.X);
//	send_buf[3] = BYTEL(_Position.X);
//	send_buf[4] = BYTEH(_Position.Y);
//	send_buf[5] = BYTEL(_Position.Y);
//	send_buf[6] = BYTEH(_Position.Z);
//	send_buf[7] = BYTEL(_Position.Z);
//	
//	send_buf[8] = BYTEH(_Velocity.X);
//	send_buf[9] = BYTEL(_Velocity.X);
//	send_buf[10] = BYTEH(_Velocity.Y);
//	send_buf[11] = BYTEL(_Velocity.Y);
//	send_buf[12] = BYTEH(_Velocity.Z);
//  send_buf[13] = BYTEL(_Velocity.Z);

//	send_buf[14] = BYTEH(_Acceleration.X);
//	send_buf[15] = BYTEL(_Acceleration.X);
//	send_buf[16] = BYTEH(_Acceleration.Y);
//	send_buf[17] = BYTEL(_Acceleration.Y);
//	send_buf[18] = BYTEH(_Acceleration.Z);
//  send_buf[19] = BYTEL(_Acceleration.Z);
//	
//	send_buf[20] = BYTEH(system_time);
//	send_buf[21] = BYTEL(system_time);
//	
//	for(i = 0;i < (SEND_BUF_LENGTH - 1);i++)//����ֽ�ΪУ���
//	{
//		send_buf_sum += send_buf[i];
//  }
//	send_buf[SEND_BUF_LENGTH - 1] = send_buf_sum;
//	
//	DMA_Cmd(DMA2_Stream7,ENABLE); //����DMA
//	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
}


void DW1000_Data_Send(void)
{
//	int i = 0;
//	u8 send_buf_sum = 0;//У��λ
//	
//	_dis_[0] = dis_[0] * 100;//�˲������������
//	_dis_[1] = dis_[1] * 100;//�˲������������
//	_dis_[2] = dis_[2] * 100;//�˲������������
//	_dis_[3] = dis_[3] * 100;//�˲������������
//	
//	send_buf[0] = 0x58;//֡ͷ
//	send_buf[1] = 0x02;//��ͷ

//	send_buf[2] = BYTEH(_dis_[0]);
//	send_buf[3] = BYTEL(_dis_[0]);
//	send_buf[4] = BYTEH(_dis_[1]);
//	send_buf[5] = BYTEL(_dis_[1]);
//	send_buf[6] = BYTEH(_dis_[2]);
//	send_buf[7] = BYTEL(_dis_[2]);
//	
//	send_buf[8] = BYTEH(_dis_[3]);
//	send_buf[9] = BYTEL(_dis_[3]);

//	
//	//send_buf[20] = BYTEH(system_time);
//	//send_buf[21] = BYTEL(system_time);
//	
//	for(i = 0;i < (SEND_BUF_LENGTH - 1);i++)//����ֽ�ΪУ���
//	{
//		send_buf_sum += send_buf[i];
//  }
//	send_buf[SEND_BUF_LENGTH - 1] = send_buf_sum;
//	
//	DMA_Cmd(DMA2_Stream7,ENABLE); //����DMA
//	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
}


extern float ut_dis[5];//�˲�ǰ����
extern float ut_dis_[5];//�˲�������
extern float target_x,target_y;//�˲�ǰĿ��λ��
extern float target_x_,target_y_;//�˲���Ŀ��λ��



void Confidant_Data_Send(void)
{
//	static s16 _ut_dis[5];//�˲�ǰ����
//	static s16 _target_x,_target_y;//�˲�ǰĿ��λ��
//	int i = 0;
//	u8 send_buf_sum = 0;//У��λ
//	
//	_ut_dis[0] = ut_dis[0] * 1000;
//	_ut_dis[1] = ut_dis[1] * 1000;
//	_ut_dis[2] = ut_dis[2] * 1000;
//	_ut_dis[3] = ut_dis[3] * 1000;
//	_ut_dis[4] = ut_dis[4] * 1000;
//	
//	_target_x = target_x  * 100;
//	_target_y = target_y  * 100;
//	
//	send_buf[0] = 0x58;//֡ͷ
//	send_buf[1] = 0x03;//��ͷ

//	send_buf[2] = BYTEH(_ut_dis[0]);
//	send_buf[3] = BYTEL(_ut_dis[0]);
//	send_buf[4] = BYTEH(_ut_dis[1]);
//	send_buf[5] = BYTEL(_ut_dis[1]);
//	send_buf[6] = BYTEH(_ut_dis[2]);
//	send_buf[7] = BYTEL(_ut_dis[2]);
//	
//	send_buf[8] = BYTEH(_ut_dis[3]);
//	send_buf[9] = BYTEL(_ut_dis[3]);
//	send_buf[10] = BYTEH(_ut_dis[4]);
//	send_buf[11] = BYTEL(_ut_dis[4]);
//	send_buf[12] = BYTEH(_target_x);
//  send_buf[13] = BYTEL(_target_x);

//	send_buf[14] = BYTEH(_target_y);
//	send_buf[15] = BYTEL(_target_y);

//	//send_buf[20] = BYTEH(system_time);
//	//send_buf[21] = BYTEL(system_time);
//	
//	for(i = 0;i < (SEND_BUF_LENGTH - 1);i++)//����ֽ�ΪУ���
//	{
//		send_buf_sum += send_buf[i];
//  }
//	send_buf[SEND_BUF_LENGTH - 1] = send_buf_sum;
//	
//	DMA_Cmd(DMA2_Stream7,ENABLE); //����DMA
//	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
}


/*
 * ��������INF_DW1000_Module_Data_Convert
 * ����  ��led��ʼ������
 * ����  ����
 * ���  ����
 */ 
void INF_DW1000_Module_Data_Convert(u8 recieve_buf[])
{
//	u8 recieve_buf_sum = 0;//У��λ
//	u8 i = 0;

//	if((recieve_buf[0] == 0x55) && (recieve_buf[1] == 0x01))//֡ͷ��ͷ���
//	{
//		for(i = 0;i < (RECIEVE_BUF_SIZE - 1);i++)//����ֽ�ΪУ���
//		{
//			recieve_buf_sum += recieve_buf[i];
//		}

//		if(recieve_buf_sum == recieve_buf[23])//����� ���
//		{
//			dis[0] = ((float)Byte16(u16, recieve_buf[2],  recieve_buf[3])) / 100;
//			dis[1] = ((float)Byte16(u16, recieve_buf[4],  recieve_buf[5])) / 100;
//			dis[2] = ((float)Byte16(u16, recieve_buf[6],  recieve_buf[7])) / 100;
//			dis[3] = ((float)Byte16(u16, recieve_buf[8],  recieve_buf[9])) / 100;
//		}

//		if(dis[0] == 0) dis[0] = dis_[0];
//		if(dis[1] == 0) dis[1] = dis_[1];
//		if(dis[2] == 0) dis[2] = dis_[2];
//		if(dis[3] == 0) dis[3] = dis_[3];
//		
//		if((dis[0] == 0) || (dis[1] == 0) || (dis[2] == 0)) dw1000_success_flag = 0;//ʧ��
//		else dw1000_success_flag = 1;//�ɹ�
//	}		
			
}


