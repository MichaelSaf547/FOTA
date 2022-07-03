/*
 * Calc_prv.h
 *
 *  Created on: Apr 14, 2022
 *      Author:
 */

#ifndef APP_SMART_HOME_SMART_HOME_PRV_H_
#define APP_SMART_HOME_SMART_HOME_PRV_H_


typedef enum
{
	App_enuStart,		/*Log in state*/
	App_enuLoggedIn,	/*Log in process success*/
	App_enuLoggedError,	/*Log in process failed*/
	App_enuWindow,		/*Window state*/
	App_enuFan			/*Fan state*/
}App_tenuStates;


typedef enum
{
	App_enuStart0,		/*Print Enter your password*/
	App_enuStart1,		/*Go to the next line*/
	App_enuStart2		/*Get user password*/
}App_tenuStartStates;

typedef enum
{
	App_enuLoggedIn0,	/*Clear the LCD*/
	App_enuLoggedIn1,	/*Print welcome Michael and wait for a while*/
	App_enuLoggedIn2,	/*Print the first option Window*/
	App_enuLoggedIn3,	/*Print the second option Fan*/
	App_enuLoggedIn4,	/*Wait for the user input*/

}App_tenuLoggedInStates;

typedef enum
{
	App_enuLoggingError0,	/*Clear the LCD and turn the buzzer and led on*/
	App_enuLoggingError1,	/*Print Pass is wrong and turn the led off*/
	App_enuLoggingError2	/*Toggle the led*/
}App_tenuLoggingErrorStates;

typedef enum
{
	App_enuWindow0,		/*Display first part*/
	App_enuWindow1,		/*Display second part*/
	App_enuWindow2,		/*Wait a while then display last part*/
	App_enuWindow3,		/*Go to the second line of LCD*/
	App_enuWindow4,		/*Read the input user then print the input*/
	App_enuWindow5, 	/*Take the action*/
}App_tenuWindowStates;

typedef enum
{
	App_enuFan0,	/*Display On*/
	App_enuFan1,	/*Display Off*/
	App_enuFan2		/*Wait for the user input*/
}App_tenuFanStates;

/*
 * App_Task is the application task to check every step in the application
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
extern void App_Task(void);

/*
 * Start_Process is the process for logging in to the application
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
extern void Start_Process(void);

/*
 * Logging_Success is the process called if the entered password is correct to control the window and fan.
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
extern void Logging_Success(void);

/*
 * LoggingError is the process called if the entered password is incorrect to turn the buzzer and toggle a LED.
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
extern void Logging_Error(void);

/*
 * Window_Process is the process called if the user choose window.
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
extern void Window_Process(void);

/*
 * Fan_Process is the process called if the user choose fan.
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
extern void Fan_Process(void);


/*
 * Uart_Task is the Uart task.
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing.
 */
extern void Uart_Task(void);

#endif /* APP_SMART_HOME_SMART_HOME_PRV_H_ */
