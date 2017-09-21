#include "usart1.h"		  
#include <stdarg.h>
#include "string.h"
#include "bsp\led\led.h"

uint16 usart1_send_buf_length = 0;
uint8 usart1_send_buf[USART1_RECEIVE_BUF_LENGTH];
uint16 usart1_receive_buf_length = 0;
uint8 usart1_receive_buf[USART1_RECEIVE_BUF_LENGTH];

uint32 usart1_baudrate_buf[9] = {9600,38400,57600,100000,115200,256000,460800,921600,1382400};

static uint32 USART1_BaudRate_Select(uint8 index);

static uint32 USART1_BaudRate_Select(uint8 index)
{
	return  usart1_baudrate_buf[index];
}

/*
 * ��������USART1_Init
 * ����  ������1��ʼ������
 * ����  ��������
 * ���  ����
 */
void USART1_Init(uint8 baudrate_index)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ�ӣ�ע�⴮��3��ʱ���ǹ���APB1�ϵ�
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10
	
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
   //USART1 ��ʼ������
	
	USART_InitStructure.USART_BaudRate = USART1_BaudRate_Select(baudrate_index);//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1  
	
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//����USART�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�3  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //�����ȼ�3  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��  
  NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART1_DMA_Init();
}


void USART1_DMA_Init(void)
{
	DMA_InitTypeDef  DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA1ʱ��ʹ�� 

	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����     
  USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);  //ʹ�ܴ���1��DMA����
	
	//****************************����USART1����  
	DMA_DeInit(DMA2_Stream7);  
	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE);//�ȴ�DMA������   
	
	/* ���� DMA Stream */  
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;  //ͨ��ѡ��  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART1->DR;//DMA�����ַ  
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)usart1_send_buf;//DMA �洢��0��ַ  
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ  
	DMA_InitStructure.DMA_BufferSize = usart1_send_buf_length;//���ݴ�����   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ   
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�  
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;           
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;  
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���  
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���  
	DMA_Init(DMA2_Stream7, &DMA_InitStructure);//��ʼ��DMA Stream  
	
	//DMA NVIC    
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
	NVIC_Init(&NVIC_InitStructure);    

	DMA_ITConfig(DMA2_Stream7,DMA_IT_TC,ENABLE);  
	
	
	//****************************����UART1����  
	DMA_DeInit(DMA2_Stream5);  
	while (DMA_GetCmdStatus(DMA2_Stream5) != DISABLE);//�ȴ�DMA������   
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;  //ͨ��ѡ��  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART1->DR;//DMA�����ַ  
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)usart1_receive_buf;//DMA �洢��0��ַ  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;//���赽�洢��ģʽ  
	DMA_InitStructure.DMA_BufferSize = USART1_RECEIVE_BUF_LENGTH;//���ݴ�����   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ   
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�е����ȼ�  
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;           
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;  
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���  
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���  
	DMA_Init(DMA2_Stream5, &DMA_InitStructure);//��ʼ��DMA Stream  
	
	DMA_Cmd(DMA2_Stream5, ENABLE);  //����DMA����
	
	usart1_rx_irq_updata_user_reset_status = 0;
	usart1_tx_irq_updata_user_reset_status = 0;
}


uint8 usart1_tx_irq_updata_user_reset_status = 0;

void DMA2_Stream7_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA2_Stream7,DMA_IT_TCIF7) != RESET)
		{
			//	LED_TX_TOGGLE;
			
        DMA_Cmd(DMA2_Stream7,DISABLE); //DISABLE DMA 
        
				DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7); 
				usart1_tx_irq_updata_user_reset_status = 0;
    }
}

/*
 * Function Name:USART1_DataFrame_Send
 * Description	:
 * Input  			:send_buf, send_buf length
 * Output  			:None
 */ 
void USART1_DataFrame_Send(unsigned char *send_buf,int length)
{
	if(usart1_tx_irq_updata_user_reset_status == 0)
	{
		memcpy(&usart1_send_buf,send_buf,length);
	
		DMA_SetCurrDataCounter(DMA2_Stream7,length);//���ô������ݳ���
		DMA_Cmd(DMA2_Stream7,ENABLE); //����DMA
		USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

		usart1_tx_irq_updata_user_reset_status = 1;
	}
}

uint8 usart1_rx_irq_updata_user_reset_status = 0;

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)
    {
				
				DMA_Cmd(DMA2_Stream5, DISABLE); 
        USART1->SR;
        USART1->DR;
			
     //   LED_RX_TOGGLE;
        DMA_ClearFlag(DMA2_Stream5,DMA_FLAG_TCIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5);//���DMA2_Steam7������ɱ�־  
				
				DMA_SetCurrDataCounter(DMA2_Stream5, USART1_RECEIVE_BUF_LENGTH);  
        DMA_Cmd(DMA2_Stream5, ENABLE);    
				usart1_rx_irq_updata_user_reset_status = 1;
				
    }
}



//*****************************************************
#if 1
#pragma import(__use_no_semihosting)             
//not use micro lib           
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       

void _sys_exit(int x) 
{ 
	x = x; 
} 
//redefine fputc function 
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET){}; 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif 
//*****************************************************

