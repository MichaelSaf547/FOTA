

#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "Led.h"
#include "Led_cfg.h"

const Led_cfg_t Leds[NUM_OF_LEDS] = 
{
	[LED_ALARM] = {
		.Led_u8Port = GPIO_PORTA,
		.Led_u8PinNum = GPIO_PIN7,
		.Led_u8ActiveState = LEDACTIVESTATE_HIGH,
		.Led_OType = OTYPE_PP
	},

	[LED_LIGHT] = {
		.Led_u8Port = GPIO_PORTC,
		.Led_u8PinNum = GPIO_PIN10,
		.Led_u8ActiveState = LEDACTIVESTATE_HIGH,
		.Led_OType = OTYPE_PP
	}

};
