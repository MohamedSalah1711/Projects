/*
 * Buzzer.c
 *
 *  Created on: Jul 16, 2022
 *      Author: mohmed salha
 */
#include "Buzzer.h"


void Buzzer_init(void){
	GPIO_setupPinDirection(Buzzer_Port,Buzzer_Pin,PIN_OUTPUT);
	GPIO_writePin(Buzzer_Port,Buzzer_Pin,LOGIC_LOW);
}
void Buzzer_On(void){
	GPIO_writePin(Buzzer_Port,Buzzer_Pin,LOGIC_HIGH);

}
void Buzzer_off(void){
	GPIO_writePin(Buzzer_Port,Buzzer_Pin,LOGIC_LOW);

}
