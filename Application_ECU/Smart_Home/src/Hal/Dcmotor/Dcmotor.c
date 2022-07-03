/*
 * Dcmotor.c
 *
 *  Created on: Apr 16, 2022
 *      Author: Michael_Safwat
 */

#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "Dcmotor.h"
#include "Dcmotor_cfg.h"

/*Extern the motor pins array*/
extern const DCmotor_cfg_t DCMotor_Pins[NUM_OF_DCMOTORS];


/*
 * DCmotor_enuInit is used to initialize the Gpio pins for the DCmotors.
 *
 * Input: It takes nothing.
 *
 * Return: It returns the error states of the function.
 */
Dcmotor_tenuErrorStatus DCmotor_enuInit(void)
{
	Dcmotor_tenuErrorStatus Loc_enuReturnStatus = Dcmotor_enuOk;

	/*Loc_u8ForCounter is used as a counter for the for loop.*/
	u8 Loc_u8ForCounter = ZERO;

	/*Loc_enuGpioConfig is used to configure the pins of the DC motor*/
	gpioPinCfg_t Loc_enuGpioConfig;

	/*Loc_enuGpioErrorStatus is used to check the initialization of the pins.*/
	gpioErrorStatus_t Loc_enuGpioErrorStatus = gpio_enuOk;

	/*Loop over the Motors pins to initialize them.*/
	for(Loc_u8ForCounter = ZERO; Loc_u8ForCounter < NUM_OF_DCMOTORS; ++Loc_u8ForCounter)
	{
		/*Read from the Dc motor pins array into the local variable for initialization. (Left pin)*/
		Loc_enuGpioConfig.port = DCMotor_Pins[Loc_u8ForCounter].DCmotor_Port1;
		Loc_enuGpioConfig.pin = DCMotor_Pins[Loc_u8ForCounter].DCmotor_Pin1;
		Loc_enuGpioConfig.mode = GPIO_PIN_OUT_OD;
		Loc_enuGpioConfig.speed = GPIO_PIN_SPEED2;

		/*Initialize the pin.*/
		Loc_enuGpioErrorStatus = gpio_initPin(& Loc_enuGpioConfig);

		/*Check if the function returned Okay or not.*/
		if(Loc_enuGpioErrorStatus != gpio_enuOk)
		{
			/*Set Buzzer_enuNotOk to Loc_enuReturnStatus as the pin failed to be initialized.*/
			Loc_enuReturnStatus = Dcmotor_enuNotOk;

			/*Break from the loop.*/
			break;
		}

		/*Read from the buzzer pins array into the local variable for initialization. (Right pin)*/
		Loc_enuGpioConfig.port = DCMotor_Pins[Loc_u8ForCounter].DCmotor_Port2;
		Loc_enuGpioConfig.pin = DCMotor_Pins[Loc_u8ForCounter].DCmotor_Pin2;
		Loc_enuGpioConfig.mode = GPIO_PIN_OUT_PP;
		Loc_enuGpioConfig.speed = GPIO_PIN_SPEED2;

		/*Initialize the pin.*/
		Loc_enuGpioErrorStatus = gpio_initPin(& Loc_enuGpioConfig);

		/*Check if the function returned Okay or not.*/
		if(Loc_enuGpioErrorStatus != gpio_enuOk)
		{
			/*Set Buzzer_enuNotOk to Loc_enuReturnStatus as the pin failed to be initialized.*/
			Loc_enuReturnStatus = Dcmotor_enuNotOk;

			/*Break from the loop.*/
			break;
		}
	}

	/*Return the error status to the caller function.*/
	return Loc_enuReturnStatus;
}


/*
 * Dcmotor_enuOnMotor is used to turn the motor on.
 *
 * Input: It takes two inputs, 1- Copy_u8MotorNumber is the motor number as specified in the Dcmotor_cfg.h file.
 * 							   2- Copy_u8MotorDirection is the direction of the motor and it has two options:
 * 							   							1- DCMOTOR_DIR_LEFT
 * 							   							2- DCMOTOR_DIR_RIGHT
 *
 * 	Return: It returns the error status of the function and has two options:
 * 			1- Dcmotor_enuOk, if the function completed its turn correctly.
 * 			2- Dcmotor_enuNotOk, if the function failed to turn the motor on due two two things:
 * 								1- Motor number is not correct.
 * 								2- Motor direction is not correct.
 */

Dcmotor_tenuErrorStatus Dcmotor_enuOnMotor(u8 Copy_u8MotorNumber, u8 Copy_u8MotorDirection)
{
	/*Loc_enuReturnStatus is used to hold the error status of the function.*/
	Dcmotor_tenuErrorStatus Loc_enuReturnStatus = Dcmotor_enuOk;

	/*Check if the motor number is in range or not.*/
	if(Copy_u8MotorNumber < NUM_OF_DCMOTORS)
	{
		/*Check the given direction is it valid or not.*/
		if(Copy_u8MotorDirection == DCMOTOR_DIR_LEFT)
		{
			/*Set the pins in the left direction*/

			gpio_setPinValue(DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Port1, DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Pin1, GPIO_HIGH);
			gpio_setPinValue(DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Port2, DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Pin2, GPIO_LOW);

		}/*end of if(Copy_u8MotorDirection == DCMOTOR_DIR_LEFT)*/
		else if(Copy_u8MotorDirection == DCMOTOR_DIR_RIGHT)
		{
			/*Set the pins in the right direction*/
			gpio_setPinValue(DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Port1, DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Pin1, GPIO_LOW);
			gpio_setPinValue(DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Port2, DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Pin2, GPIO_HIGH);

		}/*end of else if(Copy_u8MotorDirection == DCMOTOR_DIR_RIGHT)*/
		else
		{
			/*Set Dcmotor_enuNotOk to Loc_enuReturnStatus as the given motor direction is not valid.*/
			Loc_enuReturnStatus = Dcmotor_enuNotOk;

		}/*end of else of if(Copy_u8MotorDirection == DCMOTOR_DIR_LEFT)*/

	}/*end of if(Copy_u8MotorNumber < NUM_OF_DCMOTORS)*/
	else
	{
		/*Set Dcmotor_enuNotOk to Loc_enuReturnStatus as the given motor number is out of range.*/
		Loc_enuReturnStatus = Dcmotor_enuNotOk;

	}/*end of else of if(Copy_u8MotorNumber < NUM_OF_DCMOTORS)*/

	/*Return the error status to the caller function.*/
	return Loc_enuReturnStatus;
}


/*
 * Dcmotor_enuOffMotor is used to turn the motor off.
 *
 * Input: It takes one input, 1- Copy_u8MotorNumber is the motor number as specified in the Dcmotor_cfg.h file.
 *
 *
 * 	Return: It returns the error status of the function and has two options:
 * 			1- Dcmotor_enuOk, if the function completed its turn correctly.
 * 			2- Dcmotor_enuNotOk, if the function failed to turn the motor off due two one thing:
 * 								1- Motor number is not correct.
 */
Dcmotor_tenuErrorStatus Dcmotor_enuOffMotor(u8 Copy_u8MotorNumber)
{
	/*Loc_enuReturnStatus is used to hold the error status of the function.*/
	Dcmotor_tenuErrorStatus Loc_enuReturnStatus = Dcmotor_enuOk;

	/*Check if the motor number is in range or not.*/
	if(Copy_u8MotorNumber < NUM_OF_DCMOTORS)
	{
		/*Set the pins to turn off the motor*/
		gpio_setPinValue(DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Port1, DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Pin1, GPIO_LOW);
		gpio_setPinValue(DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Port2, DCMotor_Pins[Copy_u8MotorNumber].DCmotor_Pin2, GPIO_LOW);

	}/*end of if(Copy_u8MotorNumber < NUM_OF_DCMOTORS)*/
	else
	{
		/*Set Dcmotor_enuNotOk to Loc_enuReturnStatus as the given motor number is out of range.*/
		Loc_enuReturnStatus = Dcmotor_enuNotOk;

	}/*end of else of if(Copy_u8MotorNumber < NUM_OF_DCMOTORS)*/

	/*Return the error status to the caller function.*/
	return Loc_enuReturnStatus;
}
