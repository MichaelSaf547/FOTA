/*
 * Stepmotor_cfg.c
 *
 *  Created on: Jun 23, 2022
 *      Author: Michael_Safwat
 */


#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "Stepmotor.h"
#include "Stepmotor_cfg.h"

const Stepmotor_cfg_t Stepmotors[NUM_OF_STEPMOTOR] =
{
	[STEPMOTOR_WINDOW] = {
		.Stepmotor_PortA = GPIO_PORTB,
		.Stepmotor_PinA = GPIO_PIN0,

		.Stepmotor_PortB = GPIO_PORTB,
		.Stepmotor_PinB = GPIO_PIN1,

		.Stepmotor_PortC = GPIO_PORTB,
		.Stepmotor_PinC = GPIO_PIN2,

		.Stepmotor_PortD = GPIO_PORTB,
		.Stepmotor_PinD = GPIO_PIN10,
	},
//
//	[STEPMOTOR_DOOR] = {
//		.Stepmotor_PortA = GPIO_PORTB,
//		.Stepmotor_PinA = GPIO_PIN12,
//
//		.Stepmotor_PortB = GPIO_PORTB,
//		.Stepmotor_PinB = GPIO_PIN13,
//
//		.Stepmotor_PortC = GPIO_PORTB,
//		.Stepmotor_PinC = GPIO_PIN14,
//
//		.Stepmotor_PortD = GPIO_PORTB,
//		.Stepmotor_PinD = GPIO_PIN15,
//	}

};

