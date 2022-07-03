/*
 * Calc_cfg.h
 *
 *  Created on: Apr 14, 2022
 *      Author:
 */

#ifndef APP_SMART_HOME_SMART_HOME_CFG_H_
#define APP_SMART_HOME_SMART_HOME_CFG_H_

/*UARTTASKPRIORITY is the priority of the UART task and it must be from 0 to the max number of the tasks*/
#define UARTTASKPRIORITY				FOUR

/*UARTTASKPERIODICTIME is the periodic time for the UART task*/
#define UARTTASKPERIODICTIME			200

/*UARTTASK_FIRSTDELAY is the first delay of the UART task*/
#define UARTTASK_FIRSTDELAY			500

/*APPTASKPRIORITY is the priority of the APP task and it must be from 0 to the max number of the tasks*/
#define APPTASKPRIORITY				TWO

/*APPTASKPERIODICTIME is the periodic time for the APP task*/
#define APPTASKPERIODICTIME			250

/*APPTASK_FIRSTDELAY is the first delay of the Application task*/
#define APPTASK_FIRSTDELAY			200


#endif /* APP_SMART_HOME_SMART_HOME_CFG_H_ */
