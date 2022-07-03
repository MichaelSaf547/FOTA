/*
 * Dcmotor_cfg.c
 *
 *  Created on: Apr 16, 2022
 *      Author: Michael_Safwat
 */

#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "Dcmotor_cfg.h"

/*Choose interface pins from Gpio_Pin_0 -> PIN15D*/
/*Choose interface ports from GPIO_PORTA -> Gpio_Port_H*/

/*
 * Set the values of the pins and the ports and do not change the state of the two other values (Mode and speed).
 */

const DCmotor_cfg_t DCMotor_Pins[NUM_OF_DCMOTORS] = {
		[DCMOTOR_1] =
		{
				.DCmotor_Pin1 = GPIO_PIN12,
				.DCmotor_Port1 = GPIO_PORTC,
				.DCmotor_Pin2 = GPIO_PIN12,
				.DCmotor_Port2 = GPIO_PORTA
		}
};
