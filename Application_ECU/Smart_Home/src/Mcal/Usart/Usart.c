#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../Dma/DMA.h"

#include "Usart.h"
#include "Usart_cfg.h"



static u32 Usart_ClearTcSecunce(USARTHandel_t * Add_uart);

typedef struct
{
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;

}USARTReg_t;

static USARTHandel_t* Glop_Uart1 = NULL;
static USARTHandel_t* Glop_Uart2 = NULL;
static USARTHandel_t* Glop_Uart6 = NULL;
static Notify_t Glop_TxCompleteCpf1;
static Notify_t Glop_TxCompleteCpf2;
static Notify_t Glop_TxCompleteCpf6;

static Notify_t Glop_RxCompleteCpf1 = NULL;
static Notify_t Glop_RxCompleteCpf2 = NULL;
static Notify_t Glop_RxCompleteCpf6 = NULL;

static u32 Usart_ClearTcSecunce(USARTHandel_t * Add_uart)
{
	u32 TempReg = ((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_SR;
	((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_DR = 0;
	((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_SR &=  ~USART_SR_TC;
	return TempReg;
}


UART_StatusTypeDef Uart_Init(USARTHandel_t * Add_uart)
{
	UART_StatusTypeDef Return_Staus = Ok;
	if(Add_uart == NULL)
	{
		Return_Staus = Null_ptr;
	}
	else if(Add_uart->state == ready)
	{
		Add_uart->state = busy;

		/*--------------Configuration of USART_CR1---------------------*/
		u32 TempReg = ((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_CR1;
		/*Clear  USART_CR1_RE USART_CR1_TE USART_CR1_M USART_CR1_UE bits*/
		TempReg &=~(u32)(USART_CR1_RE|USART_CR1_TE|USART_CR1_M|USART_CR1_UE);
		/*Set Mode  WordLength Stop_bits Parity  */
		TempReg |=(u32)(Add_uart->Mode|Add_uart->Parity|Add_uart->WordLength|USART_CR1_OVER8);
		((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_CR1=TempReg;

		/*--------------Configuration of USART_CR2----------------------*/
		TempReg = ((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_CR2;
		TempReg &=~(u32)(USART_CR2_STOP0| USART_CR2_STOP1);
        TempReg |=(u32)(Add_uart->Stop_bits);//(USART_CR2_CLKEN	|
        ((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_CR2 = TempReg;

        if(Add_uart->Channel_BaseAdress == USART6 || Add_uart->Channel_BaseAdress == USART1)
        {
        	u32 IntegerDivider = (UART1_UART6_CLK)/(8*Add_uart->BaudRate);
        	u32 FractionalDivider = ((((UART1_UART6_CLK*100)/(8*Add_uart->BaudRate)-IntegerDivider*100))*8)/100+1;
        	((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_BRR = (u32)((IntegerDivider<<4)|(FractionalDivider&0x7));
        }
        else if(Add_uart->Channel_BaseAdress == USART2)
        {
         	u32 IntegerDivider = (UART2_CLK)/(8*Add_uart->BaudRate);
            u32 FractionalDivider = ((((UART2_CLK*100)/(8*Add_uart->BaudRate)-IntegerDivider*100))*16)/100+1;
            ((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_BRR = (u32)((IntegerDivider<<4)|(FractionalDivider&0x7));
        }
        ((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_CR1 |= USART_CR1_UE;
        Add_uart->state = ready;
	}
	else
	{
		Return_Staus = uartbusy;
	}
	return Return_Staus;
}

UART_StatusTypeDef Uart_SendBufferZeroCopy(USARTHandel_t* Add_uart , u8 * Ptr_Buff,u32 Size)
{
	UART_StatusTypeDef Return_Staus = Ok;
	if(Add_uart == NULL)
	{
		Return_Staus = Null_ptr;
	}
	else if(Add_uart->state == ready)
	{
		Add_uart->state = busy;
		Add_uart->TxIndex = 1;
		Add_uart->Tx_Buffer = Ptr_Buff;
		Add_uart->Tx_Size = Size;
		switch( (u32)Add_uart->Channel_BaseAdress )
		{
			case (u32)USART1:
				Glop_Uart1 = Add_uart;
				break;
			case (u32)USART2:
				Glop_Uart2 = Add_uart;
				break;
			case (u32)USART6:
				Glop_Uart6 = Add_uart;
				break;
			default:
				Return_Staus = Not_Ok;
		}
		Usart_ClearTcSecunce(Add_uart);
		/*Enable the TX Complete INT*/
		((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_CR1 |= USART_CR1_TCIE;
		/*Send first Byte*/
		((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_DR = Add_uart->Tx_Buffer[0];
	}
	else
	{
		Return_Staus = uartbusy;
	}
	return Return_Staus;
}

UART_StatusTypeDef Uart_SendByte(USARTHandel_t* Add_uart , u8 Data)
{
	UART_StatusTypeDef Return_Staus = Ok;
	u32 CountDown = 5000;
	((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_DR = Data;
	while( ((((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_SR) & USART_SR_TC) == 0  && CountDown)/*4- Wait for the TC bit to be Erased*/
	{
		--CountDown;
	}
	if(((((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_SR) & USART_SR_TC) == 0)
	{
		Return_Staus = Not_Ok;
	}
	return Return_Staus;
}
UART_StatusTypeDef Uart_RxByte(USARTHandel_t* Add_uart , u8* Data)
{
	UART_StatusTypeDef Return_Staus = Ok;
	//u32 CountDown = 5000;
	if(  ((((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_SR) & USART_SR_RXNE) != 0  )/*4- Wait for the USART_SR_RXNE bit to be one*/
	{
		*Data = (u8) ((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_DR;
	}
	return Return_Staus;
}



UART_StatusTypeDef Uart_RXBuffer(USARTHandel_t* Add_uart , u8 * Ptr_Buff,u32 Size)
{
	UART_StatusTypeDef Return_Staus = Ok;
	if(Add_uart == NULL)
	{
		Return_Staus = Null_ptr;
	}
	else
	{
		Add_uart->RxIndex = 0;
		Add_uart->Rx_Buffer = Ptr_Buff;
		Add_uart->Rx_Size = Size;
		switch( (u32)Add_uart->Channel_BaseAdress )
		{
			case (u32)USART1:
				Glop_Uart1 = Add_uart;
				break;
			case (u32)USART2:
				Glop_Uart2 = Add_uart;
				break;
			case (u32)USART6:
				Glop_Uart6 = Add_uart;
				break;
			default:
				Return_Staus = Not_Ok;
		}
		/*Enable RX Interrupt*/
		((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_CR1 |= USART_CR1_RXNEIE;

		//Glop_Uart1->Rx_Buffer[Glop_Uart1 -> RxIndex] =(u8) ((volatile USARTReg_t *) (Glop_Uart1->Channel_BaseAdress))->USART_DR;
	}
	return Return_Staus;
}

UART_StatusTypeDef Uart_RegisterCpfTxComplet(USARTHandel_t* Add_uart , Notify_t Add_Cpf)
{
	UART_StatusTypeDef Return_Staus = Ok;
	if(Add_Cpf == NULL)
	{
		Return_Staus = Null_ptr;
	}
	else
	{
		switch( (u32)Add_uart->Channel_BaseAdress )
		{
			case (u32)USART1:
				Glop_TxCompleteCpf1 = Add_Cpf;
				break;
			case (u32)USART2:
				Glop_TxCompleteCpf2 = Add_Cpf;
				break;
			case (u32)USART6:
				Glop_TxCompleteCpf6 = Add_Cpf;
				break;
			default:
				Return_Staus = Not_Ok;
		}
	}
	return Return_Staus;
}

UART_StatusTypeDef Uart_RegisterCpfRxComplet(USARTHandel_t* Add_uart , Notify_t Add_Cpf)
{
	UART_StatusTypeDef Return_Staus = Ok;
	if(Add_Cpf == NULL)
	{
		Return_Staus = Null_ptr;
	}
	else
	{
		switch( (u32)Add_uart->Channel_BaseAdress )
		{
			case (u32)USART1:
				Glop_RxCompleteCpf1 = Add_Cpf;
				break;
			case (u32)USART2:
				Glop_RxCompleteCpf2 = Add_Cpf;
				break;
			case (u32)USART6:
				Glop_RxCompleteCpf6 = Add_Cpf;
				break;
			default:
				Return_Staus = Not_Ok;
		}
	}
	return Return_Staus;
}

UART_StatusTypeDef Uart_SendBufferDMA(USARTHandel_t* Add_uart ,DMAcfg_t* psDMAcfg ,u32  Ptr_Buff,u32 Size)
{
	UART_StatusTypeDef Return_Staus = Ok;
	if(Add_uart == NULL)
	{
		Return_Staus = Null_ptr;
	}
	else
	{
		/*Enable the TX Complete INT*/
		//((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_CR1 |= USART_CR1_TCIE;
		/*Configure START*/
		DMA_Start(psDMAcfg,Ptr_Buff,(u32)(&((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_DR),Size);
		/*Clear TC flag*/
		((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_SR  &=~ USART_SR_TC;
		/*--------------Enable DMA enable transmitter----------------------*/
		((volatile USARTReg_t *) (Add_uart->Channel_BaseAdress))->USART_CR3 |= USART_CR3_DMAT;
	}
	return Return_Staus;
}



void USART1_IRQHandler(void)
{
	u32 TempReg_SR  =  ((volatile USARTReg_t *) (Glop_Uart1->Channel_BaseAdress))->USART_SR;
	u32 TempReg_CR1 =  ((volatile USARTReg_t *) (Glop_Uart1->Channel_BaseAdress))->USART_CR1;
	//u32 TempReg_CR3 =  ((volatile USARTReg_t *) (Glop_Uart1->Channel_BaseAdress))->USART_CR3;
	if( (TempReg_SR & USART_SR_TC) &&  (TempReg_CR1 & USART_CR1_TCIE) )
	{
		if(Glop_Uart1->TxIndex == Glop_Uart1->Tx_Size)
		{
			Glop_Uart1->state = ready;
			/*Disable Interrupt */
			((volatile USARTReg_t *) (Glop_Uart1->Channel_BaseAdress))->USART_CR1 &= ~ USART_CR1_TCIE;
			if(Glop_TxCompleteCpf1 != NULL )
			{
				Glop_TxCompleteCpf1();
			}
			Usart_ClearTcSecunce(Glop_Uart1);
		}
		else
		{
			((volatile USARTReg_t *) (Glop_Uart1->Channel_BaseAdress))->USART_DR=Glop_Uart1->Tx_Buffer[Glop_Uart1->TxIndex];
			++Glop_Uart1->TxIndex;
		}
	}
	if( (TempReg_SR & USART_SR_RXNE)   && (TempReg_CR1 & USART_CR1_RXNEIE) )
	{
		Glop_Uart1->Rx_Buffer[Glop_Uart1 -> RxIndex] = (u8) ((volatile USARTReg_t *) (Glop_Uart1->Channel_BaseAdress))->USART_DR;
		++Glop_Uart1 -> RxIndex;
		if(Glop_Uart1 -> RxIndex == Glop_Uart1 -> Rx_Size)
		{
			/*Disable Interrupt */
			((volatile USARTReg_t *) (Glop_Uart1->Channel_BaseAdress))->USART_CR1 &= ~ USART_CR1_RXNEIE;
			if(Glop_RxCompleteCpf1 != NULL )
			{
				Glop_RxCompleteCpf1();
			}
		}
	}
}









