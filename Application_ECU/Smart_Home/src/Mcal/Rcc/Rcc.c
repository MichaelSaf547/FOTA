/*
 * Rcc.c
 *
 *  Created on: Mar 9, 2022
 *      Author: Michael Safwat
 */

#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "Rcc.h"


/***********************************************************************************/

/*
 * Types
 */
typedef unsigned int uint32_t;

typedef unsigned int* puint32_t;

/***********************************************************************************/

/*
 * Numbers
 */

#define THREE		3
#define FIVE		5
#define SIX			6
#define SEVEN		7
#define NINE		9
#define TWENTYFOUR  24
#define NULL 		(uint32_t *)0x0

/***********************************************************************************/

/*
* Register Addresses
*/

#define RCC 0x40023800
#define RCC_CR           (*(uint32_t *)0x40023800)
#define RCC_PLLCFGR      (*(uint32_t *)0x40023804)
#define RCC_CFGR         (*(uint32_t *)0x40023808)
#define RCC_CIR          (*(uint32_t *)0x4002380C)
#define RCC_AHB1RSTR     (*(uint32_t *)0x40023810)
#define RCC_AHB2RSTR     (*(uint32_t *)0x40023814)
#define RCC_APN1RSTR     (*(uint32_t *)0x40023820)
#define RCC_APN2RSTR     (*(uint32_t *)0x40023824)
#define RCC_AHB1ENR      (*(uint32_t *)0x40023830)
#define RCC_AHB2ENR      (*(uint32_t *)0x40023834)
#define RCC_APB1ENR      (*(uint32_t *)0x40023840)
#define RCC_APB2ENR      (*(uint32_t *)0x40023844)
#define RCC_AHB1LPENR    (*(uint32_t *)0x40023850)
#define RCC_AHB2LPENR    (*(uint32_t *)0x40023854)
#define RCC_APB1LPENR    (*(uint32_t *)0x40023860)
#define RCC_APB2LPENR    (*(uint32_t *)0x40023864)
#define RCC_BDCR         (*(uint32_t *)0x40023870)
#define RCC_CSR          (*(uint32_t *)0x40023874)
#define RCC_SSCGR        (*(uint32_t *)0x40023880)
#define RCC_PLLI2SCFGR   (*(uint32_t *)0x40023884)
#define RCC_DCKCFGR      (*(uint32_t *)0x4002388C)

/***********************************************************************************/


/*
 * Masks for peripherals Set and Clear
 */
#define DMA2MASKS        0x00400000      //22
#define DMA2MASKC        0xFFBFFFFF      //22

#define CRCMASKS         0x00001000      //12
#define CRCMASKC         0xFFFFEFFF      //12

#define DMA1MASKS        0x00200000      //21
#define DMA1MASKC        0xFFDFFFFF      //21

#define GPIOAMASKS       0x00000001      //0
#define GPIOAMASKC       0xFFFFFFFE      //0

#define GPIOBMASKS       0x00000002      //1
#define GPIOBMASKC       0xFFFFFFFD      //1

#define GPIOCMASKS       0x00000004      //2
#define GPIOCMASKC       0xFFFFFFFB      //2

#define GPIODMASKS       0x00000008      //3
#define GPIODMASKC       0xFFFFFFF7      //3

#define GPIOEMASKS       0x00000010      //4
#define GPIOEMASKC       0xFFFFFFEF      //4

#define GPIOHMASKS       0x00000080      //7
#define GPIOHMASKC       0xFFFFFF7F      //7



#define OTGFSMASKS       0x00000080      //7
#define OTGFSMASKC       0xFFFFFF7F      //7



#define PWRMASKS         0x10000000      //28
#define PWRMASKC         0xEFFFFFFF      //28

#define I2C3MASKS        0x00800000      //23
#define I2C3MASKC        0xFF7FFFFF      //23

#define I2C2MASKS        0x00400000      //22
#define I2C2MASKC        0xFFBFFFFF      //22

#define I2C1MASKS        0x00200000      //21
#define I2C1MASKC        0xFFDFFFFF      //21

#define USART2MASKS      0x00020000      //17
#define USART2MASKC      0xFFFDFFFF      //17

#define SPI3MASKS        0x00008000      //15
#define SPI3MASKC        0xFFFF7FFF      //15

#define SPI2MASKS        0x00004000      //14
#define SPI2MASKC        0xFFFFBFFF      //14

#define WWDGMASKS        0x00000800      //11
#define WWDGMASKC        0xFFFFF7FF      //11

#define TIM5MASKS        0x00000008      //3
#define TIM5MASKC        0xFFFFFFF7      //3

#define TIM4MASKS        0x00000004      //2
#define TIM4MASKC        0xFFFFFFFB      //2

#define TIM3MASKS        0x00000002      //1
#define TIM3MASKC        0xFFFFFFFD      //1

#define TIM2MASKS        0x00000001      //0
#define TIM2MASKC        0xFFFFFFFE      //0


#define TIM11MASKS       0x00040000      //18
#define TIM11MASKC       0xFFFBFFFF      //18

#define TIM10MASKS       0x00020000      //17
#define TIM10MASKC       0xFFFDFFFF      //17

#define TIM9MASKS        0x00010000      //16
#define TIM9MASKC        0xFFFEFFFF      //16

#define SYSCFGMASKS      0x00004000      //14
#define SYSCFGMASKC      0xFFFFBFFF      //14

#define SPI4MASKS        0x00002000      //13
#define SPI4MASKC        0xFFFFDFFF      //13

#define SPI1MASKS        0x00001000      //12
#define SPI1MASKC        0xFFFFEFFF      //12

#define SDIOMASKS        0x00000800      //11
#define SDIOMASKC        0xFFFFF7FF      //11

#define ADC1MASKS        0x00000100      //8
#define ADC1MASKC        0xFFFFFEFF      //8

#define USART6MASKS      0x00000020      //5
#define USART6MASKC      0XFFFFFFDF      //5

#define USART1MASKS      0x00000010      //4
#define USART1MASKC      0xFFFFFFEF      //4

#define TIM1MASKS        0x00000001      //0
#define TIM1MASKC        0xFFFFFFFE      //0


/*
* Masks for APB1Prescaler
*/

#define PPRE1MASK1S      0x00000000
#define PPRE1MASK1C      0xFFFFFFFF

#define PPRE1MASK2S      0x00001000
#define PPRE1MASK2C      0xFFFFEFFF

#define PPRE1MASK4S      0x00001400
#define PPRE1MASK4C      0xFFFFEBFF

#define PPRE1MASK8S      0x00001800
#define PPRE1MASK8C      0xFFFFE7FF

#define PPRE1MASK16S     0x00001C00
#define PPRE1MASK16C     0xFFFFE3FF


/*
* Masks for APB2Prescaler
*/

#define PPRE2MASK1S      0x00000000
#define PPRE2MASK1C      0xFFFFFFFF

#define PPRE2MASK2S      0x00008000
#define PPRE2MASK2C      0xFFFF7FFF

#define PPRE2MASK4S      0x0000A000
#define PPRE2MASK4C      0xFFFF5FFF

#define PPRE2MASK8S      0x0000C000
#define PPRE2MASK8C      0xFFFF3FFF

#define PPRE2MASK16S     0x0000E000
#define PPRE2MASK16C     0xFFFF1FFF


/*
* Masks for AHBPrescaler
*/

#define HPREMASK1S       0x00000000
#define HPREMASK1C       0xFFFFFFFF

#define HPREMASK2S       0x00000080
#define HPREMASK2C       0xFFFFFF7F

#define HPREMASK4S       0x00000090
#define HPREMASK4C       0xFFFFFF6F

#define HPREMASK8S       0x000000A0
#define HPREMASK8C       0xFFFFFF5F

#define HPREMASK16S      0x000000B0
#define HPREMASK16C      0xFFFFFF4F

#define HPREMASK64S      0x000000C0
#define HPREMASK64C      0xFFFFFF3F

#define HPREMASK128S     0x000000D0
#define HPREMASK128C     0xFFFFFF2F

#define HPREMASK256S     0x000000E0
#define HPREMASK256C     0xFFFFFF1F

#define HPREMASK512S     0x000000F0
#define HPREMASK512C     0xFFFFFF0F


/*
* Masks for PLL
*/

#define PLLONMASK        0x01000000
#define PLLOFFMASK		 0xFEFFFFFF
#define PLLRDYMASK       0x02000000

#define PLLSRCHSIMASK    0xFFBFFFFF
#define PLLSRCHSEMASK    0x00400000

#define PLLMMASKS        0x0000003F
#define PLLMMASKC        0xFFFFFFC0

#define PLLNMASKS        0x00007FC0
#define PLLNMASKC        0xFFFF803F

#define PLLP2MASKC       0xFFFCFFFF

#define PLLP4MASKS       0x00010000

#define PLLP6MASKS       0x00020000

#define PLLP8MASKS       0x00030000

#define PLLQMASKS        0x0F000000
#define PLLQMASKC        0xF0FFFFFF


/*
 * Masks for System Clock
 */


#define SYSCLK_HSION     0x00000001
#define SYSCLK_HSEON     0x00010000
#define SYSCLK_PLLON     0x01000000

#define SYSCLK_HSIRDY    0x00000002
#define SYSCLK_HSERDY    0x00020000
#define SYSCLK_PLLRDY    0x02000000

#define SYSCLK_HSIOFF    0xFFFFFFFE
#define SYSCLK_HSEOFF    0xFFFEFFFF
#define SYSCLK_PLLOFF    0xFEFFFFFF


/*
 * SWS and SW Mask
 */

#define SWMASKS         0x00000003
#define SWMASKC         0xFFFFFFFC

#define SWSMASK         0x0000000C
#define SWSMASKHSI      0x00000000
#define SWSMASKHSE      0x00000004
#define SWSMASKPLL      0x00000008



/***********************************************************************************/

/*
 * Functions Prototype for helper function
 */

Rcc_tenuErrorStatus Rcc_enuConfigurePLLSource(u8 Copy_u8PLLSource, puint32_t Add_pu32Register);

Rcc_tenuErrorStatus Rcc_enuConfigurePLLM(u8 Copy_u8PLLM, puint32_t Add_pu32Register);

Rcc_tenuErrorStatus Rcc_enuConfigurePLLN(u16 Copy_u16PLLN, puint32_t Add_pu32Register);

Rcc_tenuErrorStatus Rcc_enuConfigurePLLP(u8 Copy_u8PLLP, puint32_t Add_pu32Register);

Rcc_tenuErrorStatus Rcc_enuConfigurePLLQ(u8 Copy_u8PLLQ, puint32_t Add_pu32Register);

Rcc_tenuErrorStatus Rcc_enuControlSystemClockHSIOn();

Rcc_tenuErrorStatus Rcc_enuControlSystemClockHSEOn();

Rcc_tenuErrorStatus Rcc_enuControlSystemClockPLLOn();

Rcc_tenuErrorStatus Rcc_enuControlSystemClockHSIOff();

Rcc_tenuErrorStatus Rcc_enuControlSystemClockHSEOff();

Rcc_tenuErrorStatus Rcc_enuControlSystemClockPLLOff();

Rcc_tenuErrorStatus Rcc_enuControlAHBPreScaler(u16 Copy_u16PreScaler);

Rcc_tenuErrorStatus Rcc_enuControlAPB1PreScaler(u8 Copy_u8PreScaler);

Rcc_tenuErrorStatus Rcc_enuControlAPB2PreScaler(u8 Copy_u8PreScaler);


/***********************************************************************************/

/*
 * InterFacing Functions Implementation
 */

Rcc_tenuErrorStatus Rcc_enuSelectSysClock(u8 Copy_u8SysClk)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;
	/*Loc_CompareValue is used to compare the value of the SWS bits with SW bits*/
	volatile uint32_t Loc_CompareValue = 0;
	/*Loc_ClockStatus is used to get the result of the clock status*/
	u8 Loc_ClockStatus;

	/*Check if the input is less than three to be sure that it is between HSI, HSE, PLL*/
	if(Copy_u8SysClk < THREE)
	{
		/*Get the status of the clock to make sure it is ready to be the system clock*/
		Loc_enuReturnStatus = Rcc_enuGetStatusClock(Copy_u8SysClk, &Loc_ClockStatus);

		/*check if the clock is ready*/
		if(Loc_ClockStatus == READY)
		{
			/*Loc_u32Register is used to map the value inside the RCC_CFGR register*/
			uint32_t Loc_u32Register = RCC_CFGR;
			/*Loc_u8TimeOut is used as a timeout counter to make sure that the operation is done or not.*/
			u8 Loc_u8TimeOut = 20;

			/*Clear the SW bits and then add the value of the clock that the user want to use*/
			Loc_u32Register &= SWMASKC;
			Loc_u32Register |= Copy_u8SysClk;

			/*Set the mapped value into the register*/
			RCC_CFGR = Loc_u32Register;

			/*Read the SWS bits value to make sure if they are equal to the SW bits*/
			Loc_CompareValue = ((RCC_CFGR & SWSMASK) >> TWO);

			/*Check if SWS bits value is equal to the SW bits*/
			while((Loc_u8TimeOut > 0) && (Copy_u8SysClk != Loc_CompareValue))
			{
				/*Reduce the Loc_u8TimeOut value by 1 and reread the SWS bits value to recheck*/
				Loc_u8TimeOut -= 1;
				Loc_CompareValue = ((RCC_CFGR & SWSMASK) >> TWO);
			}/*end of while((Loc_u8TimeOut > 0) && (Copy_u8SysClk != Loc_CompareValue))*/

			/*Check if the while was broken by the TimeOut variable or by the register SWS bits value*/
			if(Loc_u8TimeOut != 0)
			{
				//Do Nothing. Done
			}/*end of the if(Loc_u8TimeOut != 0)*/
			else
			{
				Loc_enuReturnStatus = Rcc_enuSysClkError;
			}/*end of else of if(Loc_u8TimeOut != 0)*/

		}/*end of if(Loc_ClockStatus == READY)*/
		else
		{
			Loc_enuReturnStatus = Rcc_enuOnReadyError;
		}/*end of else of if(Loc_ClockStatus == READY)*/
	}/*end of if(Copy_u8SysClk < THREE)*/
	else
	{
		Loc_enuReturnStatus = Rcc_enuSysClkError;
	}/*end of else of if(Copy_u8SysClk < THREE)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuGetSysClock(pu8 Add_pu8SysClk)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if the pointer is pointing to NULL*/
	if(Add_pu8SysClk == (pu8)NULL)
	{
		/*Set Rcc_enuNullPointr to Loc_enuReturnStatus as the pointer is pointing to NULL*/
		Loc_enuReturnStatus = Rcc_enuNullPointr;
	}/*end of if(Add_pu8SysClk == (pu8)NULL)*/
	else
	{
		/*Loc_u8 is used to read the SWS bits of the register*/
		u8 Loc_u8 = SWSMASK & RCC_CFGR;

		/*Check the result of the SWS bits*/
		if(Loc_u8 == SWSMASKHSI)
		{
			*Add_pu8SysClk = SYSCLK_HSI;
		}/*end of if(Loc_u8 == SWSMASKHSI)*/
		else if(Loc_u8 == SWSMASKHSE)
		{
			*Add_pu8SysClk = SYSCLK_HSE;
		}/*end of else if(Loc_u8 == SWSMASKHSE) of if(Loc_u8 == SWSMASKHSI)*/
		else if(Loc_u8 == SWSMASKPLL)
		{
			*Add_pu8SysClk = SYSCLK_PLL;
		}/*end of else if(Loc_u8 == SWSMASKPLL) of if(Loc_u8 == SWSMASKHSI)*/
		else
		{
			/*It will never happen*/
		}
	}/*end of else of if(Add_pu8SysClk == (pu8)NULL)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuSysClockOnOff(u8 Copy_u8SysClk, u8 Copy_u8OnOff)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Switch on the input source clock*/
	switch(Copy_u8SysClk)
	{
		case SYSCLK_HSI:
		{
			/*Check if it is ON jump to ON if it is OFF jump to OFF*/
			if(Copy_u8OnOff == ON)
			{
				/*Jump to ON function*/
				Loc_enuReturnStatus = Rcc_enuControlSystemClockHSIOn();
			}/*end of if(Copy_u8OnOff == ON)*/
			else if(Copy_u8OnOff == OFF)
			{
				/*Jump to OFF function*/
				Loc_enuReturnStatus = Rcc_enuControlSystemClockHSIOff();
			}/*end of else if(Copy_u8OnOff == OFF) of if(Copy_u8OnOff == ON)*/
			else
			{
				/*Set Rcc_enuOnOffError to Loc_enuReturnStatus as the option is invalid*/
				Loc_enuReturnStatus = Rcc_enuOnOffError;
			}/*end of else of if(Copy_u8OnOff == ON)*/
			break;
		}
		case SYSCLK_HSE:
		{
			/*Check if it is ON jump to ON if it is OFF jump to OFF*/
			if(Copy_u8OnOff == ON)
			{
				/*Jump to ON function*/
				Loc_enuReturnStatus = Rcc_enuControlSystemClockHSEOn();
			}/*end of if(Copy_u8OnOff == ON)*/
			else if(Copy_u8OnOff == OFF)
			{
				/*Jump to OFF function*/
				Loc_enuReturnStatus = Rcc_enuControlSystemClockHSEOff();
			}/*end of else if(Copy_u8OnOff == OFF) of if(Copy_u8OnOff == ON)*/
			else
			{
				/*Set Rcc_enuOnOffError to Loc_enuReturnStatus as the option is invalid*/
				Loc_enuReturnStatus = Rcc_enuOnOffError;
			}/*end of else of if(Copy_u8OnOff == ON)*/
			break;
		}
		case SYSCLK_PLL:
		{
			/*Check if it is ON jump to ON if it is OFF jump to OFF*/
			if(Copy_u8OnOff == ON)
			{
				/*Jump to ON function*/
				Loc_enuReturnStatus = Rcc_enuControlSystemClockPLLOn();
			}/*end of if(Copy_u8OnOff == ON)*/
			else if(Copy_u8OnOff == OFF)
			{
				/*Jump to OFF function*/
				Loc_enuReturnStatus = Rcc_enuControlSystemClockPLLOff();
			}/*end of else if(Copy_u8OnOff == OFF) of if(Copy_u8OnOff == ON)*/
			else
			{
				/*Set Rcc_enuOnOffError to Loc_enuReturnStatus as the option is invalid*/
				Loc_enuReturnStatus = Rcc_enuOnOffError;
			}/*end of else of if(Copy_u8OnOff == ON)*/
			break;
		}
		default:
		{
			/*Set Rcc_enuSysClkError to Loc_enuReturnStatus as the source is invalid*/
			Loc_enuReturnStatus = Rcc_enuSysClkError;
		}
	}/*end of switch(Copy_u8SysClk)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuGetStatusClock(u8 Copy_u8SysClk, pu8 Add_pu8ClockStatus)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if the pointer is pointing to NULL*/
	if(Add_pu8ClockStatus != (pu8)NULL)
	{
		/*Switch on the clock source*/
		switch(Copy_u8SysClk)
		{
			case SYSCLK_HSI:
			{
				/*Check if it is ready or not*/
				if(RCC_CR & SYSCLK_HSIRDY)
				{
					*Add_pu8ClockStatus = READY;
				}/*end of if(RCC_CR & SYSCLK_HSIRDY)*/
				else
				{
					*Add_pu8ClockStatus = NOTREADY;
				}/*end of else of if(RCC_CR & SYSCLK_HSIRDY)*/
				break;
			}
			case SYSCLK_HSE:
			{
				/*Check if it is ready or not*/
				if(RCC_CR & SYSCLK_HSERDY)
				{
					*Add_pu8ClockStatus = READY;
				}/*end of if(RCC_CR & SYSCLK_HSERDY)*/
				else
				{
					*Add_pu8ClockStatus = NOTREADY;
				}/*end of else of if(RCC_CR & SYSCLK_HSERDY)*/
				break;
			}
			case SYSCLK_PLL:
			{
				/*Check if it is ready or not*/
				if(RCC_CR & SYSCLK_PLLRDY)
				{
					*Add_pu8ClockStatus = READY;
				}/*end of if(RCC_CR & SYSCLK_PLLRDY)*/
				else
				{
					*Add_pu8ClockStatus = NOTREADY;
				}/*end of else of if(RCC_CR & SYSCLK_PLLRDY)*/
				break;
			}
			default:
			{
				/*Set Rcc_enuSysClkError to Loc_enuReturnStatus as the input clock is not valid*/
				Loc_enuReturnStatus = Rcc_enuSysClkError;
			}
		}/*end of switch(Copy_u8SysClk)*/
	}/*end of if(Add_pu8ClockStatus != (pu8)NULL)*/
	else
	{
		/*Set Rcc_enuNullPointr to Loc_enuReturnStatus as the pointer is pointing to NULL*/
		Loc_enuReturnStatus = Rcc_enuNullPointr;
	}/*end of else of if(Add_pu8ClockStatus != (pu8)NULL)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuConfigurePLL(u8 Copy_u8PLLSource, u8 Copy_u8M, u16 Copy_u16N, u8 Copy_u8P, u8 Copy_u8Q)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if the PLL is ON*/
	if(RCC_CR & PLLONMASK)
	{
		/*Set Rcc_enuPLLIsOn to Loc_enuReturnStatus as the PLL is ONE and it can not be configured whenever it is ON*/
		Loc_enuReturnStatus = Rcc_enuPLLIsOn;
	}/*end of if(RCC_CR & PLLONMASK)*/
	else
	{
		/*Loc_Register is used to sum up the configuration values together then assign it to the register.*/
		uint32_t Loc_Register = 0x00;

		/*Assign the PLL source to the Loc_Register*/
		Loc_enuReturnStatus = Rcc_enuConfigurePLLSource(Copy_u8PLLSource, &Loc_Register);

		/*Check if the previous operation completed correctly*/
		if(Loc_enuReturnStatus == Rcc_enuOk)
		{
			/*Assign the PLL M prescaler value to the Loc_Register*/
			Loc_enuReturnStatus = Rcc_enuConfigurePLLM(Copy_u8M, &Loc_Register);
		}/*end of if(Loc_enuReturnStatus == Rcc_enuOk)*/
		else
		{
			//Do Nothing
		}/*end of else of if(Loc_enuReturnStatus == Rcc_enuOk)*/

		/*Check if the previous operation completed correctly*/
		if(Loc_enuReturnStatus == Rcc_enuOk)
		{
			/*Assign the PLL N prescaler value to the Loc_Register*/
			Loc_enuReturnStatus = Rcc_enuConfigurePLLN(Copy_u16N, &Loc_Register);
		}/*end of if(Loc_enuReturnStatus == Rcc_enuOk)*/
		else
		{
			//Do Nothing
		}/*end of else of if(Loc_enuReturnStatus == Rcc_enuOk)*/

		/*Check if the previous operation completed correctly*/
		if(Loc_enuReturnStatus == Rcc_enuOk)
		{
			/*Assign the PLL P prescaler value to the Loc_Register*/
			Loc_enuReturnStatus = Rcc_enuConfigurePLLP(Copy_u8P, &Loc_Register);
		}/*end of if(Loc_enuReturnStatus == Rcc_enuOk)*/
		else
		{
			//Do Nothing
		}/*end of else of if(Loc_enuReturnStatus == Rcc_enuOk)*/

		/*Check if the previous operation completed correctly*/
		if(Loc_enuReturnStatus == Rcc_enuOk)
		{
			/*Assign the PLL Q prescaler value to the Loc_Register*/
			Loc_enuReturnStatus = Rcc_enuConfigurePLLQ(Copy_u8Q, &Loc_Register);
		}/*end of if(Loc_enuReturnStatus == Rcc_enuOk)*/
		else
		{
			//Do Nothing
		}/*end of else of if(Loc_enuReturnStatus == Rcc_enuOk)*/

		/*Check if the previous operation completed correctly*/
		if(Loc_enuReturnStatus == Rcc_enuOk)
		{
			/*Assign the total value of all the configuration into the register.*/
			RCC_PLLCFGR = Loc_Register;
		}/*end of if(Loc_enuReturnStatus == Rcc_enuOk)*/
		else
		{
			//Don Nothing
		}/*end of else of if(Loc_enuReturnStatus == Rcc_enuOk)*/

	}/*end of else of if(RCC_CR & PLLONMASK)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuPrescalerBus(u8 Copy_u8Bus, u16 Copy_u16BusPrescaler)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Switch on the input of the bus and jump to the function of the bus if the input is valid*/
	switch(Copy_u8Bus)
	{
		case AHBBUS:
		{
			/*Jump to AHB function*/
			Loc_enuReturnStatus = Rcc_enuControlAHBPreScaler(Copy_u16BusPrescaler);
			break;
		}

		case APB1BUS:
		{
			/*Jump to APB1 function*/
			Loc_enuReturnStatus = Rcc_enuControlAPB1PreScaler((u8)Copy_u16BusPrescaler);
			break;
		}
		case APB2BUS:
		{
			/*Jump to APB2 function*/
			Loc_enuReturnStatus = Rcc_enuControlAPB2PreScaler((u8)Copy_u16BusPrescaler);
			break;
		}
		default:
		{
			/*Set Rcc_enuBusError to Loc_enuReturnStatus as the input bus is invalid*/
			Loc_enuReturnStatus = Rcc_enuBusError;
			break;
		}
	}/*end of switch(Copy_u8Bus)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuEnableClockPeripheral(u8 Copy_u8PeripheralId)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;


	/*
	 * Switch on the input peripheral id and then enable the peripheral by OR the peripheral
	 * mask with the specified register.
	 */
	switch(Copy_u8PeripheralId)
	{
	    case DMA2:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | DMA2MASKS;
	    	break;
	    }
	    case DMA1:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | DMA1MASKS;
	    	break;
	    }
	    case CRC:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | CRCMASKS;
	    	break;
	    }
	    case GPIOA:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOAMASKS;
	    	break;
	    }
	    case GPIOB:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOBMASKS;
	    	break;
	    }
	    case GPIOC:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOCMASKS;
	    	break;
	    }
	    case GPIOD:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIODMASKS;
	    	break;
	    }
	    case GPIOE:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOEMASKS;
	    	break;
	    }
	    case GPIOH:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOHMASKS;
	    	break;
	    }
	    case OTGFS:
	    {
	    	RCC_AHB2ENR = RCC_AHB2ENR | OTGFSMASKS;
	    	break;
	    }
	    case PWR:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | PWRMASKS;
	    	break;
	    }
	    case I2C3:
	    {

	    	RCC_APB1ENR = RCC_APB1ENR | I2C3MASKS;
	    	break;
	    }
	    case I2C2:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | I2C2MASKS;
	    	break;
	    }
	    case I2C1:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | I2C1MASKS;
	    	break;
	    }
	    case USART_2:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | USART2MASKS;
	    	break;
	    }
	    case SPI3:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | SPI3MASKS;
	    	break;
	    }
	    case SPI2:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | SPI2MASKS;
	    	break;
	    }
	    case WWDG:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | WWDGMASKS;
	    	break;
	    }
	    case TIM5:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | TIM5MASKS;
	    	break;
	    }
	    case TIM4:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | TIM4MASKS;
	    	break;
	    }
	    case TIM3:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | TIM3MASKS;
	    	break;
	    }
	    case TIM2:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | TIM2MASKS;
	    	break;
	    }
	    case TIM11:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | TIM11MASKS;
	    	break;
	    }
	    case TIM10:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | TIM10MASKS;
	    	break;
	    }
	    case TIM9:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | TIM9MASKS;
	    	break;
	    }
	    case SYSCFG:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | SYSCFGMASKS;
	    	break;
	    }
	    case SPI4:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | SPI4MASKS;
	    	break;
	    }
	    case SPI1:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | SPI1MASKS;
	    	break;
	    }
	    case SDIO:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | SDIOMASKS;
	    	break;
	    }
	    case ADC1:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | ADC1MASKS;
	    	break;
	    }
	    case USART_6:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | USART6MASKS;
	    	break;
	    }
	    case USART_1:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | USART1MASKS;
	    	break;
	    }
	    case TIM1:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | TIM1MASKS;
	    	break;
	    }

	    default:
	    {
	    	/*Set Rcc_enuPeripheralIDError to Loc_enuReturnStatus as the input is not valid*/
	    	Loc_enuReturnStatus = Rcc_enuPeripheralIDError;
	    	break;
	    }
	}

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuDisableClockPeripheral(u8 Copy_u8PeripheralId)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Switch on the input and mask the register of the peripheral and the mask of the peripheral.*/
	switch(Copy_u8PeripheralId)
	{
	    case DMA2:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | DMA2MASKC;
	    	break;
	    }
	    case DMA1:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | DMA1MASKC;
	    	break;
	    }
	    case CRC:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | CRCMASKC;
	    	break;
	    }
	    case GPIOA:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOAMASKC;
	    	break;
	    }
	    case GPIOB:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOBMASKC;
	    	break;
	    }
	    case GPIOC:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOCMASKC;
	    	break;
	    }
	    case GPIOD:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIODMASKC;
	    	break;
	    }
	    case GPIOE:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOEMASKC;
	    	break;
	    }
	    case GPIOH:
	    {
	    	RCC_AHB1ENR = RCC_AHB1ENR | GPIOHMASKC;
	      	break;
	    }
	    case OTGFS:
	    {
	    	RCC_AHB2ENR = RCC_AHB2ENR | OTGFSMASKC;
	    	break;
	    }
	    case PWR:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | PWRMASKC;
	    	break;
	    }
	    case I2C3:
	    {

	    	RCC_APB1ENR = RCC_APB1ENR | I2C3MASKC;
	    	break;
	    }
	    case I2C2:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | I2C2MASKC;
	    	break;
	    }
	    case I2C1:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | I2C1MASKC;
	    	break;
	    }
	    case USART_2:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | USART2MASKC;
	    	break;
	    }
	    case SPI3:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | SPI3MASKC;
	      	  break;
	    }
	    case SPI2:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | SPI2MASKC;
	    	break;
	    }
	    case WWDG:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | WWDGMASKC;
	    	break;
	    }
	    case TIM5:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | TIM5MASKC;
	    	break;
	    }
	    case TIM4:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | TIM4MASKC;
	    	break;
	    }
	    case TIM3:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | TIM3MASKC;
	      break;
	    }
	    case TIM2:
	    {
	    	RCC_APB1ENR = RCC_APB1ENR | TIM2MASKC;
	    	break;
	    }
	    case TIM11:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | TIM11MASKC;
	    	break;
	    }
	    case TIM10:
	    {
	      RCC_APB2ENR = RCC_APB2ENR | TIM10MASKC;
	      break;
	    }
	    case TIM9:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | TIM9MASKC;
	    	break;
	    }
	    case SYSCFG:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | SYSCFGMASKC;
	    	break;
	    }
	    case SPI4:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | SPI4MASKC;
	    	break;
	    }
	    case SPI1:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | SPI1MASKC;
	    	break;
	    }
	    case SDIO:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | SDIOMASKC;
	      	break;
	    }
	    case ADC1:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | ADC1MASKC;
	    	break;
	    }
	    case USART_6:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | USART6MASKC;
	    	break;
	    }
	    case USART_1:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | USART1MASKC;
	    	break;
	    }
	    case TIM1:
	    {
	    	RCC_APB2ENR = RCC_APB2ENR | TIM1MASKC;
	    	break;
	    }

	    default:
	    {
	    	/*Set Rcc_enuPeripheralIDError to Loc_enuReturnStatus as the input is invalid*/
	    	Loc_enuReturnStatus = Rcc_enuPeripheralIDError;
	    	break;
	    }
	}/*end of switch(Copy_u8PeripheralId)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuControlAHBPreScaler(u16 Copy_u16PreScaler)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/* Switch on the input prescaler and clear the bits of the prescaler
	 * and then OR the input with mask of the input value.
	 */
	switch(Copy_u16PreScaler)
	{
    	case ONE:
    	{
    		RCC_CFGR = RCC_CFGR & HPREMASK2C;
    		break;
		}
		case TWO:
		{
			RCC_CFGR = RCC_CFGR & HPREMASK2C;
			RCC_CFGR = RCC_CFGR | HPREMASK2S;
			break;
		}
		case FOUR:
		{
			RCC_CFGR = RCC_CFGR & HPREMASK4C;
			RCC_CFGR = RCC_CFGR | HPREMASK4S;
			break;
		}
		case EIGHT:
		{
			RCC_CFGR = RCC_CFGR & HPREMASK8C;
			RCC_CFGR = RCC_CFGR | HPREMASK8S;
			break;
		}
		case SIXTEEN:
		{
			RCC_CFGR = RCC_CFGR & HPREMASK16C;
			RCC_CFGR = RCC_CFGR | HPREMASK16S;
			break;
		}
		case SIXTYFOUR:
		{
			RCC_CFGR = RCC_CFGR & HPREMASK64C;
			RCC_CFGR = RCC_CFGR | HPREMASK64S;
			break;
		}
		case ONEHUNTWNTYEIGHT:
		{
			RCC_CFGR = RCC_CFGR & HPREMASK128C;
			RCC_CFGR = RCC_CFGR | HPREMASK128S;
			break;
		}
		case TWOHUNFIFTYSIX:
		{
			RCC_CFGR = RCC_CFGR & HPREMASK256C;
			RCC_CFGR = RCC_CFGR | HPREMASK256S;
			break;
		}
		case FIVEHUNTWELVE:
		{
			RCC_CFGR = RCC_CFGR & HPREMASK512C;
			RCC_CFGR = RCC_CFGR | HPREMASK512S;
			break;
		}
		default:
		{
			/*Set the Rcc_enuPrecalerError to Loc_enuReturnStatus as the input prescaler is invalid.*/
			Loc_enuReturnStatus = Rcc_enuPrecalerError;
		}
	}/*end of switch(Copy_u16PreScaler)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuControlAPB1PreScaler(u8 Copy_u8PreScaler)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/* Switch on the input prescaler and clear the bits of the prescaler
	 * and then OR the input with mask of the input value.
	 */
	switch(Copy_u8PreScaler)
	{
		case ONE:
		{
			RCC_CFGR = RCC_CFGR & PPRE1MASK2C;
			break;
		}
		case TWO:
		{
			RCC_CFGR = RCC_CFGR & PPRE1MASK2C;
			RCC_CFGR = RCC_CFGR | PPRE1MASK2S;
			break;
		}
		case FOUR:
		{
			RCC_CFGR = RCC_CFGR & PPRE1MASK4C;
			RCC_CFGR = RCC_CFGR | PPRE1MASK4S;
			break;
		}
		case EIGHT:
		{
			RCC_CFGR = RCC_CFGR & PPRE1MASK8C;
			RCC_CFGR = RCC_CFGR | PPRE1MASK8S;
			break;
		}
		case SIXTEEN:
		{
			RCC_CFGR = RCC_CFGR & PPRE1MASK16C;
			RCC_CFGR = RCC_CFGR | PPRE1MASK16S;
			break;
		}
		default:
		{
			/*Set the Rcc_enuPrecalerError to Loc_enuReturnStatus as the input prescaler is invalid.*/
			Loc_enuReturnStatus = Rcc_enuPrecalerError;
		}
	}/*end of switch(Copy_u8PreScaler)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuControlAPB2PreScaler(u8 Copy_u8PreScaler)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/* Switch on the input prescaler and clear the bits of the prescaler
	 * and then OR the input with mask of the input value.
	 */
	switch(Copy_u8PreScaler)
	  {
		case ONE:
		{
			RCC_CFGR = RCC_CFGR & PPRE2MASK2S;
			break;
		}
		case TWO:
		{
			RCC_CFGR = RCC_CFGR & PPRE2MASK2S;
			RCC_CFGR = RCC_CFGR | PPRE2MASK2C;
			break;
		}
		case FOUR:
		{
			RCC_CFGR = RCC_CFGR & PPRE2MASK4S;
			RCC_CFGR = RCC_CFGR | PPRE2MASK4C;
			break;
		}
		case EIGHT:
		{
			RCC_CFGR = RCC_CFGR & PPRE2MASK8S;
			RCC_CFGR = RCC_CFGR | PPRE2MASK8C;
			break;
		}
		case SIXTEEN:
		{
			RCC_CFGR = RCC_CFGR & PPRE2MASK16S;
			RCC_CFGR = RCC_CFGR | PPRE2MASK16C;
			break;
		}
		default:
		{
			/*Set the Rcc_enuPrecalerError to Loc_enuReturnStatus as the input prescaler is invalid.*/
			Loc_enuReturnStatus =  Rcc_enuPrecalerError;
		}
	}/*end of switch(Copy_u8PreScaler)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuConfiugreMCO(u8 Copy_u8MCO1OR2, u32 Copy_u32MCOSource, u32 Copy_u32MCOPrescaler)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	u32 Loc_u32TempRegister = RCC_CFGR;

	/*Switch on the MCO type*/
	switch(Copy_u8MCO1OR2)
	{
		case MCO1:
		{
			/*Clear the source bits*/
			Loc_u32TempRegister &= MCO1SOURCEC;

			/*Set the input value of source*/
			Loc_u32TempRegister |= Copy_u32MCOSource;

			/*Clear the prescaler bits*/
			Loc_u32TempRegister &= MCO1PRESCALC;

			/*Set the input value of the prescaler*/
			Loc_u32TempRegister |= Copy_u32MCOPrescaler;

			/*Save the temp register value into the register*/
			RCC_CFGR = Loc_u32TempRegister;

			break;
		}/*end of case MCO1*/

		case MCO2:
		{
			/*Clear the source bits*/
			Loc_u32TempRegister &= MCO2SOURCEC;

			/*Set the input value of source*/
			Loc_u32TempRegister |= Copy_u32MCOSource;

			/*Clear the prescaler bits*/
			Loc_u32TempRegister &= MCO2PRESCALC;

			/*Set the input value of the prescaler*/
			Loc_u32TempRegister |= Copy_u32MCOPrescaler;

			/*Save the temp register value into the register*/
			RCC_CFGR = Loc_u32TempRegister;

			break;
		}/*end of case MCO2*/

		default:
		{
			/*Set Rcc_enuMCOType to Loc_enuReturnStatus as the input is out of range.*/
			Loc_enuReturnStatus = Rcc_enuMCOType;

			break;
		}/*end of default*/
	}/*end of switch(Copy_u8MCO1OR2)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuConfigurePLLSource(u8 Copy_u8PLLSource, puint32_t Add_pu32Register)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if the pointer is not NULL*/
	if(Add_pu32Register != NULL)
	{
		/*Switch on the source of the clock.*/
		switch(Copy_u8PLLSource)
		{
		case PLLSOURCEHSI:
			{
				/*Clear the PLL source bit in the register to be make HSI the source*/
				(*Add_pu32Register) &= PLLSRCHSIMASK;
				break;
			}
		case PLLSOURCEHSE:
			{
				/*Clear the PLL source bit in the register to be make HSE the source*/
				(*Add_pu32Register) |= PLLSRCHSEMASK;
				break;
			}
		default:
			{
				/*Set Rcc_enuPLLSourceError to Loc_enuReturnStatus as the source is not valid*/
				Loc_enuReturnStatus = Rcc_enuPLLSourceError;
				break;
			}
		}/*end of switch(Copy_u8PLLSource)*/

	}/*end of if(Add_pu32Register != NULL)*/
	else
	{
		/*Set Rcc_enuNullPointr to Loc_enuReturnStatus as the pointer equals NULL*/
		Loc_enuReturnStatus = Rcc_enuNullPointr;
	}/*end of else of if(Add_pu32Register != NULL)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuConfigurePLLM(u8 Copy_u8PLLM, puint32_t Add_pu32Register)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if the input is between 2 and 63 it will be valid otherwise it is not valid*/
	if((Copy_u8PLLM > 1) & (Copy_u8PLLM < 64))
	{
		/*Check if the pointer is not NULL*/
		if(Add_pu32Register != NULL)
		{
			(*Add_pu32Register) |= Copy_u8PLLM;
		}/*end of if(Add_pu32Register != NULL)*/
		else
		{
			/*Set Rcc_enuNullPointr to Loc_enuReturnStatus as the pointer is pointing to NULL*/
			Loc_enuReturnStatus = Rcc_enuNullPointr;
		}/*end of else of if(Add_pu32Register != NULL)*/

	}/*end of if((Copy_u8PLLM > 1) & (Copy_u8PLLM < 64))*/
	else
	{
		/*Set Rcc_enuPLLFactorsError to Loc_enuReturnStatus as the input prescaler value is out of range*/
		Loc_enuReturnStatus = Rcc_enuPLLFactorsError;
	}/*end of else of if((Copy_u8PLLM > 1) & (Copy_u8PLLM < 64))*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuConfigurePLLN(u16 Copy_u16PLLN, puint32_t Add_pu32Register)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if the input value is from 192 to 432 otherwise it is invalid*/
	if((Copy_u16PLLN > 191) & (Copy_u16PLLN < 433))
	{
		/*Check if the pointer is pointing to NULL or not*/
		if(Add_pu32Register != NULL)
		{
			/*Add the value to the register value
			 * Shift by 6 as the N prescaler starts from bit 6
			 * */
			(*Add_pu32Register) |= (Copy_u16PLLN << SIX);
		}
		else
		{
			/*Set Rcc_enuNullPointr to Loc_enuReturnStatus as the pointer is pointing to NULL*/
			Loc_enuReturnStatus = Rcc_enuNullPointr;
		}
	}/*end of if((Copy_u16PLLN > 191) & (Copy_u16PLLN < 433))*/
	else
	{
		/*Set Rcc_enuPLLFactorsError to Loc_enuReturnStatus as the input value is out of the range*/
		Loc_enuReturnStatus = Rcc_enuPLLFactorsError;
	}/*end of else of if((Copy_u16PLLN > 191) & (Copy_u16PLLN < 433))*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuConfigurePLLP(u8 Copy_u8PLLP, puint32_t Add_pu32Register)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if the pointer is pointing to NUll or not*/
	if(Add_pu32Register != NULL)
	{
		/*Switch on the input value to and OR the value mask with the register*/
		switch(Copy_u8PLLP)
		{
			case TWO:
			{
				(*Add_pu32Register) &= PLLP2MASKC;
				break;
			}
			case FOUR:
			{
				(*Add_pu32Register) &= PLLP2MASKC;
				(*Add_pu32Register) |= PLLP4MASKS;
				break;
			}
			case SIX:
			{
				(*Add_pu32Register) &= PLLP2MASKC;
				(*Add_pu32Register) |= PLLP6MASKS;
				break;
			}
			case EIGHT:
			{
				(*Add_pu32Register) &= PLLP2MASKC;
				(*Add_pu32Register) |= PLLP8MASKS;
				break;
			}
			default:
			{
				/*Set Rcc_enuPLLFactorsError to Loc_enuReturnStatus as the input value is invalid*/
				Loc_enuReturnStatus = Rcc_enuPLLFactorsError;
			}
		}
	}/*end of if(Add_pu32Register != NULL)*/
	else
	{
		/*Set Rcc_enuNullPointr to Loc_enuReturnStatus as the pointer is pointing to NULl*/
		Loc_enuReturnStatus = Rcc_enuNullPointr;
	}/*end of else of if(Add_pu32Register != NULL)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuConfigurePLLQ(u8 Copy_u8PLLQ, puint32_t Add_pu32Register)
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if the input value is in the range or not 2 to 15*/
	if((Copy_u8PLLQ > 1) & (Copy_u8PLLQ < 16))
	{
		/*Check if the pointer is pointing to NULL*/
		if(Add_pu32Register != NULL)
		{
			/*Add the value to the register value
			 * Shift by 6 as the N prescaler starts from bit 24
			 * */
			(*Add_pu32Register) |= (Copy_u8PLLQ << TWENTYFOUR);
		}/*end of if(Add_pu32Register != NULL)*/
		else
		{
			/*Set Rcc_enuNullPointr to Loc_enuReturnStatus as the pointer is pointing to NULL*/
			Loc_enuReturnStatus = Rcc_enuNullPointr;
		}/*end of else of if(Add_pu32Register != NULL)*/

	}/*end of if((Copy_u8PLLQ > 1) & (Copy_u8PLLQ < 16))*/
	else
	{
		/*Set Rcc_enuPLLFactorsError to Loc_enuReturnStatus as the input value is out of the range*/
		Loc_enuReturnStatus = Rcc_enuPLLFactorsError;
	}/*end of else of if((Copy_u8PLLQ > 1) & (Copy_u8PLLQ < 16))*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuControlSystemClockHSIOn()
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;
	/*Loc_u8TimeOut is used as a timeout counter to make sure that the operation is done or not.*/
	u8 Loc_u8TimeOut = 50;
	/*Loc_CompareValue is used to check if the HSI is ready or not*/
	volatile uint32_t Loc_CompareValue = 0;

    /*Set the HSION bit (the first bit in RCC_CR)*/
    RCC_CR |= SYSCLK_HSION;

    /*Read the HSI ready bit to check if it is ready or not*/
    Loc_CompareValue = (SYSCLK_HSIRDY & RCC_CR);
    while((Loc_u8TimeOut > 0) && (Loc_CompareValue == 0x2))
	{
    	/*Reduce the Loc_u8TimeOut by 1 and reread the HSI ready bit to recheck*/
    	Loc_u8TimeOut -= 1;
    	Loc_CompareValue = (SYSCLK_HSIRDY & RCC_CR);
	}/*end of while((Loc_u8TimeOut > 0) && (Loc_CompareValue == 0x2))*/

    /*Check if the while loop was broken by the HSI ready bit value*/
    if(Loc_u8TimeOut != 0)
    {
    	//Do Nothing. Done.
    }/*end of if(Loc_u8TimeOut != 0)*/
    else
    {
    	/*
    	 * As the while loop was broken by the Loc_u8TimeOut or by
    	 * Loc_enuReturnStatus is set to Rcc_enuOnReadyError
    	 */
    	Loc_enuReturnStatus = Rcc_enuOnReadyError;
    }/*end of else of if(Loc_u8TimeOut != 0)*/

    /*return the return status result*/
    return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuControlSystemClockHSEOn()
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;
	/*Loc_u8TimeOut is used as a timeout counter to make sure that the operation is done or not.*/
	u8 Loc_u8TimeOut = 50;
	/*Loc_CompareValue is used to check if the HSE is ready or not*/
	volatile uint32_t Loc_CompareValue = 0;

	//Set the HSEON bit (the 16th bit in RCC_CR)
	RCC_CR |= SYSCLK_HSEON;

	/*Read the HSE ready bit to check if it is ready or not*/
	Loc_CompareValue = (SYSCLK_HSERDY & RCC_CR);
	while((Loc_u8TimeOut > 0) && (Loc_CompareValue != SYSCLK_HSERDY))
	{
		/*Reduce the Loc_u8TimeOut by 1 and reread the HSE ready bit to recheck*/
		Loc_u8TimeOut -= 1;
		Loc_CompareValue = (SYSCLK_HSERDY & RCC_CR);
	}/*end of while((Loc_u8TimeOut > 0) && (Loc_CompareValue != SYSCLK_HSERDY))*/

	/*Check if the while loop was broken by the HSE ready bit value*/
	if(Loc_u8TimeOut != 0)
	{
		//Do Nothing. Done.
	}/*end of if(Loc_u8TimeOut != 0)*/
	else
	{
		/*
		 * As the while loop was broken by the Loc_u8TimeOut or by
		 * Loc_enuReturnStatus is set to Rcc_enuOnReadyError
		 */
		Loc_enuReturnStatus = Rcc_enuOnReadyError;
	}/*end of else of if(Loc_u8TimeOut != 0)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuControlSystemClockPLLOn()
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;
	/*Loc_u8TimeOut is used as a timeout counter to make sure that the operation is done or not.*/
	u8 Loc_u8TimeOut = 50;
	/*Loc_CompareValue is used to check if the PLL is ready or not*/
	volatile uint32_t Loc_CompareValue = 0;
	//Set the PLLON bit (the 24th bit in RCC_CR)
	RCC_CR |= SYSCLK_PLLON;

	/*Read the PLL ready bit to check if it is ready or not*/
	Loc_CompareValue = (SYSCLK_PLLRDY & RCC_CR);
	while((Loc_u8TimeOut > 0) && (Loc_CompareValue != SYSCLK_PLLRDY))
	{
		/*Reduce the Loc_u8TimeOut by 1 and reread the PLL ready bit to recheck*/
		Loc_u8TimeOut -= 1;
		Loc_CompareValue = (SYSCLK_PLLRDY & RCC_CR);
	}/*end of while((Loc_u8TimeOut > 0) && (Loc_CompareValue != SYSCLK_PLLRDY))*/

	/*Check if the while loop was broken by the PLL ready bit value*/
	if(Loc_u8TimeOut != 0)
	{
		//Do Nothing. Done.
	}/*end of if(Loc_u8TimeOut != 0)*/
	else
	{
		/*
		 * As the while loop was broken by the Loc_u8TimeOut or by
		 * Loc_enuReturnStatus is set to Rcc_enuOnReadyError
		 */
		Loc_enuReturnStatus = Rcc_enuOnReadyError;
	}/*end of else of if(Loc_u8TimeOut != 0)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuControlSystemClockHSIOff()
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if HSI is the system Clock then it can not be done.*/
	if((RCC_CFGR & SWSMASK) == 0x0)
	{
		/*Loc_enuReturnStatus is set to Rcc_enuOffFailedError as it can not be done.*/
		Loc_enuReturnStatus = Rcc_enuOffFailedError;
	}/*end of if((RCC_CFGR & SWSMASK) == 0x0)*/

	//Check if PLL is the system Clock and HSI is the source
	//for it then it can not be done.
	//PLLSRCMASK is mask for bit 22 in RCC_PLLCFGR PLL source.
	else if (((RCC_CFGR & SWSMASK) == 0x8) && ((RCC_PLLCFGR & PLLSRCHSEMASK) == 0x0))
	{
		/*Loc_enuReturnStatus is set to Rcc_enuOffFailedError as it can not be done.*/
		Loc_enuReturnStatus = Rcc_enuOffFailedError;
	}/*end of else if of if((RCC_CFGR & SWSMASK) == 0x0)*/

	else
	{
		//Clear the HSION bit in RCC_CR
		RCC_CR &= SYSCLK_HSIOFF;
		//Done
	}/*end of else of if((RCC_CFGR & SWSMASK) == 0x0)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuControlSystemClockHSEOff()
{
	/* Loc_enuReturnStatus is the return result and contains the error value*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if HSE is the system Clock then it can not be done.*/
	if((RCC_CFGR & SWSMASK) == 0x4)
	{
		/*Loc_enuReturnStatus is set to Rcc_enuOffFailedError as it can not be done.*/
		Loc_enuReturnStatus = Rcc_enuOffFailedError;
	}/*end of if((RCC_CFGR & SWSMASK) == 0x4)*/

	/*Check if PLL is the system Clock and HSE is the source
	* for it then it can not be done.
	* PLLSRCMASK is mask for bit 22 in RCC_PLLCFGR PLL source.
	*/
	else if (((RCC_CFGR & SWSMASK) == 0x8) && (RCC_PLLCFGR & PLLSRCHSEMASK))
	{
		/*Loc_enuReturnStatus is set to Rcc_enuOffFailedError as it can not be done.*/
		Loc_enuReturnStatus = Rcc_enuOffFailedError;
	}/*end of else if of if((RCC_CFGR & SWSMASK) == 0x4)*/

	else
	{
		//Clear the HSEON bit in RCC_CR
		RCC_CR &= SYSCLK_HSEOFF;
		//Done
  	}/*end of else of if((RCC_CFGR & SWSMASK) == 0x4)*/

	/*return the return status result*/
	return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuControlSystemClockPLLOff()
{
	/* Loc_enuReturnStatus is the return result and contains the error value.*/
	Rcc_tenuErrorStatus Loc_enuReturnStatus = Rcc_enuOk;

	/*Check if PLL is the system Clock then it can not be done.*/
	if((RCC_CFGR & SWSMASK) == 0x8)
	{
		/*Loc_enuReturnStatus is set to Rcc_enuOffFailedError as it can not be done.*/
		Loc_enuReturnStatus = Rcc_enuOffFailedError;
	}/*end of if((RCC_CFGR & SWSMASK) == 0x8)*/

	else
	{
		/*Clear the PLLON bit in RCC_CR*/
		RCC_CR &= SYSCLK_PLLOFF;
		//Done
	}/*end of else of if((RCC_CFGR & SWSMASK) == 0x8)*/
	/*return the return status result*/
	return Loc_enuReturnStatus;
}

