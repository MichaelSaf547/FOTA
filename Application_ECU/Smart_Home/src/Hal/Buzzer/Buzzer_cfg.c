/*
 * Buzzer_cfg.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Michael_Safwat
 */


#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "Buzzer_cfg.h"


/*Choose interface pins from Gpio_Pin_0 -> PIN15D*/
/*Choose interface ports from GPIO_PORTA -> Gpio_Port_H*/

/*
 * Set the values of the pins and the ports and do not change the state of the two other values (Mode and speed).
 */

const Buzzer_cfg_t Buzzer_Pins[NUM_OF_BUZZER] = {
		[BUZZER_ALARM] =
		{
				.Buzzer_Pin = GPIO_PIN13,
				.Buzzer_Port = GPIO_PORTC
		}

};
