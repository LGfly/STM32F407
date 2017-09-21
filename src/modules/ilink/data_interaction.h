#ifndef __DATE_INTERACTION_H
#define __DATE_INTERACTION_H
	
#include "stm32f4xx.h"

#define BYTEL(dwTemp)       (*(char *)(&dwTemp))
//ȡһ�����ݵĵ�ַǿ��ת����ָ��char�͵ģ�Ȼ��ȡǰ��λ
#define BYTEH(dwTemp)       (*((char *)(&dwTemp) + 1))
	

#define OUT_DATA_LENGTH 24

void ANO_Data_Send(void);
void Data_Send(void);
void Data_Send1(void);
void Data_Send2(void);
void Data_Send3(void);
void Data_Send4(void);
void Plane_Position_Data_Send(void);
void DW1000_Data_Send(void);

void INF_DW1000_Module_Data_Convert(u8 recieve_buf[]);
void Confidant_Data_Send(void);

#endif



