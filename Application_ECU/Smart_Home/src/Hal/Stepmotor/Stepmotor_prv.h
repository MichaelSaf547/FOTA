/*
 * Stepmotor_prv.h
 *
 *  Created on: Apr 24, 2022
 *      Author: Michael_Safwat
 */

#ifndef STEPMOTOR_STEPMOTOR_PRV_H_
#define STEPMOTOR_STEPMOTOR_PRV_H_

typedef enum
{
	Stepmotor_enuStep0,
	Stepmotor_enuStep1,
	Stepmotor_enuStep2,
	Stepmotor_enuStep3,
	Stepmotor_enuStep4,
	Stepmotor_enuStep5,
	Stepmotor_enuStep6,
	Stepmotor_enuStep7,
	Stepmotor_enuStep8,

}Stepmotor_tenuTaskSteps;


/*
 * Stepmotor_Task is used to rotate the motor number of steps in the specified direction.
 *
 * Input: It takes no inputs.
 *
 * Return: It returns nothing.
 */
extern void Stepmotor_Task(void);

#endif /* STEPMOTOR_STEPMOTOR_PRV_H_ */
