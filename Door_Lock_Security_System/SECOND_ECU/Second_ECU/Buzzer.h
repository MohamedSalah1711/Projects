/*
 * Buzzer.h
 *
 *  Created on: Jul 16, 2022
 *      Author: mohmed salha
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "gpio.h"
#include "std_types.h"
#define Buzzer_Port PORTD_ID /*port of buzzer*/
#define Buzzer_Pin 	PIN5_ID /*pin of buzzer*/
void Buzzer_init(void);/*initialize buzzer*/
void Buzzer_On(void);/*get buzzer in on mode*/
void Buzzer_off(void);/*turn buzzer off*/


#endif /* BUZZER_H_ */
