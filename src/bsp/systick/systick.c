#include "systick.h"

static __IO u32 TimingDelay = 0;

/*
 * ��������SysTick_Init
 * ����  ������ϵͳ�δ�ʱ��
 * ����  ����
 * ���  ����
 */
void Systick_Init(void)
{ 
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//SystemCoreClock / 1000    1ms�ж�һ��
	//SystemCoreClock / 500	    2ms�ж�һ��
	 
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		while (1);
	}		
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  NVIC_InitStruct.NVIC_IRQChannel = (uint8_t)SysTick_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x000F;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;//�رյδ�ʱ��  	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk; //ʹ�ܵδ�ʱ��  
}

