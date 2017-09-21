/**************I_UWB_DT-SDK**************
 *	File					:				main.c
 *  IDE						:			  MDK5.14
 *	Author				:	 		  	INF						
 *	Support				:		 www.infcre.com
 *	QQ Group			:   	  168590475
 *  github				: https://github.com/inf-labs
 *	Copyright			:	 				 INF
 *	Last Time			:			  20170822	
 *			For infinite creativity
 */


#include "system_init.h"
#include "task.h"

/*
 * Function Name:main
 * Description	: 
 * Input  			:None
 * Output  			:None
 */
int main(void)
{
	u8 key;
	System_Init();											//system initialize
  while(1)
	{
		key=KEY_Scan();
		if(key) TIM3_Int_Init(4999,8399);
	}
}

