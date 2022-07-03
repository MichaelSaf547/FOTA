/*
 * Calc_prv.c
 *
 *  Created on: Apr 14, 2022
 *      Author:
 */



#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Flash/Flash.h"
#include "../../Mcal/Scb/SCB.h"
#include "../../Mcal/Usart/Usart.h"
#include "../../Hal/Keypad/Keypad.h"
#include "../../Hal/Stepmotor/Stepmotor.h"
#include "../../Hal/Stepmotor/Stepmotor_cfg.h"
#include "../../Hal/Led/Led.h"
#include "../../Hal/Led/Led_cfg.h"
#include "../../Hal/Buzzer/Buzzer.h"
#include "../../Hal/Buzzer/Buzzer_cfg.h"
#include "../../Hal/Dcmotor/Dcmotor.h"
#include "../../Hal/Dcmotor/Dcmotor_cfg.h"
#include "Smart_Home.h"
#include "Smart_Home_prv.h"
#include "../../Lcd/Lcd.h"
#include "diag/Trace.h"

/*App_au8Password is the password for logging in.*/
static const u8 App_au8Password[FOUR] = {'2', '2', '2', '2'};

/*App_enuStates is used to save the states of the Application task*/
static App_tenuStates App_enuStates = App_enuStart;

/*Stepmotor_u8Direction is used to indicate the direction and it is changed by the application file*/
extern volatile u8 Stepmotor_u8Direction;

/*Stepmotor_u16Steps is the number of steps to turn and it is changed by the application file*/
extern volatile u16 Stepmotor_u16Steps;

/*Stepmotor_u8TaskFlag is used as an indicator for the task to be enabled or not*/
extern volatile u8 Stepmotor_u8TaskFlag;

/*Stepmotor_u8MotorIndex is used to indicate which motor to be on the window or the door*/
extern volatile u8 Stepmotor_u8MotorIndex;


extern USARTHandel_t Loc_uart;

/*
 * App_Task is the application task to check every step in the application
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */

void App_Task(void)
{
	/*Switch over the states to find what to do.*/
	switch(App_enuStates)
	{
		case App_enuStart:
		{
			Start_Process();
			break;
		}/*end of case App_enuStart*/

		case App_enuLoggedIn:
		{
			Logging_Success();
			break;
		}/*end of case App_enuLoggedIn*/

		case App_enuLoggedError:
		{
			Logging_Error();
			break;
		}/*end of case App_enuLoggedError*/

		case App_enuWindow:
		{
			Window_Process();
			break;
		}/*end of case App_enuWindow*/

		case App_enuFan:
		{
			Fan_Process();
			break;
		}/*end of case App_enuFan*/

		default:
		{
			break;
		}/*end of default*/

	}/*end of switch(Loc_enuStates)*/
}


/*
 * Start_Process is the process for logging in to the application
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
void Start_Process(void)
{
	/*Loc_u8PasswordCounter is used to count the index of the password*/
	static u8 Loc_u8PasswordCounter = ZERO;

	/*Loc_u8PassCorrectIndicator is used as an indicator for the password is it correct or not.*/
	static u8 Loc_u8PassCorrectIndicator = ZERO;

	/*Loc_u8KeyValue is used to read the key value from the keypad in it.*/
	u8 Loc_u8KeyValue;

	/*Loc_enuStartStates is used to control the states of the start process*/
	static App_tenuStartStates Loc_enuStartStates = App_enuStart0;

	/*Loc_enuKeypadError is used to read a key from the keypad*/
	Keypad_tenuErrorStatus Loc_enuKeypadError = Keypad_enuOk;

	/*Check the state*/
	if(Loc_enuStartStates == App_enuStart0)
	{
		/*Change the start state to move to the next one*/
		Loc_enuStartStates = App_enuStart1;

		/*Display the log in message*/
		Lcd_vidDisplayString("Enter Password", 14, 0, 0);

	}/*end of if(Loc_enuStartStates == App_enuStart0)*/
	else if(Loc_enuStartStates == App_enuStart1)
	{
		/*Change the start state tom move to the next state*/
		Loc_enuStartStates = App_enuStart2;

		/*Go to the second row of the LCD*/
		Lcd_vidGoTo(ONE, ZERO);

	}/*end of else if(Loc_enuStartStates == App_enuStart1)*/
	else
	{
		/*Get a key*/
		Loc_enuKeypadError = Keypad_enuGetKey(&Loc_u8KeyValue);

		/*Check if a key is pressed or not*/
		if(Loc_enuKeypadError == Keypad_enuOk)
		{
			/*Compare the value of the key to the value saved in the index of the password*/
			if(Loc_u8KeyValue == App_au8Password[Loc_u8PasswordCounter])
			{
				/*This key is correct*/
				/*So do nothing*/
			}/*end of if(Loc_u8KeyValue == App_au8Password[Loc_u8PasswordCounter])*/
			else
			{
				/*This key is false in the password*/
				/*Raise the error flag*/
				Loc_u8PassCorrectIndicator = ONE;

			}/*end of else of if(Loc_u8KeyValue == App_au8Password[Loc_u8PasswordCounter])*/

			/*Dispaly one '*' to indicate a key is pressed*/
			Lcd_vidDisplayCharacter(Loc_u8KeyValue);

			/*Increase the password counter*/
			Loc_u8PasswordCounter++;

			/*Check if a four digits are pressed or not yet.*/
			if(Loc_u8PasswordCounter == FOUR)
			{
				/*Check if the password is correct or not*/
				if(Loc_u8PassCorrectIndicator == ONE)
				{
					/*Password is wrong so go to the state of error logging in*/
					App_enuStates = App_enuLoggedError;

					/*Reset the value of the states variable*/
					Loc_enuStartStates = App_enuStart0;

					/*Reset the value of the counter*/
					Loc_u8PasswordCounter = ZERO;

				}/*end of if(Loc_u8PassCorrectIndicator == ONE)*/
				else
				{
					/*Password is correct so go the state of logged in*/
					App_enuStates = App_enuLoggedIn;

					/*Reset the value of the states variable*/
					Loc_enuStartStates = App_enuStart0;

					/*Reset the value of the counter*/
					Loc_u8PasswordCounter = ZERO;

				}/*end of else of if(Loc_u8PassCorrectIndicator == ONE)*/

			}/*end of if(Loc_u8PasswordCounter == FOUR)*/
			else
			{
				/*Do nothing as we still waiting for the rest of the password*/
			}/*end of else of if(Loc_u8PasswordCounter == FOUR)*/

		}/*end of if(Loc_enuKeypadError == Keypad_enuOk)*/
		else
		{
			/*Do nothing*/
		}/*end of else of if(Loc_enuKeypadError == Keypad_enuOk)*/

	}/*end of else of if(Loc_enuStartStates == App_enuStart0)*/

}


/*
 * Logging_Success is the process called if the entered password is correct to control the window and fan.
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
void Logging_Success(void)
{
	/*Loc_enuLoggedState is used to control the states in this process*/
	static App_tenuLoggedInStates Loc_enuLoggedState = App_enuLoggedIn0;

	/*Loc_u8TimerCounter is used as a counter as a delay*/
	static u8 Loc_u8TimerCounter = ZERO;

	/*Loc_u16TimeOut is used to as a counter to time up if the user did not enter any option.*/
	static u16 Loc_u16TimeOut = 300;

	/*Loc_enuKeypad is used to check the return of the function pressed or not*/
	Keypad_tenuErrorStatus Loc_enuKeypad = Keypad_enuOk;

	/*Loc_u8KeypadValue is the pressed key if pressed*/
	u8 Loc_u8KeypadValue;

	/*Switch on the states to know what to do*/
	switch(Loc_enuLoggedState)
	{
		case App_enuLoggedIn0:
		{
			/*Clear the LCD*/
			Lcd_vidSendCommand(ONE);

			/*Open the door for the user to enter*/

			/*Set the direction to Clockwise*/
			Stepmotor_u8Direction = STEPMOTOR_CLOCKWISE;

			/*Calculate the number of steps and save the value in the step motor steps variable*/
			Stepmotor_u16Steps = 128;

			/*Set the index flag to Door so the task open the door.*/
			Stepmotor_u8MotorIndex = STEPMOTOR_DOOR;

			/*Enable the task*/
			Stepmotor_u8TaskFlag = ONE;

			/*Change the state to the next one*/
			Loc_enuLoggedState = App_enuLoggedIn1;

			break;
		}/*end of case App_enuLoggedIn0*/

		case App_enuLoggedIn1:
		{
			/*Check the delay counter if 0 print the string*/
			if(Loc_u8TimerCounter == ZERO)
			{
				/*Display the welcome message*/
				Lcd_vidDisplayString("Welcome ITI", 11, ZERO, TWO);

				/*Increase the delay counter by one*/
				Loc_u8TimerCounter++;

			}/*end of if(Loc_u8TimerCounter == ZERO)*/
			/*Check if the delay counter is 10 break from this state and go to the next state*/
			else if(Loc_u8TimerCounter == 30)
			{
				/*Change the state to the next state and reset the delay counter*/
				Loc_enuLoggedState = App_enuLoggedIn2;

				/*Clear the LCD*/
				Lcd_vidSendCommand(ONE);

				/*Close the door*/

				/*Set the direction to counter Clockwise*/
				Stepmotor_u8Direction = STEPMOTOR_COUNTERCLOCKWISE;

				/*Calculate the number of steps and save the value in the step motor steps variable*/
				Stepmotor_u16Steps = 128;

				/*Set the index flag to Door so the task close the door.*/
				Stepmotor_u8MotorIndex = STEPMOTOR_DOOR;

				/*Enable the task*/
				Stepmotor_u8TaskFlag = ONE;

				/*Reset the value*/
				Loc_u8TimerCounter = ZERO;
			}
			else
			{
				/*Increase the counter*/
				Loc_u8TimerCounter++;

			}/*end of else of if(Loc_u8TimerCounter == ZERO)*/

			break;
		}/*end of case App_enuLoggedIn1*/

		case App_enuLoggedIn2:
		{
			/*Display the first option*/
			Lcd_vidDisplayString("Window: Press 1", 15, 0, 0);

			/*Change the state to the next one*/
			Loc_enuLoggedState = App_enuLoggedIn3;

			break;
		}/*end of case App_enuLoggedIn2*/

		case App_enuLoggedIn3:
		{
			/*Display the second option*/
			Lcd_vidDisplayString("Fan: Press 2", 12, 1, 0);

			/*Change the state to the next one*/
			Loc_enuLoggedState = App_enuLoggedIn4;

			break;
		}/*end of case App_enuLoggedIn3*/

		case App_enuLoggedIn4:
		{
			/*Get key if pressed*/
			Loc_enuKeypad = Keypad_enuGetKey(&Loc_u8KeypadValue);

			/*Check if the return is ok or not*/
			if(Loc_enuKeypad == Keypad_enuOk)
			{
				/*Check if the key is valid or not*/
				if(Loc_u8KeypadValue == '1')
				{
					/*Change the state of the application to window*/
					App_enuStates = App_enuWindow;

					/*Reset the state of the current process to the menu view*/
					Loc_enuLoggedState = App_enuLoggedIn2;

					/*Reset the time out timer*/
					Loc_u16TimeOut = 300;

					/*Clear the LCD*/
					Lcd_vidSendCommand(ONE);

				}/*end of if(Loc_u8KeypadValue == '1')*/
				else if(Loc_u8KeypadValue == '2')
				{
					/*Change the state of the application to fan*/
					App_enuStates = App_enuFan;

					/*Reset the state of the current process to the menu view*/
					Loc_enuLoggedState = App_enuLoggedIn2;

					/*Reset the time out timer*/
					Loc_u16TimeOut = 300;

					/*Clear the LCD*/
					Lcd_vidSendCommand(ONE);

				}/*end of else if(Loc_u8KeypadValue == '2')*/
				else
				{
					/*Decrease the Loc_u16TimeOut timer till reach time out.*/
					Loc_u16TimeOut--;

					/*Wait till a minute elapse*/
					if(Loc_u16TimeOut == ZERO)
					{
						/*Reset the time out timer*/
						Loc_u16TimeOut = 300;

						/*Reset the state of the logging state to the start of it.*/
						Loc_enuLoggedState = App_enuLoggedIn0;

						/*Reset the state of the application to the start state.*/
						App_enuStates = App_enuStart;

						/*Clear the LCD*/
						Lcd_vidSendCommand(ONE);

					}/*end of if(Loc_u16TimeOut == ZERO)*/
					else
					{
						/*Do nothing.*/
					}/*end of else of if(Loc_u16TimeOut == ZERO)*/

				}/*end of else of if(Loc_u8KeypadValue == '1')*/

			}/*end of if(Loc_enuKeypad == Keypad_enuOk)*/
			else
			{
				/*Decrease the Loc_u16TimeOut timer till reach time out.*/
				Loc_u16TimeOut--;

				/*Wait till a minute elapse*/
				if(Loc_u16TimeOut == ZERO)
				{
					/*Reset the time out timer*/
					Loc_u16TimeOut = 300;

					/*Reset the state of the logging state to the start of it.*/
					Loc_enuLoggedState = App_enuLoggedIn0;

					/*Reset the state of the application to the start state.*/
					App_enuStates = App_enuStart;

					/*Clear the LCD*/
					Lcd_vidSendCommand(ONE);

				}/*end of if(Loc_u16TimeOut == ZERO)*/
				else
				{
					/*Do nothing.*/
				}/*end of else of if(Loc_u16TimeOut == ZERO)*/
			}/*end of else of if(Loc_enuKeypad == Keypad_enuOk)*/

			break;
		}/*end of case App_enuLoggedIn4*/


	}/*end of switch(Loc_enuLoggedState)*/
}


/*
 * LoggingError is the process called if the entered password is incorrect to turn the buzzer and toggle a LED.
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
void Logging_Error(void)
{
	/*Loc_enuLoggingErrorState is used to hold the state to know what to do now*/
	static App_tenuLoggingErrorStates Loc_enuLoggingErrorState = App_enuLoggingError0;

	/*Loc_u8LedState is used to save the state of the LED.*/
	static u8 Loc_u8LedState = ZERO;

	/*Switch on the states*/
	switch(Loc_enuLoggingErrorState)
	{
		case App_enuLoggingError0:
		{
			/*Clear the LCD for whatever is coming*/
			Lcd_vidSendCommand(ONE);

			/*Turn the Buzzer ON*/
			Buzzer_enuOn(BUZZER_ALARM);

			/*Turn on the LED*/
			Led_enuSetState(LED_ALARM, LEDSTATE_ON);

			/*Change LED state*/
			Loc_u8LedState = ONE;

			/*Change the state for the next time*/
			Loc_enuLoggingErrorState = App_enuLoggingError1;

			break;
		}/*end of App_enuLoggingError0*/

		case App_enuLoggingError1:
		{

			/*Display that the password is incorrect*/
			Lcd_vidDisplayString("Pass. is Wrong!", 15, 0, 0);

			/*LED is on*/
			/*Turn the LED off and change the state*/
			Led_enuSetState(LED_ALARM, LEDSTATE_OFF);
			Loc_u8LedState = ZERO;

			/*Change the state for the next time*/
			Loc_enuLoggingErrorState = App_enuLoggingError2;

			break;
		}/*end of App_enuLoggingError1*/

		case App_enuLoggingError2:
		{

			/*Toggle the led only*/
			/*Check the LED state either on or off*/
			if(Loc_u8LedState == ZERO)
			{
				/*LED is off*/
				/*Turn the LED on and change the state*/
				Led_enuSetState(LED_ALARM, LEDSTATE_ON);
				Loc_u8LedState = ONE;
			}/*end of if(Loc_u8LedState == ZERO)*/
			else
			{
				/*LED is on*/
				/*Turn the LED off and change the state*/
				Led_enuSetState(LED_ALARM, LEDSTATE_OFF);
				Loc_u8LedState = ZERO;
			}/*end of else of if(Loc_u8LedState == ZERO)*/

			break;
		}/*end of App_enuLoggingError2*/

		default:
		{
			/*Error Handling*/
			break;
		}/*end of defualt*/

	}/*end of switch(Loc_enuLoggingErrorState)*/
}

/*
 * Window_Process is the process called if the user choose window.
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
void Window_Process(void)
{
	/*Loc_enuWindowStates is used to save the state of the window process.*/
	static App_tenuWindowStates Loc_enuWindowStates = App_enuWindow0;

	/*Loc_u8TimerCounter is used as a counter as a delay*/
	static u8 Loc_u8TimerCounter = ZERO;

	/*Loc_u16TimeOut is used to as a counter to time up if the user did not enter any option.*/
	static u16 Loc_u16TimeOut = 300;

	/*Loc_u8WindowValue is used to store the window value from 0 to 100*/
	static u8 Loc_u8WindowValue = ZERO;

	/*Loc_u8NumberOfDigit is used to save the number of the digit that the user entered with a maximum of 3.*/
	static u8 Loc_u8NumberOfDigit = ZERO;

	/*Loc_u8WindowPosition is used to save the window position from 0 to 100*/
	static u8 Loc_u8WindowPosition = ZERO;

	/*Loc_enuKeypad is used to check the return of the function pressed or not*/
	Keypad_tenuErrorStatus Loc_enuKeypad = Keypad_enuOk;

	/*Loc_u8KeypadValue is the pressed key if pressed*/
	u8 Loc_u8KeypadValue;

	/*Switch on the states*/
	switch(Loc_enuWindowStates)
	{
		case App_enuWindow0:
		{
			/*Display the first part of the sentence*/
			Lcd_vidDisplayString("Window percent", 14 , 0, 0);

			/*Change the state to the next state*/
			Loc_enuWindowStates = App_enuWindow1;

			break;
		}/*end of case App_enuWindow0*/

		case App_enuWindow1:
		{
			/*Display the second part of the sentence*/
			Lcd_vidDisplayString("from 0 to 100.", 14 , 1, 0);

			/*Change the state to the next state*/
			Loc_enuWindowStates = App_enuWindow2;

			break;
		}/*end of case App_enuWindow1*/

		case App_enuWindow2:
		{
			/*Check the delay counter if 19 clear the LCD*/
			if(Loc_u8TimerCounter < 19)
			{
				/*Increase the counter*/
				Loc_u8TimerCounter++;

			}/*end of if(Loc_u8TimerCounter < 19)*/
			/*Check if the delay counter is 10 break from this state and go to the next state*/
			else if(Loc_u8TimerCounter == 19)
			{
				/*Clear the LCD*/
				Lcd_vidSendCommand(ONE);

				/*Increase the delay counter by one*/
				Loc_u8TimerCounter++;

			}/*end of else if(Loc_u8TimerCounter == 19)*/
			else
			{
				/*Change the state to the next state*/
				Loc_enuWindowStates = App_enuWindow3;

				/*Display the last part of  the sentence*/
				Lcd_vidDisplayString("Press * to end:", 15 , 0, 0);

				/*Reset the value*/
				Loc_u8TimerCounter = ZERO;

			}/*end of else of if(Loc_u8TimerCounter < 19)*/

			break;
		}/*end of case App_enuWindow2*/

		case App_enuWindow3:
		{
			/*Go to the next line*/
			Lcd_vidGoTo(ONE, ZERO);

			/*Change the state to the next one*/
			Loc_enuWindowStates = App_enuWindow4;

			break;
		}/*end of case App_enuWindow3*/

		case App_enuWindow4:
		{
			/*Get key if pressed*/
			Loc_enuKeypad = Keypad_enuGetKey(&Loc_u8KeypadValue);

			/*Check if the return is okay or not*/
			if(Loc_enuKeypad == Keypad_enuOk)
			{
				/*Check if the key is valid or not*/
				if(Loc_u8KeypadValue >= '0' && Loc_u8KeypadValue <= '9')
				{
					/*Increase the number of digits and check if the number is more than 3 that means wrong input*/
					Loc_u8NumberOfDigit++;

					/*Reset the time out timer*/
					Loc_u16TimeOut = 300;

					if(Loc_u8NumberOfDigit > THREE)
					{
						/*Reset the number of digits*/
						Loc_u8NumberOfDigit = ZERO;

						/*Assume that the input operation is done and go to the next step*/
						/*Set the state of the current process*/
						Loc_enuWindowStates = App_enuWindow5;

					}/*end of if(Loc_u8NumberOfDigit > THREE)*/
					else
					{
						/*Add the value to the variable that hold the percent*/
						Loc_u8WindowValue = Loc_u8WindowValue * ((u8)TEN) + (Loc_u8KeypadValue - '0');

						/*Display the input value on the LCD*/
						Lcd_vidDisplayCharacter(Loc_u8KeypadValue);

						/*Check the value to decide what to do*/
						if(Loc_u8WindowValue <= TEN)
						{
							/*Do nothing*/

						}/*end of if(Loc_u8WindowValue <= TEN)*/
						else if(Loc_u8WindowValue > TEN && Loc_u8WindowValue <= 100)
						{
							/*Insert process is done.*/
							/*Set the state of the current process*/
							Loc_enuWindowStates = App_enuWindow5;

							/*Clear the LCD*/
							Lcd_vidSendCommand(ONE);

							/*Reset the number of digits*/
							Loc_u8NumberOfDigit = ZERO;

						}/*end of else if(Loc_u8WindowValue > TEN && Loc_u8WindowValue <= 100)*/
						else
						{
							/*Invalid input so make it 100*/
							Loc_u8WindowValue = 100;

							/*Set the state of the current process*/
							Loc_enuWindowStates = App_enuWindow5;

							/*Clear the LCD*/
							Lcd_vidSendCommand(ONE);

							/*Reset the number of digits*/
							Loc_u8NumberOfDigit = ZERO;

						}/*end of else of if(Loc_u8WindowValue <= TEN)*/

					}/*end of else of if(Loc_u8NumberOfDigit > THREE)*/

				}/*end of if(Loc_u8KeypadValue >= '0' && Loc_u8KeypadValue <= '9')*/
				else if(Loc_u8KeypadValue == '*')
				{
					/*Insert process is done.*/
					/*Set the state of the current process*/
					Loc_enuWindowStates = App_enuWindow5;

					/*Reset the time out timer*/
					Loc_u16TimeOut = 300;

					/*Clear the LCD*/
					Lcd_vidSendCommand(ONE);

					/*Reset the number of digits*/
					Loc_u8NumberOfDigit = ZERO;

				}/*end of else if(Loc_u8KeypadValue == '*')*/
				else
				{
					/*Decrease the Loc_u16TimeOut timer till reach time out.*/
					Loc_u16TimeOut--;

					/*Wait till a minute elapse*/
					if(Loc_u16TimeOut == ZERO)
					{
						/*Reset the time out timer*/
						Loc_u16TimeOut = 300;

						/*Reset the state of the current process*/
						Loc_enuWindowStates = App_enuWindow0;

						/*Reset the state of the application to the start state.*/
						App_enuStates = App_enuStart;

						/*Clear the LCD*/
						Lcd_vidSendCommand(ONE);

						/*Reset the number of digits*/
						Loc_u8NumberOfDigit = ZERO;

					}/*end of if(Loc_u16TimeOut == ZERO)*/
					else
					{
						/*Do nothing.*/
					}/*end of else of if(Loc_u16TimeOut == ZERO)*/

				}/*end of else of if(Loc_u8KeypadValue >= '0' && Loc_u8KeypadValue <= '9')*/

			}/*end of if(Loc_enuKeypad == Keypad_enuOk)*/
			else
			{
				/*Decrease the Loc_u16TimeOut timer till reach time out.*/
				Loc_u16TimeOut--;

				/*Wait till a minute elapse*/
				if(Loc_u16TimeOut == ZERO)
				{
					/*Reset the time out timer*/
					Loc_u16TimeOut = 300;

					/*Reset the state of the process to the start of it.*/
					Loc_enuWindowStates = App_enuWindow0;

					/*Reset the state of the application to the start state.*/
					App_enuStates = App_enuStart;

					/*Clear the LCD*/
					Lcd_vidSendCommand(ONE);

					/*Reset the number of digits*/
					Loc_u8NumberOfDigit = ZERO;

				}/*end of if(Loc_u16TimeOut == ZERO)*/
				else
				{
					/*Do nothing.*/
				}/*end of else of if(Loc_u16TimeOut == ZERO)*/
			}/*end of else of if(Loc_enuKeypad == Keypad_enuOk)*/

			break;
		}/*end of case App_enuWindow4*/

		case App_enuWindow5:
		{
			/*Open the window by using the stepper motor*/
			/*Check the required value in compare to the current position*/
			if(Loc_u8WindowValue < Loc_u8WindowPosition)
			{
				/*Set the direction to Clockwise*/
				Stepmotor_u8Direction = STEPMOTOR_CLOCKWISE;

				/*Calculate the number of steps and save the value in the step motor steps variable*/
				Stepmotor_u16Steps = (Loc_u8WindowPosition - Loc_u8WindowValue) * (u16)512 / (u16)100;

				/*TSet the index flag to Window.*/
				Stepmotor_u8MotorIndex = STEPMOTOR_WINDOW;

				/*Enable the task*/
				Stepmotor_u8TaskFlag = ONE;

				/*Save the window position*/
				Loc_u8WindowPosition = Loc_u8WindowValue;

				/*Clear the window value*/
				Loc_u8WindowValue = ZERO;

			}/*end of if(Loc_u8WindowValue < Loc_u8WindowPosition)*/
			else if(Loc_u8WindowValue > Loc_u8WindowPosition)
			{
				/*Set the direction to counter Clockwise*/
				Stepmotor_u8Direction = STEPMOTOR_COUNTERCLOCKWISE;

				/*Calculate the number of steps and save the value in the step motor steps variable*/
				Stepmotor_u16Steps = (Loc_u8WindowValue - Loc_u8WindowPosition) * (u16)512 / (u16)100;

				/*TSet the index flag to Window.*/
				Stepmotor_u8MotorIndex = STEPMOTOR_WINDOW;

				/*Enable the task*/
				Stepmotor_u8TaskFlag = ONE;

				/*Save the window position*/
				Loc_u8WindowPosition = Loc_u8WindowValue;

				/*Clear the window value*/
				Loc_u8WindowValue = ZERO;

			}/*end of else if(Loc_u8WindowValue > Loc_u8WindowPosition)*/
			else
			{
				/*Do nothing as the current position is the same as the required position*/

			}/*end of else of if(Loc_u8WindowValue < Loc_u8WindowPosition)*/

			/*Change the state of the Window state to the start one*/
			Loc_enuWindowStates = App_enuWindow0;

			/*Change the state of the Application to the login in state*/
			App_enuStates = App_enuLoggedIn;

			break;
		}/*end of case App_enuWindow5*/

		default:
		{
			break;
		}/*end of default*/


	}/*end of switch(Loc_enuWindowStates)*/
}

/*
 * Fan_Process is the process called if the user choose fan.
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
void Fan_Process(void)
{
	/*Loc_enuFanStates is used to save the state of the fan*/
	static App_tenuFanStates Loc_enuFanStates = App_enuFan0;

	/*Loc_u16TimeOut is used to as a counter to time up if the user did not enter any option.*/
	static u16 Loc_u16TimeOut = 300;

	/*Loc_enuKeypad is used to check the return of the function pressed or not*/
	Keypad_tenuErrorStatus Loc_enuKeypad = Keypad_enuOk;

	/*Loc_u8KeypadValue is the pressed key if pressed*/
	u8 Loc_u8KeypadValue;

	/*Switch on the states*/
	switch(Loc_enuFanStates)
	{
		case App_enuFan0:
		{
			/*Display On on the LCD*/
			Lcd_vidDisplayString("On: Press 1", 11, 0, 0);

			/*Change the state to the next one*/
			Loc_enuFanStates = App_enuFan1;

			break;
		}/*end of App_enuFan0*/

		case App_enuFan1:
		{
			/*Display On on the LCD*/
			Lcd_vidDisplayString("Off: Press 2", 12, 1, 0);

			/*Change the state to the next one*/
			Loc_enuFanStates = App_enuFan2;

			break;
		}/*end of App_enuFan1*/

		case App_enuFan2:
		{
			/*Get key if pressed*/
			Loc_enuKeypad = Keypad_enuGetKey(&Loc_u8KeypadValue);

			/*Check if the return is ok or not*/
			if(Loc_enuKeypad == Keypad_enuOk)
			{
				/*Check if the key is valid or not*/
				if(Loc_u8KeypadValue == '1')
				{
					/*On the motor*/
					Dcmotor_enuOnMotor(DCMOTOR_1, DCMOTOR_DIR_RIGHT);

					/*Change the state of the application to window*/
					App_enuStates = App_enuLoggedIn;

					/*Reset the state of the current process*/
					Loc_enuFanStates = App_enuFan0;

					/*Reset the time out timer*/
					Loc_u16TimeOut = 300;

					/*Clear the LCD*/
					Lcd_vidSendCommand(ONE);

				}/*end of if(Loc_u8KeypadValue == '1')*/
				else if(Loc_u8KeypadValue == '2')
				{
					/*Off the motor*/
					Dcmotor_enuOffMotor(DCMOTOR_1);

					/*Change the state of the application to fan*/
					App_enuStates = App_enuLoggedIn;

					/*Reset the state of the current process*/
					Loc_enuFanStates = App_enuFan0;

					/*Reset the time out timer*/
					Loc_u16TimeOut = 300;

					/*Clear the LCD*/
					Lcd_vidSendCommand(ONE);

				}/*end of else if(Loc_u8KeypadValue == '2')*/
				else
				{
					/*Decrease the Loc_u16TimeOut timer till reach time out.*/
					Loc_u16TimeOut--;

					/*Wait till a minute elapse*/
					if(Loc_u16TimeOut == ZERO)
					{
						/*Reset the time out timer*/
						Loc_u16TimeOut = 300;

						/*Reset the state of the current process*/
						Loc_enuFanStates = App_enuFan0;

						/*Reset the state of the application to the start state.*/
						App_enuStates = App_enuStart;

						/*Clear the LCD*/
						Lcd_vidSendCommand(ONE);

					}/*end of if(Loc_u16TimeOut == ZERO)*/
					else
					{
						/*Do nothing.*/
					}/*end of else of if(Loc_u16TimeOut == ZERO)*/

				}/*end of else of if(Loc_u8KeypadValue == '1')*/

			}/*end of if(Loc_enuKeypad == Keypad_enuOk)*/
			else
			{
				/*Decrease the Loc_u16TimeOut timer till reach time out.*/
				Loc_u16TimeOut--;

				/*Wait till a minute elapse*/
				if(Loc_u16TimeOut == ZERO)
				{
					/*Reset the time out timer*/
					Loc_u16TimeOut = 300;

					/*Reset the state of the process to the start of it.*/
					Loc_enuFanStates = App_enuFan0;

					/*Reset the state of the application to the start state.*/
					App_enuStates = App_enuStart;

					/*Clear the LCD*/
					Lcd_vidSendCommand(ONE);

				}/*end of if(Loc_u16TimeOut == ZERO)*/
				else
				{
					/*Do nothing.*/
				}/*end of else of if(Loc_u16TimeOut == ZERO)*/
			}/*end of else of if(Loc_enuKeypad == Keypad_enuOk)*/

			break;
		}/*end of App_enuFan2*/

		default:
		{
			break;
		}/*end of default*/

	}/*end of switch(Loc_enuFanStates)*/
}

void Uart_Task(void)
{
	u8 Loc_u8UartTaskUpdate = 0;

	Uart_RxByte(&Loc_uart, &Loc_u8UartTaskUpdate);

	if(Loc_u8UartTaskUpdate == 0x55)
	{
		Flash_SectorErase(1);

		Flash_Program(FLASH_PROGRAM_SIZE_x32 , 0x0800400Cu , 0x55555555);

		Uart_SendByte(&Loc_uart, 0xAA);
		SCB_RestSys();
	}

}
