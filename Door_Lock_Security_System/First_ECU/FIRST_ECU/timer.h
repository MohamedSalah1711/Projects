/*
 * timer.h
 *
 *  Created on: Jul 14, 2022
 *      Author: mohmed salha
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"
/**********************************************************************/
typedef enum
{
	Normal,Compare=2
}Timer_mode;
typedef enum
{
	No_clc,No_prescaling,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Pre_scaler;
typedef struct
{
	Timer_mode Mode;
	Pre_scaler pre_sc;
	uint8 initial_value;
	uint8 Compare_value;
}Timer_config;
/*************************************************************************/
void Timer_init(Timer_config *config_ptr);  /*function to initial timer*/

void Timer_Call_back(void(*ptr)(void)); /*call back function*/

void Timer_deinit(void);/*Function to DeInit the timer to start again from beginning*/





#endif /* TIMER_H_ */
