/*
 * RCC.h
 *
 *  Created on: July 1, 2022
 *      Author: FOTA | ITI_42
 */

#ifndef RCC_H_
#define RCC_H_


//************************new types**************************//

//*************************Defines***************************//
#define Sysclk_HSI 0
#define Sysclk_HSE 1
#define Sysclk_PLL 2

#define Sysclk_ret_NOK 0
#define Sysclk_ret_OK 1

#define Sysclk_mode_ON 1
#define Sysclk_mode_OFF 0

#define Sysclk_status_Rdy 1
#define Sysclk_status_NRdy 0

#define Src_HSI 0xFFBFFFFF
#define Src_HSE 0x00400000

#define PLL_OK 1
#define PLL_NOK 0
#define PLLP2 0
#define PLLP4 1
#define PLLP6 2
#define PLLP8 3

#define Path_AHBP 0
#define AHBP_0 0x00000000
#define AHBP_2 0x00000080
#define AHBP_4 0x00000090
#define AHBP_8 0x000000A0
#define AHBP_16 0x000000B0
#define AHBP_64 0x000000C0
#define AHBP_128 0x000000D0
#define AHBP_256 0x000000E0
#define AHBP_512 0x000000F0
#define Path_APB1 1
#define APB1_0 0x00000000
#define APB1_2 0x00001000
#define APB1_4 0x00001400
#define APB1_8 0x00001800
#define APB1_16 0x00001C00
#define Path_APB2 2
#define APB2_0 0x00000000
#define APB2_2 0x00008000
#define APB2_4 0x0000A000
#define APB2_8 0x0000C000
#define APB2_16 0x0000E000

#define Peripheral_GPIOA 0
#define Peripheral_GPIOB 1
#define Peripheral_GPIOC 2
#define Peripheral_GPIOD 3
#define Peripheral_GPIOE 4
#define Peripheral_GPIOH 5
#define Peripheral_CRC 6
#define Peripheral_DMA1 7
#define Peripheral_DMA2 8
#define Peripheral_OTG 9
#define Peripheral_TIM2 10
#define Peripheral_TIM3 11
#define Peripheral_TIM4 12
#define Peripheral_TIM5 13
#define Peripheral_WWDG 14
#define Peripheral_SPI2 15
#define Peripheral_SPI3 16
#define Peripheral_USART2 17
#define Peripheral_I2C1 18
#define Peripheral_I2C2 19
#define Peripheral_I2C3 20
#define Peripheral_PWR 21
#define Peripheral_TIM1 22
#define Peripheral_USART1 23
#define Peripheral_USART6 24
#define Peripheral_ADC1 25
#define Peripheral_SDIO 26
#define Peripheral_SPI1 27
#define Peripheral_SPI4 28
#define Peripheral_SYSCFG 29
#define Peripheral_TIM9 30
#define Peripheral_TIM10 31
#define Peripheral_TIM11 32
#define Peripheral_mode_ON 1
#define Peripheral_mode_OFF 0
//*******************function Prototypes*********************//

/**
 * Purpose : Select the Clock of system ... it takes 1 argument and
 * return error type
 *
 * Arguments : Sysclk_type and it could be one of
 * 			   Sysclk_HSI , Sysclk_HSE , Sysclk_PLL
 *
 * Return : it return ok if clock selected right and
 * 		 	return Nok if clock not selected
 * 		 	Sysclk_ret_NOK , Sysclk_ret_OK
 */
u8 Select_Sysclk(u8 Sysclk_type);


//Arg : Sysclk_x , Sysclk_mode_x
/**
 * Purpose : control the clock On or Off ... it takes 2 arguments
 * Sysclk_type and mode of Sysclk
 *
 * Arguments : Sysclk_type and it could be one those (Sysclk_HSI , Sysclk_HSE , Sysclk_PLL)
 * 			   Sysclk_mode and it could be one of those (Sysclk_mode_ON , Sysclk_mode_OFF)
 *
 * Return : Not accessed (Void)
 */
u8 Control_Sysclk(u8 Sysclk_type,u8 Sysclk_mode);


//Return : Sysclk_status_x , Arg: Sysclk_x
/**
 * Purpose : Get the status of sysclk ... it takes 1 argument : Sysclk_type and
 * return the status of that clock
 *
 * Arguments : Sysclk_type : (Sysclk_HSI , Sysclk_HSE , Sysclk_PLL)
 *
 * Return : Sysclk_Status_x : (Sysclk_status_Rdy , Sysclk_status_NRdy)
 */
u8 Status_Sysclk(u8 Sysclk_type);



//Return : PLL_x , Arg : Src_x,value of M,N,Q,PLLPx
/**
 * Purpose : Configure the PLL parameters .. select the source of PLL , M , N , Q , P
 *
 * Arguments : Src (Src_HSI , Src_HSE)
 * 			   M range 2 -> 63
 * 			   N range 192 -> 432
 * 			   Q range 2 -> 15
 * 			   P (PLLP2 , PLLP4 , PLLP6 , PLLP8)
 *
 * Return : Error State if PLL is ON OR no before configuration
 * 			PLL_OK , PLL_NOK
 */
u8 Config_PLL(u32 Src,u8 M,u32 N,u8 Q,u8 P);



//Arg : Path_x,value
/**
 * Purpose : Configure the prescaler of paths , it takes the path and the value of the prescaler
 * 			 and doesn't return thing ( Void )
 *
 * Arguments : Path (Path_AHBP , Path_APB1 , Path_APB2)
 * 			   value of prescaler
 *
 * Return : No return value (Void)
 *
 *
 */
void Config_Prescaler(u8 Path,u32 value);



//Arg : Peripheral_x , Peripheral_mode_x
/**
 * Purpose : Control the peripheral clock On Or OFF , this fucntion take 2 argumets .. the peripheral and the mode of clock
 * 			 and it doesn't return anything (VOID)
 *
 * Arguments : Peripheral_x , Peripheral_mode_x
 *
 * Return : Nothing (Void)
 */
void Control_Peripheral_Clk(u8 Peripheral,u8 Peripheral_mode);


/**
 * Purpose : To know the used System clock
 * 			 this function take no arguments and return the sysclk type
 *
 * Arguments : No Arguments (Void)
 *
 * Return : Sysclk_HSI , Sysclk_HSE , Sysclk_PLL
 *
 */
u8 Used_Sysclk(void);

#endif /* RCC_H_ */
