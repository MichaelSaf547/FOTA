/*
 * Dcmotor.h
 *
 *  Created on: Apr 16, 2022
 *      Author: Michael_Safwat
 */

#ifndef DCMOTOR_DCMOTOR_H_
#define DCMOTOR_DCMOTOR_H_

 /*********************************************************************************************************/
 /* 												Defines 											  */
 /*********************************************************************************************************/

/*Directions*/

#define DCMOTOR_DIR_LEFT			ZERO
#define DCMOTOR_DIR_RIGHT			ONE


 /*********************************************************************************************************/
 /* 												Types												  */
 /*********************************************************************************************************/

typedef enum
{
	Dcmotor_enuOk,
	Dcmotor_enuNotOk,
}Dcmotor_tenuErrorStatus;



 /*********************************************************************************************************/
 /* 									Interface functions prototype									  */
 /*********************************************************************************************************/

/*
 * DCmotor_enuInit is used to initialize the Gpio pins for the DCmotors.
 *
 * Input: It takes nothing.
 *
 * Return: It returns the error states of the function.
 */
extern Dcmotor_tenuErrorStatus DCmotor_enuInit(void);

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

Dcmotor_tenuErrorStatus Dcmotor_enuOnMotor(u8 Copy_u8MotorNumber, u8 Copy_u8MotorDirection);


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

Dcmotor_tenuErrorStatus Dcmotor_enuOffMotor(u8 Copy_u8MotorNumber);


#endif /* DCMOTOR_DCMOTOR_H_ */
