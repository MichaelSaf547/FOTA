/*
 * Stepmotor.c
 *
 *  Created on: Apr 20, 2022
 *      Author: Michael_Safwat
 */


#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "../../Services/Sched/Sched.h"
#include "Stepmotor.h"
#include "Stepmotor_prv.h"
#include "Stepmotor_cfg.h"

/*Stepmotor_u8Direction is used to indicate the direction and it is changed by the application file*/
volatile u8 Stepmotor_u8Direction = ZERO;

/*Stepmotor_u16Steps is the number of steps to turn and it is changed by the application file*/
volatile u16 Stepmotor_u16Steps = ZERO;

/*Stepmotor_u8TaskFlag is used as an indicator for the task to be enabled or not*/
volatile u8 Stepmotor_u8TaskFlag = ZERO;

/*Stepmotor_u8MotorIndex is used to indicate which motor to be on the window or the door*/
volatile u8 Stepmotor_u8MotorIndex = ZERO;

/*Stepmotors has the pins of the stepper motors.*/
extern const Stepmotor_cfg_t Stepmotors[NUM_OF_STEPMOTOR];

/*************************************************************************************************/
/*										Function Implementation									 */
/*************************************************************************************************/

/*
 * Stepmotor_vidInit is used to add the step motor task into the scheduler
 *
 * Input: It takes no inputs.
 *
 * Return: It returns nothing.
 */
void Stepmotor_vidInit(void)
{
	Runnable_t Loc_run;

	/*Loc_u8ForCounter is used as a counter for the for loop.*/
	u8 Loc_u8ForCounter = ZERO;

	/*Loc_enuGpioConfig is used to configure the pins of the Stepper motor*/
	gpioPinCfg_t Loc_enuGpioConfig;

	/*Loop over the Stepper motors pins to initialize them.*/
	for(Loc_u8ForCounter = ZERO; Loc_u8ForCounter < NUM_OF_STEPMOTOR; ++Loc_u8ForCounter)
	{
		/*Read from the buzzer pins array into the local variable for initialization.*/
		Loc_enuGpioConfig.port = Stepmotors[Loc_u8ForCounter].Stepmotor_PortA;
		Loc_enuGpioConfig.pin = Stepmotors[Loc_u8ForCounter].Stepmotor_PinA;
		Loc_enuGpioConfig.mode = GPIO_PIN_OUT_PP;
		Loc_enuGpioConfig.speed = GPIO_PIN_SPEED2;

		/*Initialize the pin.*/
		gpio_initPin(& Loc_enuGpioConfig);

		/*Read from the buzzer pins array into the local variable for initialization.*/
		Loc_enuGpioConfig.port = Stepmotors[Loc_u8ForCounter].Stepmotor_PortB;
		Loc_enuGpioConfig.pin = Stepmotors[Loc_u8ForCounter].Stepmotor_PinB;
		Loc_enuGpioConfig.mode = GPIO_PIN_OUT_PP;
		Loc_enuGpioConfig.speed = GPIO_PIN_SPEED2;

		/*Initialize the pin.*/
		gpio_initPin(& Loc_enuGpioConfig);

		/*Read from the buzzer pins array into the local variable for initialization.*/
		Loc_enuGpioConfig.port = Stepmotors[Loc_u8ForCounter].Stepmotor_PortC;
		Loc_enuGpioConfig.pin = Stepmotors[Loc_u8ForCounter].Stepmotor_PinC;
		Loc_enuGpioConfig.mode = GPIO_PIN_OUT_PP;
		Loc_enuGpioConfig.speed = GPIO_PIN_SPEED2;

		/*Initialize the pin.*/
		gpio_initPin(& Loc_enuGpioConfig);

		/*Read from the buzzer pins array into the local variable for initialization.*/
		Loc_enuGpioConfig.port = Stepmotors[Loc_u8ForCounter].Stepmotor_PortD;
		Loc_enuGpioConfig.pin = Stepmotors[Loc_u8ForCounter].Stepmotor_PinD;
		Loc_enuGpioConfig.mode = GPIO_PIN_OUT_PP;
		Loc_enuGpioConfig.speed = GPIO_PIN_SPEED2;

		/*Initialize the pin.*/
		gpio_initPin(& Loc_enuGpioConfig);

	}

	Loc_run.CyclicTimems = STEPMOTORTASKPERIODICTIME;

	Loc_run.cbfP = Stepmotor_Task;

	Loc_run.FirstDelay = STEPMOTORFIRSTDALAY;

	Sched_RegisterRunnable(&Loc_run, STEPMOTORTASKPRIORITY);
}

