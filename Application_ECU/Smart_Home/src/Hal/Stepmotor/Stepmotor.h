/*
 * Stepmotor.h
 *
 *  Created on: Apr 20, 2022
 *      Author: Michael_Safwat
 */

#ifndef STEPMOTOR_STEPMOTOR_H_
#define STEPMOTOR_STEPMOTOR_H_


/*************************************************************************************************/
/*												Definies										 */
/*************************************************************************************************/

#define STEPMOTOR_FULLSTEP				1
#define STEPMOTOR_HALFSTEP				0

#define STEPMOTOR_CLOCKWISE    			1
#define STEPMOTOR_COUNTERCLOCKWISE		0


/*************************************************************************************************/
/*											Function Prototypes									 */
/*************************************************************************************************/

/*
 * Stepmotor_vidInit is used to add the step motor task into the scheduler
 *
 * Input: It takes no inputs.
 *
 * Return: It returns nothing.
 */
extern void Stepmotor_vidInit(void);


#endif /* STEPMOTOR_STEPMOTOR_H_ */
