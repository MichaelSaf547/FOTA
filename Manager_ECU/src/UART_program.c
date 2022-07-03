/**************************************************************/
/***********     Author    :  FOTA || ITI_42         **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  1-7-2022              **********/
/***********     File      :  USART_program          **********/
/**************************************************************/


#include "Bits_utils.h"
//#include "MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
#include "diag/Trace.h"

/**********************************************************/
/*         Implementations of the Functions               */
/**********************************************************/
 void MUSART1_vidInit(void)
 {
	
	//MUSART1 -> BRR = 0x683;			//9600 baudrate	--> 104.1875
	MUSART1 -> BRR = 	0x8B;		//115200        --> 8.6875


	/* Initialize Transmitter,Receiver, and Parity  Status */
	/*switch (MUSART1_TRANSMITTER_STATUS)
	{
		case MUSART1_ENABLE :  SET_BIT(MUSART1 -> CR1, 3 );     break;
		case MUSART1_DISABLE:  CLR_BIT(MUSART1 -> CR1, 3 );     break;
	}
	switch (MUSART1_RECEIVER_STATUS)
	{
		case MUSART1_ENABLE :  SET_BIT(MUSART1 -> CR1, 2 );     break;
		case MUSART1_DISABLE:  CLR_BIT(MUSART1 -> CR1, 2 );     break;
	}
	switch (MUSART1_PARITY_STATUS)
	{
		case MUSART1_ENABLE :  SET_BIT(MUSART1 -> CR1, 10);     break;
		case MUSART1_DISABLE:  CLR_BIT(MUSART1 -> CR1, 10);     break;
	}*/

	//fady initialization
	MUSART1 -> CR1 |= 0x2000;
	MUSART1 -> CR2 = 0;
	MUSART1 -> CR3 = 0;
	MUSART1 -> CR1 |= 0|0|0;
	MUSART1 -> CR1 |= 0x0004; 	//Recieve Enable
	/* Parity Selection Init*/
	#if  MUSART1_PARITY_STATUS	==    MUSART1_ENABLE

	switch (MUSART1_PARITY_SELECTION)
	{
		case MUSART1_ODD :   SET_BIT(MUSART1 -> CR1, 9);    break;
		case MUSART1_EVEN:   CLR_BIT(MUSART1 -> CR1, 9);    break;
	}

	#endif



	/*Enable USART1*/
	SET_BIT(MUSART1 -> CR1, 13);
	MUSART1 -> SR = 0;

 }


void MUSART1_vidSendSynch     (u8 * pu8DatatoSend)
{
	MUSART1 -> CR1 |= 0x0008;	//transmit on
	/*Write the Data To the Transmit Buffer*/
	MUSART1 -> DR = *pu8DatatoSend; 
	/*wait until the trnsission complete*/
	while ( GET_BIT( MUSART1 -> SR,6) ==0  );

	//trace_printf("%c\n",*pu8DatatoSend);

	MUSART1 -> CR1 &= ~(0x0008);	//transmit Off
}


void MUSART1_vidSendTextSynch   (u8 * pu8TextDataToSend)
{
	u8 Loc_u8Counter=0;
	
	while (pu8TextDataToSend[Loc_u8Counter] != '\0')
	{
		MUSART1_vidSendSynch(&pu8TextDataToSend[Loc_u8Counter]);
		Loc_u8Counter++;
	}
}


void MUSART1_vidReceiveSynch(u8 * pu8ReceivedData,u32 Copy_u32timeout)
{
	u32 Loc_u8TimeOut=0;
	
	/* Make Sure that the Content is Received Buffer*/
	while (GET_BIT(MUSART1 -> SR,5)==0)		 //This flag is set when receive buffer is not empty(valid data is received)
	{
		Loc_u8TimeOut++;
		if (Loc_u8TimeOut == Copy_u32timeout)
		{
			*pu8ReceivedData = 255;         //the max. value at ASCI table is 127, so if it returned with 255, that mean the time is up without an answer
			break;
		}				
	}
	if (Loc_u8TimeOut != Copy_u32timeout)
	{
		*pu8ReceivedData= MUSART1 -> DR;
		//trace_printf("%c\n",*pu8ReceivedData);
	}
}





