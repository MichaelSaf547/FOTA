/*
 * Dcmotor_cfg.h
 *
 *  Created on: Apr 16, 2022
 *      Author: Michael_Safwat
 */

#ifndef DCMOTOR_DCMOTOR_CFG_H_
#define DCMOTOR_DCMOTOR_CFG_H_

/*
 * Motor pins type
 */

typedef struct
{
	void * DCmotor_Port1;
	void * DCmotor_Port2;
	u16 DCmotor_Pin1;
	u16 DCmotor_Pin2;

}DCmotor_cfg_t;

/*
 * Motor numbers
 */

#define NUM_OF_DCMOTORS		ONE

/*
 * Motor names
 */

#define DCMOTOR_1			ZERO

#endif /* DCMOTOR_DCMOTOR_CFG_H_ */
