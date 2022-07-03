#include "Bits_utils.h"
#include "stdint.h"

#include "RCC.h"
#include "Gpio.h"
#include "UART_interface.h"

#include "DMA.h"
#include "Usart.h"

#include "ESP_interface.h"

#include"Nvic.h"
#include "diag/Trace.h"

#include "App.h"

u8 Hex_file[20000];

/* APP Meta-data */
uint32_t AppFirstAdd;
uint32_t AppEntryPoint;
uint32_t AppSize;

USARTHandel_t Loc_uart6;

static void ParseLine(u8* Line);
static u8 getHex(u8 Copy_u8Asci);

void App_init()
{
	Control_Peripheral_Clk(Peripheral_USART1,Peripheral_mode_ON);
	Control_Peripheral_Clk(Peripheral_USART6,Peripheral_mode_ON);
	Control_Peripheral_Clk(Peripheral_GPIOA,Peripheral_mode_ON);

	GpioPinCfg_t RX_USART1,TX_USART1;
	GpioPinCfg_t RX_USART6,TX_USART6;

	/* USART1 */
	/* A9 = TX output 50 Mhz  Note : You must configure this pin as AFPP  */
	TX_USART1.Mode = MODE_AF_PP;
	TX_USART1.Pin = PIN_9;
	TX_USART1.Port = GPIO_A;
	TX_USART1.Speed = SPEED_VERYHIGH;
	Gpio_Init_Pin(&TX_USART1);

	/* A10 = RX input floating */
	RX_USART1.Mode = MODE_AF_PP;
	RX_USART1.Pin = PIN_10;
	RX_USART1.Port = GPIO_A;
	RX_USART1.Speed = SPEED_VERYHIGH;
	Gpio_Init_Pin(&RX_USART1);

	/* USART6 */
	/* A11 = TX output 50 Mhz  Note : You must configure this pin as AFPP  */
	TX_USART6.Mode = MODE_AF_PP;
	TX_USART6.Pin = PIN_11;
	TX_USART6.Port = GPIO_A;
	TX_USART6.Speed = SPEED_VERYHIGH;
	Gpio_Init_Pin(&TX_USART6);

	/* A12 = RX input floating */
	RX_USART6.Mode = MODE_AF_PP;
	RX_USART6.Pin = PIN_12;
	RX_USART6.Port = GPIO_A;
	RX_USART6.Speed = SPEED_VERYHIGH;
	Gpio_Init_Pin(&RX_USART6);

	/*---Configure Uart1---*/
	Loc_uart6.BaudRate           = 9600;
	Loc_uart6.Channel_BaseAdress = USART6;
	Loc_uart6.Mode               = MODE_TX_RX;
	Loc_uart6.Parity 			 = PARITY_DISABLE;
	Loc_uart6.Stop_bits			 = STOP_BITS_ONE;
	Loc_uart6.WordLength		 = WORD_LENGHT_8B;
	Loc_uart6.state				 = ready;
	Uart_Init(&Loc_uart6);

	/* Register Callback function for USART6 */
	/*
	 *
	 *
	 *
	 *
	 */

	pu32 x = (pu32)(0x40020024);	//GPIO Enable Peripherals
	*x |= 0x88770;					// Enabling AF for USART1 & USART6 in GPIO
	Nvic_EnableIRQ(IRQ37);			//USART1 Enable interrupt
	Nvic_EnableIRQ(IRQ71);			//USART6 Enable interrupt

	MUSART1_vidInit();

	HESP_voidInit();
	HESP_voidWifiConnect("ITIians","AshmawyITI");
	HESP_voidWifiServerUrlTCP("162.253.155.225","80");
}

void App_start()
{
	volatile u8 X ;
	u8 File_req = '0';
	u8 ECU_APP_Response = 0;

	u8* PreHexFile;
	u8* PostHexFile;

	u16 HexIndex = 0;		/* Hex file index */

	u8 HexLine[100];		/* Hex Line to be parsed */


//		for(u8 i=0;i<4;i++)
//					{
//						Uart_SendByte(&Loc_uart6,0x35);
//						trace_printf("Start %d\n",i);
//						Uart_RxByte(&Loc_uart6,&ECU_APP_Response);//0x38
//						Uart_SendByte(&Loc_uart6,'a');
//						Uart_SendByte(&Loc_uart6,'b');
//						Uart_SendByte(&Loc_uart6,'c');
//						Uart_SendByte(&Loc_uart6,'d');
//						Uart_SendByte(&Loc_uart6,'e');
//						Uart_SendByte(&Loc_uart6,'f');
//						Uart_SendByte(&Loc_uart6,'g');
//						Uart_SendByte(&Loc_uart6,'h');
//						trace_printf("Done\n");
//					}
//	while(1);

	while (1) {
		X = HESP_u8ReceiveData(38,"http://fota.orgfree.com/flag.txt");

		/* Reset the App Size */
		AppSize = 0;
		HexIndex = 0;
		if(File_req != X)
		{
			File_req ^= 1;

			HESP_voidWifiServerUrlTCP("162.253.155.225","80");
			HESP_u8SendReceiveData(46,"http://fota.orgfree.com/uploads/smrt.hex",Hex_file);  // 42 -> Length of URL  + 6 -> Length of "GET " + "\r\n"

			/* Reset the App Size */
			AppSize = 0;
			HexIndex = 0;

			PreHexFile = Hex_file;
			PostHexFile = Hex_file;

			/* Excluding the header of hex file */
			while((*(PreHexFile++)) != ':');

			/* Pre-Parsing Hex File */
			do {
				if ((*PreHexFile) == '+') {
					while (*(PreHexFile++) != ':');
				} else if (((*PreHexFile) == '\r') ||
						   ((*PreHexFile) == '\n') ||
						   ((*PreHexFile) == ' '))  {
					PreHexFile += 2;
				} else {
					*(PostHexFile++) = *(PreHexFile++);
				}
			} while (*(PreHexFile+1) != 'L'); /* End Of File Indicator */

			*PostHexFile = ':'; /* Indicate End of File */
			*(PostHexFile+1) = 'Z';

			/* Parsing Hex File */
			char i;
			do {
				i = 0;
				do {
					HexLine[i++] = Hex_file[HexIndex++];
				} while (Hex_file[HexIndex] != ':');
				ParseLine(HexLine);
			} while (Hex_file[HexIndex+1] != 'Z');

			HexIndex = 0;

			trace_printf("App size %d\n",AppSize);
			trace_printf("App Entry %x\n",AppEntryPoint);
			trace_printf("App first %x\n",AppFirstAdd);


			/* Update request sent to the ECU_APP */
			do {
				Uart_SendByte(&Loc_uart6,0x55);
				Uart_RxByte(&Loc_uart6,&ECU_APP_Response);
			} while (ECU_APP_Response != 0xAA);//0xAA

			/* Enter Session Control for Bootloader */
			do {
				Uart_SendByte(&Loc_uart6,0x10);
				Uart_RxByte(&Loc_uart6,&ECU_APP_Response);
			} while (ECU_APP_Response != 0x20);

			/* Enter Request Download for Bootloader */

			Uart_SendByte(&Loc_uart6,0x34);
			Uart_RxByte(&Loc_uart6,&ECU_APP_Response);
			//while(ECU_APP_Response != 0x30);
			Uart_SendByte(&Loc_uart6, (u8)(AppEntryPoint >> 24));
			Uart_SendByte(&Loc_uart6, (u8)(AppEntryPoint >> 16));
			Uart_SendByte(&Loc_uart6, (u8)(AppEntryPoint >> 8));
			Uart_SendByte(&Loc_uart6, (u8)(AppEntryPoint >> 0));

			Uart_SendByte(&Loc_uart6, (u8)(AppSize >> 24));
			Uart_SendByte(&Loc_uart6, (u8)(AppSize >> 16));
			Uart_SendByte(&Loc_uart6, (u8)(AppSize >> 8));
			Uart_SendByte(&Loc_uart6, (u8)(AppSize >> 0));

			Uart_SendByte(&Loc_uart6, (u8)(AppFirstAdd >> 24));
			Uart_SendByte(&Loc_uart6, (u8)(AppFirstAdd >> 16));
			Uart_SendByte(&Loc_uart6, (u8)(AppFirstAdd >> 8));
			Uart_SendByte(&Loc_uart6, (u8)(AppFirstAdd >> 0));


			Uart_RxByte(&Loc_uart6,&ECU_APP_Response);
			while (ECU_APP_Response != 0x44);//0x10 + (AppEntryPoint >> 24)


			do {
				Uart_SendByte(&Loc_uart6,0x36);
				Uart_RxByte(&Loc_uart6,&ECU_APP_Response);//0x38
				trace_printf("%x\n",ECU_APP_Response);
				if (AppSize - HexIndex >= 1024) {
					for(u16 i=0;i<1024;i++)
					{
						Uart_SendByte(&Loc_uart6,Hex_file[HexIndex+i]);
					}

					Uart_RxByte(&Loc_uart6,&ECU_APP_Response);//0x46
					//trace_printf("%x\n",ECU_APP_Response);
					HexIndex += 1024;
				} else {
//					Uart_SendBufferZeroCopy(&Loc_uart6, &Hex_file[HexIndex],(AppSize - HexIndex));
					for(u16 i=0;i<AppSize - HexIndex;i++)
					{
						Uart_SendByte(&Loc_uart6,Hex_file[HexIndex+i]);
					}

					Uart_RxByte(&Loc_uart6,&ECU_APP_Response);
					HexIndex = AppSize;
				}
			} while (HexIndex != AppSize);

			do{
				Uart_SendByte(&Loc_uart6,0x37);
				Uart_RxByte(&Loc_uart6,&ECU_APP_Response);
			}while(ECU_APP_Response != 0x47);
			trace_printf("%x\n",ECU_APP_Response);

		}
		else
		{
			//Do nothing
		}
		HESP_voidWifiServerUrlTCP("162.253.155.225","80");
	}
}

static void ParseLine(u8* Line)
{
    u8 CC, i;
    static u16 Counter = 0;
    static u8 First_Line = 0;

    switch (getHex(Line[8]))
    {
    case 1:
    	Counter = 0;
    	First_Line = 0;
    	break;

    case 4: /* Extended Linear Address Record: used to identify the extended linear address  */
    	AppFirstAdd = (getHex(Line[9]) << 28) |
						(getHex(Line[10]) << 24) |
						(getHex(Line[11]) << 20) |
						(getHex(Line[12]) << 16);
        break;

    case 5: /* Start Linear Address Record: the address where the program starts to run      */
    	AppEntryPoint = ((u32)getHex(Line[9]) << 28)  |
						((u32)getHex(Line[10]) << 24) |
						((u32)getHex(Line[11]) << 20) |
						((u32)getHex(Line[12]) << 16) |
						((u32)getHex(Line[13]) << 12) |
						((u32)getHex(Line[14]) << 8) |
						((u32)getHex(Line[15]) << 4) |
						((u32)getHex(Line[16]) << 0) ;
        break;

    case 0: /* Data Rrecord: used to record data, most records of HEX files are data records */

    	if(First_Line == 0)
    	{
    		First_Line = 1;
    		AppFirstAdd |= (getHex(Line[3]) << 12) |
							(getHex(Line[4]) << 8) |
							(getHex(Line[5]) << 4) |
							(getHex(Line[6]) << 0);
    	}

        /* Get Character Count */
        CC = (getHex(Line[1]) << 4) | getHex(Line[2]);
        AppSize += CC;

        /* Get the data of the record */
        for (i = 0; i < CC / 2; i++)
        {
        	Hex_file[Counter++] = (getHex(Line[4 * i + 9]) << 4) | getHex(Line[4 * i + 10]);
        	Hex_file[Counter++] = (getHex(Line[4 * i + 11]) << 4) | getHex(Line[4 * i + 12]);
        }

        if (CC % 2 != 0)
        {
        	Hex_file[Counter++] = (getHex(Line[4 * (CC / 2) + 9]) << 4) | getHex(Line[4 * (CC / 2) + 10]);
        	Hex_file[Counter++] = 0xFF;
        	AppSize++;
        }
        break;
    default:
        break;
    }
}

static u8 getHex(u8 Copy_u8Asci)
{
    u8 Result = 0;

    /*0 ... 9*/
    if ((Copy_u8Asci >= 48) && (Copy_u8Asci <= 57))
    {
        Result = Copy_u8Asci - 48;
    }

    /*A ... F*/
    else if ((Copy_u8Asci >= 65) && (Copy_u8Asci <= 70))
    {
        Result = Copy_u8Asci - 55;
    }

    return Result;
}

