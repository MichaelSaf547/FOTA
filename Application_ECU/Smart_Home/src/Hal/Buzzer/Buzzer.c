



#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "Buzzer.h"
#include "Buzzer_cfg.h"

/*Extern Buzzer_au8Pins to use the pins.*/
extern const Buzzer_cfg_t Buzzer_Pins[NUM_OF_BUZZER];

/*
 * Buzzer_enuInit is used to initialize the Gpio pins for the buzzer
 *
 * Input: It takes nothing.
 *
 * Return: It returns the error states of the function.
 */
Buzzer_tenuErrorStatus Buzzer_enuInit(void)
{
	Buzzer_tenuErrorStatus Loc_enuReturnStatus = Buzzer_enuOk;

	/*Loc_u8ForCounter is used as a counter for the for loop.*/
	u8 Loc_u8ForCounter = ZERO;

	/*Loc_enuGpioConfig is used to configure the pins of the Buzzer*/
	gpioPinCfg_t Loc_enuGpioConfig;

	/*Loc_enuGpioErrorStatus is used to check the initialization of the pins.*/
	gpioErrorStatus_t Loc_enuGpioErrorStatus = gpio_enuOk;

	/*Loop over the buzzer pins to initialize them.*/
	for(Loc_u8ForCounter = ZERO; Loc_u8ForCounter < NUM_OF_BUZZER; ++Loc_u8ForCounter)
	{
		/*Read from the buzzer pins array into the local variable for initialization.*/
		Loc_enuGpioConfig.port = Buzzer_Pins[Loc_u8ForCounter].Buzzer_Port;
		Loc_enuGpioConfig.pin = Buzzer_Pins[Loc_u8ForCounter].Buzzer_Pin;
		Loc_enuGpioConfig.mode = GPIO_PIN_OUT_PP;
		Loc_enuGpioConfig.speed = GPIO_PIN_SPEED2;

		/*Initialize the pin.*/
		Loc_enuGpioErrorStatus = gpio_initPin(& Loc_enuGpioConfig);

		/*Check if the function returned Okay or not.*/
		if(Loc_enuGpioErrorStatus != gpio_enuOk)
		{
			/*Set Buzzer_enuNotOk to Loc_enuReturnStatus as the pin failed to be initialized.*/
			Loc_enuReturnStatus = Buzzer_enuNotOk;

			/*Break from the loop.*/
			break;
		}
	}

	/*Return the error status to the caller function.*/
	return Loc_enuReturnStatus;
}

/*
 * Buzzer_enuOn is used to switch on a Buzzer
 *
 * Input: It takes one input, Copy_u8BuzzerId which is one of the Buzzer in the Buzzer_cfg.h file
 *
 * Return: It returns the error status of the function.
 */
Buzzer_tenuErrorStatus Buzzer_enuOn(u8 Copy_u8BuzzerId)
{
	Buzzer_tenuErrorStatus Loc_enuReturnStatus = Buzzer_enuOk;
	if (Copy_u8BuzzerId >= NUM_OF_BUZZER)
	{
		Loc_enuReturnStatus = Buzzer_enuNotOk;
	}
	else
	{
		gpioErrorStatus_t Loc_enuGpioError = gpio_enuOk;
		Loc_enuGpioError = gpio_setPinValue(Buzzer_Pins[Copy_u8BuzzerId].Buzzer_Port, Buzzer_Pins[Copy_u8BuzzerId].Buzzer_Pin, GPIO_HIGH);
		if(Loc_enuGpioError == gpio_enuOk)
		{
			//Do Nothing.  Done.
		}
		else
		{
			/*Error handling*/
			Loc_enuReturnStatus = Buzzer_enuNotOk;
		}
	}
	return Loc_enuReturnStatus;
}

/*
 * Buzzer_enuOn is used to switch off a Buzzer
 *
 * Input: It takes one input, Copy_u8BuzzerId which is one of the Buzzer in the Buzzer_cfg.h file
 *
 * Return: It returns the error status of the function.
 */
Buzzer_tenuErrorStatus Buzzer_enuOff(u8 Copy_u8BuzzerId)
{
	Buzzer_tenuErrorStatus Loc_enuReturnStatus = Buzzer_enuOk;
	if (Copy_u8BuzzerId >= NUM_OF_BUZZER)
	{
		Loc_enuReturnStatus = Buzzer_enuNotOk;
	}
	else
	{
		gpioErrorStatus_t Loc_enuGpioError = gpio_enuOk;
		Loc_enuGpioError = gpio_setPinValue(Buzzer_Pins[Copy_u8BuzzerId].Buzzer_Port, Buzzer_Pins[Copy_u8BuzzerId].Buzzer_Pin, GPIO_LOW);
		if(Loc_enuGpioError == gpio_enuOk)
		{
			//Do Nothing.  Done.
		}
		else
		{
			/*Error handling*/
			Loc_enuReturnStatus = Buzzer_enuNotOk;
		}
	}
	return Loc_enuReturnStatus;
}

