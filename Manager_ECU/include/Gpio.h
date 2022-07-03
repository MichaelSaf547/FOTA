/*
 * Gpio.h
 *
 *  Created on: July 1, 2022
 *      Author: FOTA || ITI_42
 */

#ifndef GPIO_H_
#define GPIO_H_

//************************New types************************//
/**
 * gpiopincfg_t New type of structure to control the pins of Gpio
 * 				this structure have 4 parameters
 * 				1)mode to config pin mode
 * 				2)Speed to config pin speed
 * 				3)Pin to config pin number
 * 				4)Port to select gpio port
 */
typedef struct {
	u8 Mode;
	u8 Speed;
	u8 Pin;
	u32 Port;
}GpioPinCfg_t;

//***********************Defines**************************//

//Modes of pins
#define MODE_INPUT_FLOAT		0x00
#define MODE_INPUT_PULLUP		0x01
#define MODE_INPUT_PULLDOWN		0x02


#define MODE_OUTPUT_OD			0x0C
#define MODE_OUTPUT_OD_PU		0x0D
#define MODE_OUTPUT_OD_PD       0x0E
#define MODE_OUTPUT_PP          0x08
#define MODE_OUTPUT_PP_PU       0x09
#define MODE_OUTPUT_PP_PD       0x0A

#define MODE_AF_PP				0x10
#define MODE_AF_PP_PU           0x11
#define MODE_AF_PP_PD           0x12
#define MODE_AF_OD              0x14
#define MODE_AF_OD_PU           0x15
#define MODE_AF_OD_PD           0x16

#define MODE_ANALOG				0x18

//Speed
#define SPEED_LOW				0
#define SPEED_MEDIUM			1
#define SPEED_HIGH				2
#define SPEED_VERYHIGH			3

//Pin_Num
#define PIN_0       0
#define PIN_1		1
#define PIN_2       2
#define PIN_3       3
#define PIN_4       4
#define PIN_5       5
#define PIN_6       6
#define PIN_7       7
#define PIN_8       8
#define PIN_9       9
#define PIN_10      10
#define PIN_11      11
#define PIN_12      12
#define PIN_13      13
#define PIN_14      14
#define PIN_15		15

//Port
#define GPIO_A		0x40020000
#define GPIO_B		0x40020400
#define GPIO_C		0x40020800
#define GPIO_D		0x40020C00
#define GPIO_E		0x40021000
#define GPIO_H		0x40021C00

//Pin_Values
#define PIN_HIGH 	1
#define PIN_LOW 	0

//Error Status
#define GPIO_OK		1
#define GPIO_NOK	0



//*********************Function Prototypes*********************//

/**
 * Purpose : Configure the Pin mode and speed and pin number and the port .. this function take 1 argument
 * 			 from new data type GpioPinCfg_t and return Error status
 *
 * Arguments : Pointer to GpioPinCnfg_t variable
 *
 * Return : Error Status
 */
u8 Gpio_Init_Pin(GpioPinCfg_t* val);


/**
 * Purpose : Sending data ( high or Low ) to the pin with value .. this function takes 2 arguments
 * 			 Pointer to GpioPinCfg_t and u8 variable
 *
 * Arguments : Pointer to GpioPinCfg_t
 * 			   u8 value >>> PIN_x
 *
 * Return : Error Status
 */
u8 Gpio_Set_Pin_Value(u32 Port ,u8 Pin,u8 value);


/**
 * Purpose : Get value of custom pin .. this fucntion takes 2 arguments
 * 			 Pointer to GpioPinCfg_t and Pointer to u8 to put the data on it
 *
 * Arguments : Pointer to GpioPinCfg_t , pu8
 *
 * Return : Error Status
 */
u8 Gpio_Get_Pin_Value(u32 Port ,u8 Pin,pu8 value);

#endif /* GPIO_H_ */
