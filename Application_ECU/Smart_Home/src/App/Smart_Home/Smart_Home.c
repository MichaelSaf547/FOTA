/*
 * Calc.c
 *
 *  Created on: Apr 14, 2022
 *      Author:
 */



#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Rcc/Rcc.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "../../Mcal/Usart/Usart.h"
#include "../../Services/Sched/Sched.h"
#include "../../Hal/Keypad/Keypad.h"
#include "../../Hal/Buzzer/Buzzer.h"
#include "../../Hal/Led/Led.h"
#include "../../Hal/Dcmotor/Dcmotor.h"
#include "../../Hal/Stepmotor/Stepmotor.h"
#include "Smart_Home.h"
#include "../../Lcd/Lcd.h"
#include "Smart_Home_prv.h"
#include "Smart_Home_cfg.h"



USARTHandel_t Loc_uart;


/*
 * App_vidInit is used to initialize all the needed peripherals and HAL
 *
 * Input: It takes no input.
 *
 * Return: It returns nothing
 */
void App_vidInit(void)
	{
	/*Loc_runnable is used to add the Application task in the scheduler*/
	Runnable_t Loc_runnable;

	gpioPinCfg_t UARTTX, UARTRX;

	Rcc_enuSysClockOnOff(SYSCLK_HSI, ON);
	Rcc_enuSelectSysClock(SYSCLK_HSI);

	Rcc_enuEnableClockPeripheral(GPIOA);
	Rcc_enuEnableClockPeripheral(GPIOB);
	Rcc_enuEnableClockPeripheral(GPIOC);

	Rcc_enuEnableClockPeripheral(USART_1);

	/*Initialize the scheduler*/
	Sched_vidInit();

	/*Initialize the LCD and its pins*/
	Lcd_vidInit();

	/*Initialize the keypad pins*/
	Keypad_enuInit();

	/*Initialize the Buzzer pins*/
	Buzzer_enuInit();

	/*Initialize the DC motor pins*/
	DCmotor_enuInit();

	/*Initialize the LED pins*/
	Led_enuInit();

	/*Initialize the Stepper motor pins and add its task to the Scheduler.*/
	Stepmotor_vidInit();

	/*Flash Unlocking*/
	Flash_Init();

	/*Initialize the USART1*/

	/*Initialize the pins for the USART1*/
	/*---Configure pin 9  TX_UART1---*/

	UARTTX.mode  = GPIO_PIN_AF_PP;
	UARTTX.port  = GPIO_PORTA;
	UARTTX.pin   = GPIO_PIN9;
	UARTTX.speed = GPIO_PIN_SPEED3;
	gpio_initPin(&UARTTX);

	/*---Configure pin 10 RX_UART1---*/

	UARTRX.mode  = GPIO_PIN_AF_PP;
	UARTRX.port  = GPIO_PORTA;
	UARTRX.pin   = GPIO_PIN10;
	UARTRX.speed = GPIO_PIN_SPEED3;
	gpio_initPin(&UARTRX);

	(*(pu32)(0x40020024)) = 0x00000770;

	/*---Configure Uart1---*/
	Loc_uart.BaudRate           = 9600;
	Loc_uart.Channel_BaseAdress = USART1;
	Loc_uart.Mode               = MODE_TX_RX;
	Loc_uart.Parity 			= PARITY_DISABLE;
	Loc_uart.Stop_bits			= STOP_BITS_ONE;
	Loc_uart.WordLength			= WORD_LENGHT_8B;
	Loc_uart.state				= ready;
	Uart_Init(&Loc_uart);

	/*Add the values of the UART task into the runnable to add the task into the scheduler*/
	Loc_runnable.CyclicTimems = UARTTASKPERIODICTIME;
	Loc_runnable.cbfP = Uart_Task;
	Loc_runnable.FirstDelay = UARTTASK_FIRSTDELAY;

	Sched_RegisterRunnable(&Loc_runnable, UARTTASKPRIORITY);


	/*Add the values of the application task into the runnable to add the task into the scheduler*/
	Loc_runnable.CyclicTimems = APPTASKPERIODICTIME;
	Loc_runnable.cbfP = App_Task;
	Loc_runnable.FirstDelay = APPTASK_FIRSTDELAY;

	Sched_RegisterRunnable(&Loc_runnable, APPTASKPRIORITY);

	/*Start the scheduler*/
	Sched_vidStart();
}
