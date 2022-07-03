/*
 * Gpio.c
 *
 *  Created on: July 1, 2022
 *      Author: FOTA || ITI_42
 */

#include"Bits_utils.h"
#include"Gpio.h"

typedef struct
{
	u32 MODER;				//0x00 Offset
	u32 OTYPER;             //0x04 Offset
	u32 OSPEEDR;            //0x08 Offset
	u32 PUPDR;              //0x0C Offset
	u32 IDR;                //0x10 Offset
	u32 ODR;                //0x14 Offset
	u32 BSRR;               //0x18 Offset
	u32 LCKR;               //0x1C Offset
	u32 AFRL;               //0x20 Offset
	u32 AFRH;               //0x24 Offset

}Gpio_t;


//**************************Define Masks**********************//
#define GPIO_MODER			0b00011000
#define GPIO_OTYPER			0b00000100
#define GPIO_PUPDR			0b00000011


/**
 * Purpose : Configure the Pin mode and speed and pin number and the port .. this function take 1 argument
 * 			 from new data type GpioPinCfg_t and return Error status
 *
 * Arguments : Pointer to GpioPinCnfg_t variable
 *
 * Return : Error Status
 */
u8 Gpio_Init_Pin(GpioPinCfg_t* val)
{
	u8 Error_Status = GPIO_OK;
	u32 temp;
	Gpio_t* const Gpio_x =(Gpio_t* const) val->Port;
	u8 MODER = (val->Mode&GPIO_MODER)>>3;
	u8 OTYPER = (val->Mode&GPIO_OTYPER)>>2;
	u8 PUPDR = val->Mode&GPIO_PUPDR;

	//Set MODE On MODER Register
	temp = Gpio_x->MODER;
	temp &= ~(3<<(val->Pin*2));
	temp |= (MODER<<(val->Pin*2));
	Gpio_x->MODER = temp;

	//Set OTYPER
	temp = Gpio_x->OTYPER;
	temp &= ~(1<<val->Pin);
	temp |= (OTYPER<<val->Pin);
	Gpio_x->OTYPER = temp;

	//Set PUPDR
	temp = Gpio_x->PUPDR;
	temp &= ~(3<<(val->Pin*2));
	temp |= (PUPDR<<(val->Pin*2));
	Gpio_x->PUPDR = temp;

	//Set Speed
	temp = Gpio_x->OSPEEDR;
	temp &= ~(3<<val->Pin);
	temp |= ((val->Speed)<<(val->Pin*2));
	Gpio_x->OSPEEDR = temp;

	return Error_Status;
}

/**
 * Purpose : Sending data ( high or Low ) to the pin with value .. this function takes 2 arguments
 * 			 Pointer to GpioPinCfg_t and u8 variable
 *
 * Arguments : Pointer to GpioPinCfg_t
 * 			   u8 value >>> PIN_x
 *
 * Return : Error Status
 */
u8 Gpio_Set_Pin_Value(u32 Port ,u8 Pin,u8 value)
{
	u8 Error_Status = GPIO_OK;
	Gpio_t* const Gpio_x =(Gpio_t* const) Port;
	if(Pin > 15)
	{
		Error_Status = GPIO_NOK;
	}
	else
	{
		switch(value)
		{
		case PIN_LOW:
			CLR_BIT(Gpio_x->BSRR,Pin);
			SET_BIT(Gpio_x->BSRR,(Pin+16));
			break;

		case PIN_HIGH:
			CLR_BIT(Gpio_x->BSRR,(Pin+16));
			SET_BIT(Gpio_x->BSRR,Pin);
			break;
		}
	}

	return Error_Status;
}


/**
 * Purpose : Get value of custom pin .. this fucntion takes 2 arguments
 * 			 Pointer to GpioPinCfg_t and Pointer to u8 to put the data on it
 *
 * Arguments : Pointer to GpioPinCfg_t , pu8
 *
 * Return : Error Status
 */
u8 Gpio_Get_Pin_Value(u32 Port ,u8 Pin,pu8 value)
{
	u8 Error_Status = GPIO_OK;
	Gpio_t* const Gpio_x =(Gpio_t* const) Port;
	if(Pin > 15)
	{
		Error_Status = GPIO_NOK;
	}
	else
	{
		*value = GET_BIT(Gpio_x->IDR,Pin);
	}
	return Error_Status;
}


