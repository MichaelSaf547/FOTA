/*
 * Sched.c
 *
 *  Created on: Apr 14, 2022
 *      Author: Michael_Safwat
 */


#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Systick/Systick.h"
#include "Sched.h"
#include "Sched_prv.h"
#include "Sched_cfg.h"


/*
 * Sched is used to loop over the tasks every time the system timer interrupt happens
 *
 * Inputs: It takes no input.
 *
 * Return: It returns nothing.
 */
static void Sched(void);

/*
 * RunnableList is an array to hold the tasks in it with the defined length in the Sched_cfg.h file
 */
Runnable_t RunnableList[RUNNABLELISTLENGTH];

extern void Sched_vidInit()
{
	/*Initialize the system timer*/
	Systick_Init();

	/*Set the time for the timer in ms*/
	Systick_SetTickTime_ms(TICK_MS);

	/*Set the Sched function as the call back function to be called every time the timer finish*/
	Systick_Register_cbf(Sched);
}


extern void Sched_vidStart()
{
	/*Start the System timer*/
	Systick_Start();

	/*While to hold the processor waiting for the next interrupt of system timer*/
	while(1);
}

extern void Sched_RegisterRunnable(Runnable_t * Runnable, u32 Priority)
{
	/*Check if the priority place in the array is empty or not*/
	if(RunnableList[Priority].cbfP == NULL)
	{
		/*Save the structure in the runnable list array*/
		RunnableList[Priority].CyclicTimems = Runnable->CyclicTimems;
		RunnableList[Priority].FirstDelay = Runnable->FirstDelay;
		RunnableList[Priority].cbfP = Runnable->cbfP;
	}/*end of if(RunnableList[Priority].cbfP == NULL)*/

	else
	{
		/*Raise Error*/
	}/*end of else of if(RunnableList[Priority].cbfP == NULL)*/

}

static void Sched(void)
{
	/*Loc_u32ForCounter is used to loop over the runnable list*/
	u32 Loc_u32ForCounter = 0;

	for(Loc_u32ForCounter = 0; Loc_u32ForCounter < RUNNABLELISTLENGTH; Loc_u32ForCounter++)
	{
		/*Check that the function pointer is not pointing to Null*/
		if(RunnableList[Loc_u32ForCounter].cbfP != NULL)
		{
			/*Check if the runnable time has come*/
			if(RunnableList[Loc_u32ForCounter].FirstDelay == ZERO)
			{
				/*Call the function*/
				(RunnableList[Loc_u32ForCounter].cbfP)();

				/*Increase the first delay variable with the cyclic time for the next round*/
				RunnableList[Loc_u32ForCounter].FirstDelay += RunnableList[Loc_u32ForCounter].CyclicTimems;
			}/*End of if(RunnableList[Loc_u32ForCounter].FirstDelay_ms == ZERO)*/
			else
			{
				/*Do Nothing*/
			}/*End of else of if(RunnableList[Loc_u32ForCounter].FirstDelay_ms == ZERO)*/

			/*Reduce the time that the runnable will be called after.*/
			(RunnableList[Loc_u32ForCounter].FirstDelay) -= TICK_MS;
		}/*End of if(RunnableList[Loc_u32ForCounter] != NULL)*/
		else
		{
			/*Ignore it.*/
		}/*End of else of if(RunnableList[Loc_u32ForCounter] != NULL)*/
	}/*End of for(Loc_u32ForCounter = 0; Loc_u32ForCounter < RUNNABLELISTLENGTH; Loc_u32ForCounter++)*/
}


