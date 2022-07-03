/**************************************************************/
/***********     Author    :  FOTA || ITI_42         **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  1-7-2022              **********/
/***********     File      :  USART_private          **********/
/**************************************************************/

#ifndef _UART_PRIVATE_H
#define _UART_PRIVATE_H


/**********************************************************/
/*                 Registers Definition                   */
/**********************************************************/
typedef struct
{
	volatile u32 SR   ;
	volatile u32 DR   ;
	volatile u32 BRR  ;
	volatile u32 CR1  ;
	volatile u32 CR2  ;
	volatile u32 CR3  ;
	volatile u32 GRPR ;

} MUSART_t;



#define MUSART1       ((volatile MUSART_t *)0x40011000)



/**********************************************************/
/*                           GLOBALS                      */
/**********************************************************/
//static void (* vidCallBack)(u16) = NULL ;

/**********************************************************/
/*                           MACROS                       */
/**********************************************************/
#define MUSART1_ENABLE     1
#define MUSART1_DISABLE    0

#define MUSART1_EVEN       0
#define MUSART1_ODD        1

#endif
