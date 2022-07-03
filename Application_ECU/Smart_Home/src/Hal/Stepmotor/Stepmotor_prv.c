/*
 * Stepmotor_prv.c
 *
 *  Created on: Apr 24, 2022
 *      Author: Michael_Safwat
 */

#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "../../Services/Sched/Sched.h"
#include "../../Hal/Led/Led.h"
#include "../../Hal/Led/Led_cfg.h"
#include "Stepmotor.h"
#include "Stepmotor_prv.h"
#include "Stepmotor_cfg.h"


/*Stepmotor_u8Direction is used to indicate the direction and it is changed by the application file*/
extern volatile u8 Stepmotor_u8Direction;

/*Stepmotor_u16Steps is the number of steps to turn and it is changed by the application file*/
extern volatile u16 Stepmotor_u16Steps;

/*Stepmotor_u8TaskFlag is used as an indicator for the task to be enabled or not*/
extern volatile u8 Stepmotor_u8TaskFlag;

/*Stepmotor_u8MotorIndex is used to indicate which motor to be on the window or the door*/
extern volatile u8 Stepmotor_u8MotorIndex;

/*Stepmotors is used to hold the ports and pins of every Stepper motor*/
extern const Stepmotor_cfg_t Stepmotors[NUM_OF_STEPMOTOR];

/*
 * Stepmotor_Task is used to rotate the motor number of steps in the specified direction.
 *
 * Input: It takes no inputs.
 *
 * Return: It returns nothing.
 */
void Stepmotor_Task(void)
{
	/*Loc_u16StepCounter is used to count the number of steps*/
	static u16 Loc_u16StepCounter = ZERO;

	/*Loc_enuTaskSteps is used to hold the state of the task*/
	static Stepmotor_tenuTaskSteps Loc_enuTaskSteps = Stepmotor_enuStep0;

	if(Stepmotor_u8TaskFlag == ZERO)
	{
		/*Do nothing*/
	}
	else
	{
		/*Check which type of code*/
#if STEPMOTOR_STEP == STEPMOTOR_HALFSTEP

		/*Check the direction*/
		if(Stepmotor_u8Direction == STEPMOTOR_CLOCKWISE)
		{
			/*Switch on the states*/
			switch(Loc_enuTaskSteps)
			{
				case Stepmotor_enuStep0:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep1;

					/*On the A coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortA, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinA, GPIO_HIGH);

					/*On the D coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortD, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinD, GPIO_HIGH);


					break;
				}/*end of case Stepmotor_enuStep0*/

				case Stepmotor_enuStep1:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep2;

					/*Off the D coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortD, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinD, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep1*/


				case Stepmotor_enuStep2:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep3;

					/*On the B coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortB, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinB, GPIO_HIGH);


					break;
				}/*end of case Stepmotor_enuStep2*/


				case Stepmotor_enuStep3:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep4;

					/*Off the A coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortA, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinA, GPIO_LOW);



					break;
				}/*end of case Stepmotor_enuStep3*/


				case Stepmotor_enuStep4:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep5;

					/*On the C coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortC, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinC, GPIO_HIGH);


					break;
				}/*end of case Stepmotor_enuStep4*/


				case Stepmotor_enuStep5:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep6;

					/*Off the B coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortB, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinB, GPIO_LOW);


					break;
				}/*end of case Stepmotor_enuStep5*/


				case Stepmotor_enuStep6:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep7;

					/*On the D coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortD, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinD, GPIO_HIGH);


					break;
				}/*end of case Stepmotor_enuStep6*/

				case Stepmotor_enuStep7:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep8;

					/*Off the C coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortC, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinC, GPIO_LOW);


					break;
				}/*end of case Stepmotor_enuStep7*/

				default:
				{
					/*Do nothing*/
					break;
				}/*end of default*/

			}/*end of switch(Loc_enuTaskSteps)*/

		}/*end of if(Stepmotor_u8Direction == STEPMOTOR_CLOCKWISE)*/
		else
		{
			/*Switch on the states*/
			switch(Loc_enuTaskSteps)
			{
				case Stepmotor_enuStep0:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep1;

					/*On the A coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortA, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinA, GPIO_HIGH);

					/*On the D coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortD, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinD, GPIO_HIGH);

					break;
				}/*end of case Stepmotor_enuStep0*/

				case Stepmotor_enuStep1:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep2;

					/*Off the A coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortA, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinA, GPIO_LOW);


					break;
				}/*end of case Stepmotor_enuStep1*/


				case Stepmotor_enuStep2:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep3;

					/*On the C coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortC, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinC, GPIO_HIGH);


					break;
				}/*end of case Stepmotor_enuStep2*/


				case Stepmotor_enuStep3:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep4;

					/*Off the D coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortD, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinD, GPIO_LOW);


					break;
				}/*end of case Stepmotor_enuStep3*/


				case Stepmotor_enuStep4:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep5;

					/*On the B coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortB, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinB, GPIO_HIGH);

					break;
				}/*end of case Stepmotor_enuStep4*/


				case Stepmotor_enuStep5:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep6;

					/*Off the C coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortC, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinC, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep5*/


				case Stepmotor_enuStep6:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep7;

					/*On the A coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortA, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinA, GPIO_HIGH);

					break;
				}/*end of case Stepmotor_enuStep6*/

				case Stepmotor_enuStep7:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep8;

					/*Off the B coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortB, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinB, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep7*/

				default:
				{
					/*Do nothing*/
					break;
				}/*end of default*/


			}/*end of switch(Loc_enuTaskSteps)*/

		}/*end of else of if(Stepmotor_u8Direction == STEPMOTOR_CLOCKWISE)*/

		/*Check if all the steps is done reset the variables*/
		if(Loc_enuTaskSteps == Stepmotor_enuStep8)
		{
			/*Reset the state variable*/
			Loc_enuTaskSteps = Stepmotor_enuStep0;

			/*Increase the steps counter*/
			Loc_u16StepCounter++;

			/*Check if the number of steps equal to the required*/
			if(Loc_u16StepCounter == Stepmotor_u16Steps)
			{
				/*Reset the steps counter*/
				Loc_u16StepCounter = ZERO;

				/*Disable the task*/
				Stepmotor_u8TaskFlag = ZERO;

			}/*end of if(Loc_u16StepCounter == Stepmotor_u16Steps)*/
			else
			{
				/*Do nothing*/
			}/*end of else of if(Loc_u16StepCounter == Stepmotor_u16Steps)*/

		}/*end of if(Loc_enuTaskSteps == Stepmotor_enuStep8)*/
		else
		{
			/*Do nothing*/
		}/*end of else of if(Loc_enuTaskSteps == Stepmotor_enuStep8)*/

#else

		/*Check the direction*/
		if(Stepmotor_u8Direction == STEPMOTOR_CLOCKWISE)
		{
			/*Switch on the states*/
			switch(Loc_enuTaskSteps)
			{
				case Stepmotor_enuStep0:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep1;

					/*On the A coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortA, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinA, GPIO_HIGH);

					/*Off the D coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortD, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinD, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep0*/

				case Stepmotor_enuStep1:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep2;

					/*On the B coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortB, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinB, GPIO_HIGH);

					/*Off the A coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortA, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinA, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep1*/


				case Stepmotor_enuStep2:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep3;

					/*On the C coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortC, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinC, GPIO_HIGH);

					/*Off the B coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortB, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinB, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep2*/


				case Stepmotor_enuStep3:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep4;

					/*On the D coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortD, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinD, GPIO_HIGH);

					/*Off the C coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortC, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinC, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep3*/

				default:
				{
					/*Do nothing*/
					break;
				}/*end of default*/


			}/*end of switch(Loc_enuTaskSteps)*/

		}/*end of if(Stepmotor_u8Direction == STEPMOTOR_CLOCKWISE)*/
		else
		{
			/*Switch on the states*/
			switch(Loc_enuTaskSteps)
			{
				case Stepmotor_enuStep0:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep1;

					/*On the D coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortD, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinD, GPIO_HIGH);

					/*Off the A coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortA, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinA, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep0*/

				case Stepmotor_enuStep1:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep2;

					/*On the C coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortC, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinC, GPIO_HIGH);

					/*Off the D coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortD, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinD, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep1*/


				case Stepmotor_enuStep2:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep3;

					/*On the B coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortB, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinB, GPIO_HIGH);

					/*Off the C coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortC, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinC, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep2*/


				case Stepmotor_enuStep3:
				{
					/*Change the step to the next one*/
					Loc_enuTaskSteps = Stepmotor_enuStep4;

					/*On the A coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortA, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinA, GPIO_HIGH);

					/*Off the B coil pin*/
					gpio_setPinValue(Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PortB, Stepmotors[Stepmotor_u8MotorIndex].Stepmotor_PinB, GPIO_LOW);

					break;
				}/*end of case Stepmotor_enuStep3*/

				default:
				{
					/*Do nothing*/
					break;
				}/*end of default*/


			}/*end of switch(Loc_enuTaskSteps)*/

		}/*end of else of if(Stepmotor_u8Direction == STEPMOTOR_CLOCKWISE)*/

		/*Check if all the steps is done reset the variables*/
		if(Loc_enuTaskSteps == Stepmotor_enuStep4)
		{
			/*Reset the state variable*/
			Loc_enuTaskSteps = Stepmotor_enuStep0;

			/*Increase the steps counter*/
			Loc_u16StepCounter++;

			/*Check if the number of steps equal to the required*/
			if(Loc_u16StepCounter == Stepmotor_u16Steps)
			{
				/*Reset the steps counter*/
				Loc_u16StepCounter = ZERO;

				/*Disable the task*/
				Stepmotor_u8TaskFlag = ZERO;

			}/*end of if(Loc_u16StepCounter == Stepmotor_u16Steps)*/
			else
			{
				/*Do nothing*/
			}/*end of else of if(Loc_u16StepCounter == Stepmotor_u16Steps)*/

		}/*end of if(Loc_enuTaskSteps == Stepmotor_enuStep4)*/
		else
		{
			/*Do nothing*/
		}/*end of else of if(Loc_enuTaskSteps == Stepmotor_enuStep4)*/

#endif

	}/*end of else of if(Stepmotor_u8TaskFlag == ZERO)*/
}


