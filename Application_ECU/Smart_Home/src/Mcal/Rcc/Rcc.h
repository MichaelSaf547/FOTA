/*
 * Rcc.h
 *
 *  Created on: Mar 9, 2022
 *      Author: Michael Safwat
 */

#ifndef RCC_H_
#define RCC_H_

/*
* Types Definition
*/

typedef enum
{
	Rcc_enuOk,
	Rcc_enuPeripheralIDError,
	Rcc_enuBusError,
	Rcc_enuPrecalerError,
	Rcc_enuPLLSourceError,
	Rcc_enuPLLFactorsError,
	Rcc_enuSysClkError,
	Rcc_enuOnOffError,
	Rcc_enuOnReadyError,
	Rcc_enuOffFailedError,
	Rcc_enuNullPointr,
	Rcc_enuPLLIsOn,
	Rcc_enuMCOType

} Rcc_tenuErrorStatus;


/*
* Defines
*/

#define SYSCLK_HSI        0x00000000
#define SYSCLK_HSE        0x00000001
#define SYSCLK_PLL        0x00000002

#define OFF               0
#define ON                1

#define PLLSOURCEHSI      0
#define PLLSOURCEHSE      1

#define AHBBUS            0
#define APB1BUS           1
#define APB2BUS           2

#define NOTREADY		  0
#define READY			  1


/*
* Peripheral Ids
*/

#define DMA2      0
#define DMA1      1
#define CRC       2
#define GPIOA     3
#define GPIOB     4
#define GPIOC     5
#define GPIOD     6
#define GPIOE     7
#define GPIOH     8

#define OTGFS     9

#define PWR       10
#define I2C3      11
#define I2C2      12
#define I2C1      13
#define USART_2    14
#define SPI3      15
#define SPI2      16
#define WWDG      17
#define TIM5      18
#define TIM4      19
#define TIM3      20
#define TIM2      21

#define TIM11     22
#define TIM10     23
#define TIM9      24
#define SYSCFG    25
#define SPI4      26
#define SPI1      27
#define SDIO      28
#define ADC1      29
#define USART_6    30
#define USART_1    31
#define TIM1      32


/*
* Values for Prescaler
*/

#define ONE						1
#define TWO						2
#define FOUR					4
#define EIGHT					8
#define SIXTEEN					16
#define SIXTYFOUR				64
#define ONEHUNTWNTYEIGHT		128
#define TWOHUNFIFTYSIX			256
#define FIVEHUNTWELVE			512


/*
 * MOC options
 */

#define MCO1					0
#define MCO2					1

#define MCO1SOURCEC				0xFF9FFFFF
#define MCO1SOURCESHI			0x00000000
#define MCO1SOURCELSE			0x00200000
#define MCO1SOURCEHSE			0x00400000
#define MCO1SOURCEPLL			0x00600000

#define MCO1PRESCALC			0x00000000
#define MCO1PRESCAL1			0x00000000
#define MCO1PRESCAL2			0x04000000
#define MCO1PRESCAL3			0x05000000
#define MCO1PRESCAL4			0x06000000
#define MCO1PRESCAL5			0x07000000

#define MCO2SOURCEC				0x3FFFFFFF
#define MCO2SOURCESS			0x00000000
#define MCO2SOURCEPLLI2S		0x40000000
#define MCO2SOURCEHSE			0x80000000
#define MCO2SOURCEPLL			0xC0000000

#define MCO2PRESCALC			0x00000000
#define MCO2PRESCAL1			0x00000000
#define MCO2PRESCAL2			0x20000000
#define MCO2PRESCAL3			0x28000000
#define MCO2PRESCAL4			0x30000000
#define MCO2PRESCAL5			0x38000000

/*
* Functions Prototype
*/


/*
* Rcc_enuSelectSysClock: is used to set the system clock using one of the options:
*                        1- SYSCLK_HSI
*                        2- SYSCLK_HSE
*                        3- SYSCLK_PLL
*                        But the source must be On and Ready before using it.
*                        The function returns the error status of the function:
*                        1- Rcc_enuOk.					Done.
*                        2- Rcc_enuSysClkError			Failed as the input source is not an option.
*                        3- Rcc_enuOnReadyError			Failed as the source is not Ready.
*/

Rcc_tenuErrorStatus Rcc_enuSelectSysClock(u8 Copy_u8SysClk);




/*
* Rcc_enuGetSysClock: is used to get the system clock:
*                        First input: is an pointer to get the result in it and it will be one of the next options:
*                        1- SYSCLK_HSI
*                        2- SYSCLK_HSE
*                        3- SYSCLK_PLL
*                        The function returns the error status of the function:
*                        1- Rcc_enuOk.					Done.
*                        2- Rcc_enuNullPointr			Failed as the pointer is pointing to NULL.
*/

Rcc_tenuErrorStatus Rcc_enuGetSysClock(pu8 Add_pu8SysClk);


/*
 * Rcc_enuSysClockOnOff: is used to switch a clock on or off:
 * 						First input:
 * 								1- SYSCLK_HSI
 * 								2- SYSCLK_HSE
 * 								3- SYSCLK_PLL
 * 						Second input:
 * 								1- OFF
 * 								2- ON
 * 						The function returns the error status of the function:
 * 						1- Rcc_enuOk					Done.
 * 						2- Rcc_enuOnOffError			Failed as the input is neither OFF nor ON.
 * 						3- Rcc_enuSysClkError			Failed as the input is not an option of clocks.
 * 						4- Rcc_enuOnReadyError			Failed as the clock is not getting Ready.
 * 						5- Rcc_enuOffFailedError		Failed as the clock is the source clock so it can not be switched off.
 * */
Rcc_tenuErrorStatus Rcc_enuSysClockOnOff(u8 Copy_u8SysClk, u8 Copy_u8OnOff);



/*
 * Rcc_enuGetStatusClock: is used to check if the clock is ready or not:
 * 						First input:
 * 								1- SYSCLK_HSI
 * 								2- SYSCLK_HSE
 * 								3- SYSCLK_PLL
 * 						Second input:
 * 								A pointer to get the status back either READY or NOTREADY.
 * 						The function returns the error status of the function:
 * 						1- Rcc_enuOk					Done.
 * 						2- Rcc_enuNullPointr			Failed as the pointer is pointing to NULL.
 * 						3- Rcc_enuSysClkError			Failed as the input is not an option of clocks.
 */

Rcc_tenuErrorStatus Rcc_enuGetStatusClock(u8 Copy_u8SysClk, pu8 Add_pu8ClockStatus);



/*
 * Rcc_enuConfigurePLL: is used to configure the PLL source:
 * 						First input:
 * 								1- PLLSOURCEHSI
 * 								2- PLLSOURCEHSE
 * 						Second input:
 * 								The value of the M prescaler.(2 -> 63)
 * 						Third input:
 * 								The value of the N prescaler.(192 -> 432)
 * 						Fourth input:
 * 								The value of the P prescaler.(2-4-6-8)
 * 						Fivth input:
 * 								The value of the Q prescaler.(2 -> 15)
 * 						The function returns the error status of the function:
 * 						1- Rcc_enuOk					Done.
 * 						2- Rcc_enuPLLIsOn				Failed as the PLL is on and it must be OFF to be configured.
 * 						3- Rcc_enuPLLSourceError		Failed as the input as a source for the PLL is not an option.
 *						4- Rcc_enuNullPointr			Failed as something in the middle change the variable that holds the register value to NULL.
 *						5- Rcc_enuPLLFactorsError		Failed as the factor value is not eligible.
 */

Rcc_tenuErrorStatus Rcc_enuConfigurePLL(u8 Copy_u8PLLSource, u8 Copy_u8M, u16 Copy_u16N, u8 Copy_u8P, u8 Copy_u8Q);

/*
 * Rcc_enuPrescalerBus: is used to configure the prescaler of the buses:
 * 						First input:
 * 								1- AHBBUS
 * 								2- APB1BUS
 * 								3- APB2BUS
 * 						Second input:
 * 								The value of the prescaler.
 * 								For AHBBUS    (ONE-TWO-FOUR-EIGHT-SIXTEEN-SIXTYFOUR-ONEHUNTWNTYEIGHT-TWOHUNFIFTYSIX-FIVEHUNTWELVE)
 * 								For APB1BUS   (ONE-TWO-FOUR-EIGHT-SIXTEEN)
 * 								For APB2BUS  (ONE-TWO-FOUR-EIGHT-SIXTEEN)
 * 						The function returns the error status of the function:
 * 						1- Rcc_enuOk					Done.
 * 						2- Rcc_enuBusError				Failed as the input is not an option.
 * 						3- Rcc_enuPrecalerError			Failed as the prescaler value is not an option.
 */


Rcc_tenuErrorStatus Rcc_enuPrescalerBus(u8 Copy_u8Bus, u16 Copy_u16BusPrescaler);


/*
 * Rcc_enuEnableClockPeripheral: is used to enable the clock of a peripheral:
 * 						One of the above options.
 * 						The function returns the error status of the function:
 * 						1- Rcc_enuOk					Done.
 * 						2- Rcc_enuPeripheralIDError		Failed as the peripheral is not an option.
 */


Rcc_tenuErrorStatus Rcc_enuEnableClockPeripheral(u8 Copy_u8PeripheralId);


/*
 * Rcc_enuDisableClockPeripheral: is used to disable the clock of a peripheral:
 * 						One of the above options.
 * 						The function returns the error status of the function:
 * 						1- Rcc_enuOk					Done.
 * 						2- Rcc_enuPeripheralIDError		Failed as the peripheral is not an option.
 */


Rcc_tenuErrorStatus Rcc_enuDisableClockPeripheral(u8 Copy_u8PeripheralId);


/*
 * Rcc_enuConfiugreMCO: is used to configure the MCO either 1 or 2
 * Note: You MUST configure the MCO bit as AF Output to work.
 * Inputs:  1- Copy_u8MCO1OR2 is to choose between MCO1 and MCO2
 * 			2- Copy_u32MCOSource is used to choose the source of the clock to the MCO and it has the following options:
 * 			for MOC1:  MCO1SOURCESHI						for MCO2:  MCO2SOURCESS
 *                     MCO1SOURCELSE                                   MCO2SOURCEPLLI2S
 *                     MCO1SOURCEHSE                                   MCO2SOURCEHSE
 *                     MCO1SOURCEPLL                                   MCO2SOURCEPLL
 *
 *          3- Copy_u32MCOPrescaler is used to choose the prescaler of the clock and it has the following options:
 *         	for MCO1:  MCO1PRESCAL1							for MCO2:  MCO2PRESCAL1
 *         	           MCO1PRESCAL2                                    MCO2PRESCAL2
 *         	           MCO1PRESCAL3                                    MCO2PRESCAL3
 *         	           MCO1PRESCAL4                                    MCO2PRESCAL4
 *         	           MCO1PRESCAL5                                    MCO2PRESCAL5
 *
 *			The function returns the error status of the function:
 *			1- Rcc_enuOk								Done.
 *			2- Rcc_enuMCOType							The MCO type is not correct.
 */

Rcc_tenuErrorStatus Rcc_enuConfiugreMCO(u8 Copy_u8MCO1OR2, u32 Copy_u32MCOSource, u32 Copy_u32MCOPrescaler);



#endif /* RCC_H_ */
