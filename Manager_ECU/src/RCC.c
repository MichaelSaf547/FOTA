/*
 * RCC.c
 *
 *  Created on: July 1, 2022
 *      Author: FOTA || ITI_42
 *
 *  This file include Functions implementation that are used in RCC Driver
 *  with the used Registers
 */
#include "Bits_utils.h"
#include"RCC.h"

//*************************Defines****************************//
#define RCC_CR *((pu32) 0x40023800U)
#define RCC_CFGR *((pu32) 0x40023808U)
#define RCC_PLLCFGR *((pu32) 0x40023804U)
#define RCC_AHB1ENR *((pu32) 0x40023830U)
#define RCC_AHB2ENR *((pu32) 0x40023834U)
#define RCC_APB1ENR *((pu32) 0x40023840U)
#define RCC_APB2ENR *((pu32) 0x40023844U)

#define HSI_CONTROL 0x00000001		//HSI control Mask
#define HSE_CONTROL 0x00010000 		//HSE control Mask
#define PLL_CONTROL 0x01000000		//PLL control Mask

#define SWS_HSI 0		//HSI Mask
#define SWS_HSE 4		//HSE Mask
#define SWS_PLL 8		//PLL Mask
#define SWS_MASK 12		//SWS Mask

#define HSI_RDY 0x00000002	//Ready mask for HSI
#define HSE_RDY 0x00020000	//Ready mask for HSE
#define PLL_RDY 0x02000000	//Ready mask for PLL

//************************Functions***************************//

u8 Select_Sysclk(u8 Sysclk_type)
{
	u8 Error = Sysclk_ret_NOK;
	u8 SWS_val = (RCC_CFGR&SWS_MASK);
	u32 temp=0;								//to select SW value
	volatile u8 counter = 0;
	switch (Sysclk_type)
	{
	case Sysclk_HSI:
		if(SWS_val==SWS_HSI)
		{
			//Do nothing
			Error = Sysclk_ret_OK;
		}
		else
		{
			while(!Status_Sysclk(Sysclk_HSI) && counter<20)
			{
					counter++;
			}
			if(Status_Sysclk(Sysclk_HSI))
			{
				temp=RCC_CFGR;
				temp&=0x11111110;
				temp|=Sysclk_HSI;
				RCC_CFGR=temp;									//SW = HSI
				SWS_val = (RCC_CFGR&SWS_MASK);					//check SWS
				if(SWS_val==SWS_HSI)
				{
					Error = Sysclk_ret_OK;
				}
			}
			else
			{
				//Do nothing
			}
		}
		break;

	case Sysclk_HSE:
		if(SWS_val==SWS_HSE)
		{
			//Do nothing
			Error = Sysclk_ret_OK;
		}
		else
		{
			while(!Status_Sysclk(Sysclk_HSE) && counter<20)				//Wait till Ready
			{
				counter++;
			}
			if(Status_Sysclk(Sysclk_HSE))
			{
				temp=RCC_CFGR;
				temp&=0x11111110;
				temp|=Sysclk_HSE;
				RCC_CFGR=temp;									//SW = HSE
				SWS_val = (RCC_CFGR&SWS_MASK);					//check SWS
				if(SWS_val==SWS_HSE)
				{
					Error = Sysclk_ret_OK;
				}
			}
			else
			{
				//do nothing
			}
		}
		break;

	case Sysclk_PLL:
		if(SWS_val==SWS_PLL)
		{
			//Do nothing
			Error = Sysclk_ret_OK;
		}
		else
		{
			while(!Status_Sysclk(Sysclk_PLL) && counter <20)				//Wait till Ready
			{
				counter++;
			}
			if(Status_Sysclk(Sysclk_PLL))
			{
				temp=RCC_CFGR;
				temp&=0x11111110;
				temp|=Sysclk_PLL;
				RCC_CFGR=temp;									//SW = HSE
				SWS_val = (RCC_CFGR&SWS_MASK);					//check SWS
				if(SWS_val==SWS_PLL)
				{
					Error = Sysclk_ret_OK;
				}
			}
			else
			{
				//do nothing
			}
		}
		break;
	}
	return Error;
}


u8 Control_Sysclk(u8 Sysclk_type,u8 Sysclk_mode)
{
	u8 Error = Sysclk_ret_NOK;
	volatile u8 timeout = 50;
	if(Sysclk_mode==Sysclk_mode_ON)
	{
		switch(Sysclk_type)
		{
		case Sysclk_HSI:
			RCC_CR|=HSI_CONTROL;
			while(timeout && !Status_Sysclk(Sysclk_HSI))
			{
				timeout--;
			}
			if(Status_Sysclk(Sysclk_HSI))
			{
				Error = Sysclk_ret_OK;
			}
			break;
		case Sysclk_HSE:
			RCC_CR|=HSE_CONTROL;
			while(timeout && !Status_Sysclk(Sysclk_HSE))
			{
				timeout--;
			}
			if(Status_Sysclk(Sysclk_HSE))
			{
				Error = Sysclk_ret_OK;
			}
			break;
		case Sysclk_PLL:
			RCC_CR|=PLL_CONTROL;
			while(timeout && !Status_Sysclk(Sysclk_PLL))
			{
				timeout--;
			}
			if(Status_Sysclk(Sysclk_PLL))
			{
				Error = Sysclk_ret_OK;
			}
			break;
		};
	}
	else
	{
		switch(Sysclk_type)
		{
		case Sysclk_HSI:
			RCC_CR&=~(HSI_CONTROL);
			Error = Sysclk_ret_OK;
			break;
		case Sysclk_HSE:
			RCC_CR&=~(HSI_CONTROL);
			Error = Sysclk_ret_OK;
			break;
		case Sysclk_PLL:
			RCC_CR&=~(HSI_CONTROL);
			Error = Sysclk_ret_OK;
			break;
		};
	}

	return Error;
}


u8 Status_Sysclk(u8 Sysclk_type)
{
	u8 state = Sysclk_status_NRdy;
	switch (Sysclk_type)
	{
	case Sysclk_HSI:
		if(RCC_CR&HSI_RDY)
		{
			state = Sysclk_status_Rdy;
		}
		else
		{
			//do nothing
		}
		break;

	case Sysclk_HSE:
		if(RCC_CR&HSE_RDY)
		{
			state = Sysclk_status_Rdy;
		}
		else
		{
			//do nothing
		}
		break;

	case Sysclk_PLL:
		if(RCC_CR&PLL_RDY)
		{
			state = Sysclk_status_Rdy;
		}
		else
		{
			//do nothing
		}
		break;
	};

	return state;
}


u8 Config_PLL(u32 Src,u8 M,u32 N,u8 Q,u8 P)
{
	//check if PLL On or OFF
	u8 Error = PLL_NOK;
	u32 temp = 0;
	if((RCC_CR&PLL_CONTROL)==PLL_CONTROL)
	{
		//Do nothing
	}
	else if(M<2 || M>63)
	{
		//Do nothing
	}
	else if(N<192 || N>432)
	{
		//Do Nothing
	}
	else if(P>3)
	{
		//Do Nothing
	}
	else if(Q<2 || Q>15)
	{
		//Do nothing
	}
	else
	{
		temp = M | (N<<6) | (P<<16) | (Q<<24);
		RCC_PLLCFGR = temp;
		if(Src == Src_HSI)
		{
			RCC_PLLCFGR&=Src_HSI;
			//CLR_BIT(RCC_PLLCFGR,22);
		}
		else
		{
			RCC_PLLCFGR|=Src_HSE;
			//SET_BIT(RCC_PLLCFGR,22);
		}
		Error = PLL_OK;
	}
	return Error;
}


void Config_Prescaler(u8 Path,u32 value)
{
	u32 temp=RCC_CFGR;
	switch (Path)
	{
	case Path_AHBP:
		temp&=(~AHBP_512);
		temp|=value;
		RCC_CFGR = temp;
		break;

	case Path_APB1:
		temp&=(~APB1_16);
		temp|=value;
		RCC_CFGR = temp;
		break;

	case Path_APB2:
		temp&=(~APB2_16);
		temp|=value;
		RCC_CFGR = temp;
		break;
	}
}


void Control_Peripheral_Clk(u8 Peripheral,u8 Peripheral_mode)
{
	if(Peripheral<=8)	//(RCC_AHB1ENR
	{
		switch (Peripheral)
		{
		case Peripheral_GPIOA:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_AHB1ENR,0);
			}
			else
			{
				CLR_BIT(RCC_AHB1ENR,0);
			}
			break;

		case Peripheral_GPIOB:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_AHB1ENR,1);
			}
			else
			{
				CLR_BIT(RCC_AHB1ENR,1);
			}
			break;

		case Peripheral_GPIOC:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_AHB1ENR,2);
			}
			else
			{
				CLR_BIT(RCC_AHB1ENR,2);
			}
			break;

		case Peripheral_GPIOD:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_AHB1ENR,3);
			}
			else
			{
				CLR_BIT(RCC_AHB1ENR,3);
			}
			break;

		case Peripheral_GPIOE:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_AHB1ENR,4);
			}
			else
			{
				CLR_BIT(RCC_AHB1ENR,4);
			}
			break;

		case Peripheral_GPIOH:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_AHB1ENR,7);
			}
			else
			{
				CLR_BIT(RCC_AHB1ENR,7);
			}
			break;

		case Peripheral_CRC:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_AHB1ENR,12);
			}
			else
			{
				CLR_BIT(RCC_AHB1ENR,12);
			}
			break;

		case Peripheral_DMA1:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_AHB1ENR,21);
			}
			else
			{
				CLR_BIT(RCC_AHB1ENR,21);
			}
			break;

		case Peripheral_DMA2:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_AHB1ENR,22);
			}
			else
			{
				CLR_BIT(RCC_AHB1ENR,22);
			}
			break;
		}
	}
	else if(Peripheral==9)		//RCC_AHB2ENR
	{
		if(Peripheral_mode==Peripheral_mode_ON)
		{
			SET_BIT(RCC_AHB2ENR,7);
		}
		else
		{
			CLR_BIT(RCC_AHB2ENR,7);
		}
	}
	else if(Peripheral>=10 && Peripheral<=21)	//RCC_APB1ENR
	{
		switch(Peripheral)
		{
		case Peripheral_TIM2:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,0);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,0);
			}
			break;

		case Peripheral_TIM3:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,1);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,1);
			}
			break;

		case Peripheral_TIM4:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,2);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,2);
			}
			break;

		case Peripheral_TIM5:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,3);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,3);
			}
			break;

		case Peripheral_WWDG:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,11);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,11);
			}
			break;

		case Peripheral_SPI2:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,14);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,14);
			}
			break;

		case Peripheral_SPI3:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,15);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,15);
			}
			break;

		case Peripheral_USART2:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,17);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,17);
			}
			break;

		case Peripheral_I2C1:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,21);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,21);
			}
			break;

		case Peripheral_I2C2:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,22);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,22);
			}
			break;

		case Peripheral_I2C3:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,23);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,23);
			}
			break;

		case Peripheral_PWR:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB1ENR,28);
			}
			else
			{
				CLR_BIT(RCC_APB1ENR,28);
			}
			break;
		}
	}
	else							//RCC_APB2ENR
	{
		switch(Peripheral)
		{
		case Peripheral_TIM1:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,0);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,0);
			}
			break;

		case Peripheral_USART1:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,4);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,4);
			}
			break;

		case Peripheral_USART6:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,5);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,5);
			}
			break;

		case Peripheral_ADC1:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,8);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,8);
			}
			break;

		case Peripheral_SDIO:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,11);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,11);
			}
			break;

		case Peripheral_SPI1:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,12);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,12);
			}
			break;

		case Peripheral_SPI4:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,13);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,13);
			}
			break;

		case Peripheral_SYSCFG:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,14);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,14);
			}
			break;

		case Peripheral_TIM9:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,16);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,16);
			}
			break;

		case Peripheral_TIM10:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,17);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,17);
			}
			break;

		case Peripheral_TIM11:
			if(Peripheral_mode==Peripheral_mode_ON)
			{
				SET_BIT(RCC_APB2ENR,18);
			}
			else
			{
				CLR_BIT(RCC_APB2ENR,18);
			}
			break;
		}
	}
}


u8 Used_Sysclk(void)
{
	volatile u8 Res;
	u8 SWS_val = (RCC_CFGR&SWS_MASK);
	switch (SWS_val)
	{
	case SWS_HSI:
		Res = Sysclk_HSI;
		break;
	case SWS_HSE:
		Res = Sysclk_HSE;
		break;
	case SWS_PLL:
		Res = Sysclk_PLL;
		break;
	}
	return Res;
}
