#ifndef __BuzzerCFGH__
#define __BuzzerCFGH__


typedef struct
{
	void * Buzzer_Port;
	u16 Buzzer_Pin;

}Buzzer_cfg_t;

/*Number of Buzzer in the project*/
#define NUM_OF_BUZZER 			1

/*Index of the Buzzer used in the configuration in the Buzzer_cfg.c file in the array*/
#define BUZZER_ALARM				0

#endif
