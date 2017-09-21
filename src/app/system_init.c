#include "system_init.h"
#include "stm32f4xx.h"
#include "task.h"

#include "bsp\system\system_param.h"
#include "bsp\delay\delay.h"
#include "bsp\led\led.h"
#include "bsp\key\key.h"
#include "bsp\usart\usart1.h"	
#include "bsp\systick\systick.h"


/*
 * Function Name:System_Init
 * Description	:System init function
 * Input  			:None
 * Output  			:None
 */
void System_Init(void)
{
	System_Param_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  

	KEY_Init();
	LED_Init();
	USART1_Init(7);//baudrate:921600
	Systick_Init();
	TIM3_Int_Init(9999,8399);
}



