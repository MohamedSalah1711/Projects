/*
 * motor.c
 *
 *  Created on: May 26, 2022
 *      Author: mohmed salha
 */

#include "motor.h"
\
/*function to setup direction of motor*/
void DcMotor_Init(void){
	GPIO_setupPinDirection(motor_port, motor_firstPin, PIN_OUTPUT);
	GPIO_setupPinDirection(motor_port, motor_secondPin, PIN_OUTPUT);
	GPIO_writePin(motor_port, motor_firstPin, LOGIC_LOW);
	GPIO_writePin(motor_port, motor_secondPin, LOGIC_LOW);


}
/*direction of dc motor*/
void DcMotor_Rotate(DcMotor_State state){
	 \
	if(state==CW){
		GPIO_writePin(motor_port, motor_firstPin, LOGIC_HIGH);
		GPIO_writePin(motor_port, motor_secondPin, LOGIC_LOW);

	}else if(state==(A_CW)){
		GPIO_writePin(motor_port, motor_firstPin, LOGIC_LOW);
		GPIO_writePin(motor_port, motor_secondPin, LOGIC_HIGH);

	}else{
		GPIO_writePin(motor_port, motor_firstPin, LOGIC_LOW);
		GPIO_writePin(motor_port, motor_secondPin, LOGIC_LOW);
	}

}
