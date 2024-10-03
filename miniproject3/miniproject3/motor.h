/*
 * motor.h
 *
 *  Created on: May 26, 2022
 *      Author: mohmed salha
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include "std_types.h"
#include "gpio.h"
#include "commonmacro.h"
/*DEFINITON*/
#define motor_firstPin PIN0_ID
#define motor_secondPin PIN1_ID
#define motor_port PORTB_ID

/*ENUMS*/
typedef enum {
	CW,A_CW,off
}DcMotor_State;
/*FUNCTION DECLRATION*/
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */
