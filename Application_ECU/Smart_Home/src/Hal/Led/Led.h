#ifndef	__LEDH__
#define __LEDH__

/*
 *typedefs
 */ 

typedef struct
{
	void * Led_u8Port;
	u8 Led_u8PinNum;
	u8 Led_u8ActiveState;
	u8 Led_OType;
}Led_cfg_t;


typedef enum
{
	Led_enuOk,
	Led_enuNotOk,
}Led_tenuErrorStatus;
/*
 * The output type of the pin
 */
#define OTYPE_PP			0
#define OTYPE_OD			1

/*
 * The led state either on or off
 */
 
#define LEDSTATE_OFF		0
#define LEDSTATE_ON			1

/*
 * The Active state of the led
 */

#define LEDACTIVESTATE_HIGH 0
#define LEDACTIVESTATE_LOW	1

/*
 * Interface function prototype
 */

/*
 * Led_enuInit is used to initialise the leds pin
 * Inputs: It takes nothing
 * Return: It returns the error status of the function
 */
extern Led_tenuErrorStatus Led_enuInit();

/*
 * Led_enuSetState is used to set the state of the led either on or off using 
 * 1- LEDSTATE_OFF 
 * 2- LEDSTATE_ON
 *
 * Inputs:  1- Copy_u16LedNum, the led number as configured in the Led_cfg.h
 *			2- Copy_LedState, the state of the led either on or off
 *
 * Return: It returns the error status of the function
 */
extern Led_tenuErrorStatus Led_enuSetState(u16 Copy_u16LedNum, u8 Copy_LedState);

#endif