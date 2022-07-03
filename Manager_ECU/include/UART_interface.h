/**************************************************************/
/***********     Author    :  FOTA || ITI_42         **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  1-7-2022              **********/
/***********     File      :  USART_interface        **********/
/**************************************************************/

#ifndef _UART_INTERFACE_H
#define _UART_INTERFACE_H


/*******************************************************************************/
/******                               Functions                           ******/
/*******************************************************************************/


/*****************************************************************
* Name:          MUSART1_vidInit                                 *
* Description:   1-Init Baud Rate                                *
*			     2-Init Transmitter, Receiver, and Parity Status *
*			     3-Init Parity Options                           *
*				 4-Enable the UART                               *
*****************************************************************/
void MUSART1_vidInit(void);


void MUSART1_vidSendTextSynch (u8 * pu8TextDataToSend);


void MUSART1_vidSendSynch     (u8 * pu8DataToSend);



/****************************************************************************
* Name          :MUSART1_vidReceiveSynch                                    *
* Type          :Synchronous         										*
* Parameters    :Pointer to u8 Variable         						    *
* O/P           :if valid data is recevied, it will return with that Data   *
*                else if the time is up, it will return with 255            *                                
****************************************************************************/
//void MUSART1_vidReceiveSynch  (u8 * pu8ReceivedData);
void MUSART1_vidReceiveSynch(u8 * pu8ReceivedData,u32 Copy_u32timeout);


/*****************************************************************/
/******                Function's parameters                ******/
/*****************************************************************/


#endif
