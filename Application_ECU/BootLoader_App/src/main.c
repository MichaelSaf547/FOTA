#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Flash.h"
#include "BLD_Manger.h"
#include "Usart.h"
#include "SCB.h"
#include "RCC.h"





typedef void (*Notify_t)(void);

//extern USARTHandel_t Loc_uart;

int main()
{

	trace_printf("Restart\n");
	if((APP_INFO->AppEntryPoint) == 0xffffffff)
	{
		trace_printf("BL\n");
		Flash_Init();
		BLDManger_UartInit();

		while(1)
		{
			BLDManger_FlashingTask();
		}
	}
	else
	{
		Notify_t App = (Notify_t)(APP_INFO->AppEntryPoint);
		SCB_ChangeINTVECTadd(APP_INFO->AppFirstAdd);
		if(App != NULL)
		{
			App();
		}
	}
	return 0;
}
