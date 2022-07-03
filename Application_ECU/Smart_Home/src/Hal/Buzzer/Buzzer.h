#ifndef __BUZZERDRIVERH__
#define __BUZZERDRIVERH__

#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "Buzzer_cfg.h"

typedef enum
{
	Buzzer_enuOk,
	Buzzer_enuNotOk,
  
}Buzzer_tenuErrorStatus;

/*
 * Buzzer_enuInit is used to initialize the Gpio pins for the buzzer
 *
 * Input: It takes nothing.
 *
 * Return: It returns the error states of the function.
 */
extern Buzzer_tenuErrorStatus Buzzer_enuInit(void);

/*
 * Buzzer_enuOn is used to switch on a Buzzer
 *
 * Input: It takes one input, Copy_u8BuzzerId which is one of the Buzzer in the Buzzer_cfg.h file
 *
 * Return: It returns the error status of the function.
 */
extern Buzzer_tenuErrorStatus Buzzer_enuOn(u8 Copy_u8BuzzerId);

/*
 * Buzzer_enuOn is used to switch off a Buzzer
 *
 * Input: It takes one input, Copy_u8BuzzerId which is one of the Buzzer in the Buzzer_cfg.h file
 *
 * Return: It returns the error status of the function.
 */
extern Buzzer_tenuErrorStatus Buzzer_enuOff(u8 Copy_u8BuzzerId);

#endif
