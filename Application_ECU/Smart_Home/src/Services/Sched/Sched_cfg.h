/*
 * Sched_cfg.h
 *
 *  Created on: Apr 14, 2022
 *      Author:
 */

#ifndef SERVICES_SCHED_SCHED_CFG_H_
#define SERVICES_SCHED_SCHED_CFG_H_


/*
 * The number of tasks in the scheduler
 */
#define RUNNABLELISTLENGTH			5

/*Adjust the tick time of the system timer it should be the greatest common divisor of all the tasks*/
#define TICK_MS				1


#endif /* SERVICES_SCHED_SCHED_CFG_H_ */
