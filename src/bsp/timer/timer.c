#include "timer.h"
#include "bsp\led\led.h"

u8 count=0;
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM3,ENABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) 
	{
		
		if(count) LED_ON;
		else LED_OFF;
		count=!count;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  
}

