/*
 * Lcd_cfg.c
 *
 *  Created on: Apr 14, 2022
 *      Author:
 */


#include "../Lib/Std_types.h"
#include "../Lib/Bit_utils.h"
#include "../Mcal/Gpio/Gpio.h"
#include "Lcd_cfg.h"
#include "Lcd.h"

/*Choose interface pins from Gpio_Pin_0 -> PIN15D*/
/*Choose interface ports from GPIO_PORTA -> Gpio_Port_H*/

/*
 * Set the values of the pins and the ports and do not change the state of the two other values (Mode and speed).
 */

const Lcd_cfg_t Lcd_Pins[LCD_PINS] = {
		[LCD_ENABLE_PIN] =
		{
				.Lcd_Pin = GPIO_PIN5,
				.Lcd_Port = GPIO_PORTB
		},

		[LCD_READ_WRITE_PIN] =
		{
				.Lcd_Pin = GPIO_PIN15,
				.Lcd_Port = GPIO_PORTC
		},

		[LCD_REGISTERSELECT_PIN] =
		{
				.Lcd_Pin = GPIO_PIN14,
				.Lcd_Port = GPIO_PORTC
		},
#if INTERFACE_TYPE == 1
		[LCD_D0_PIN] =
		{
				.Lcd_Pin = GPIO_PIN12,
				.Lcd_Port = GPIO_PORTB
		},

		[LCD_D1_PIN] =
		{
				.Lcd_Pin = GPIO_PIN13,
				.Lcd_Port = GPIO_PORTB
		},

		[LCD_D2_PIN] =
		{
				.Lcd_Pin = GPIO_PIN14,
				.Lcd_Port = GPIO_PORTB
		},

		[LCD_D3_PIN] =
		{
				.Lcd_Pin = GPIO_PIN15,
				.Lcd_Port = GPIO_PORTB
		},
#endif
		[LCD_D4_PIN] =
		{
				.Lcd_Pin = GPIO_PIN6,
				.Lcd_Port = GPIO_PORTB
		},

		[LCD_D5_PIN] =
		{
				.Lcd_Pin = GPIO_PIN7,
				.Lcd_Port = GPIO_PORTB
		},

		[LCD_D6_PIN] =
		{
				.Lcd_Pin = GPIO_PIN8,
				.Lcd_Port = GPIO_PORTB
		},

		[LCD_D7_PIN] =
		{
				.Lcd_Pin = GPIO_PIN9,
				.Lcd_Port = GPIO_PORTB
		}
};





