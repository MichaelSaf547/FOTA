/**************************************************************/
/***********     Author    :  FOTA || ITI_42         **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  1-7-2022              **********/
/***********     File      :  USART_cofig            **********/
/**************************************************************/


#ifndef _UART_CONFIG_H
#define _UART_CONFIG_H

/* Baud Rate Configuration: -Write the Clk Src of  APB2, and Required Baud Rate     */
#define MUSART1_APB2_CLK     8000000
#define MUSART1_BAUD_RATE    115200

/* Transmitter,Receiver, and Parity  Status Options:  MUSART1_ENABLE
 *											          MUSART1_DISABLE
 */
#define MUSART1_TRANSMITTER_STATUS	MUSART1_ENABLE
#define MUSART1_RECEIVER_STATUS	    MUSART1_ENABLE
#define MUSART1_PARITY_STATUS	    MUSART1_DISABLE


/* Parity Selection Options:  MUSART1_EVEN
 *							  MUSART1_ODD
 */
#if  MUSART1_PARITY_STATUS	==    MUSART1_ENABLE
#define MUSART1_PARITY_SELECTION	    MUSART1_EVEN
#endif


#endif
