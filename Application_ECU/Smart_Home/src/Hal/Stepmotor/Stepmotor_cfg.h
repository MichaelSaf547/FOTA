/*
 * Stepmotor_cfg.h
 *
 *  Created on: Apr 20, 2022
 *      Author: Michael_Safwat
 */

#ifndef STEPMOTOR_STEPMOTOR_CFG_H_
#define STEPMOTOR_STEPMOTOR_CFG_H_

typedef struct
{
	void * Stepmotor_PortA;
	void * Stepmotor_PortB;
	void * Stepmotor_PortC;
	void * Stepmotor_PortD;

	u16 Stepmotor_PinA;
	u16 Stepmotor_PinB;
	u16 Stepmotor_PinC;
	u16 Stepmotor_PinD;

}Stepmotor_cfg_t;

/*
 * Number of Stepper motors in the project
 */
#define NUM_OF_STEPMOTOR		1

/*
 * Type the name of each stepper motor and the number in front of it.
 */
#define STEPMOTOR_WINDOW		0
#define STEPMOTOR_DOOR			1


/*STEPMOTORTASKPRIORITY is the priority of the STEPMOTOR task and it must be from 0 to the max number of the tasks*/
#define STEPMOTORTASKPRIORITY				THREE

/*STEPMOTORTASKPERIODICTIME is the periodic time for the STEPMOTOR task.*/
#define STEPMOTORTASKPERIODICTIME			10

/*STEPMOTORFIRSTDALAY is the first delay of the stepper motor task*/
#define STEPMOTORFIRSTDALAY					100

/*
 * STEPMOTOR_STEP is the step configuration
 * 1- STEPMOTOR_FULLSTEP
 * 2- STEPMOTOR_HALFSTEP
 * */
#define STEPMOTOR_STEP						STEPMOTOR_HALFSTEP


#endif /* STEPMOTOR_STEPMOTOR_CFG_H_ */
