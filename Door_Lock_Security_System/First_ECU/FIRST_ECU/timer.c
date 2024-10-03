/*
 * timer.c
 *
 *  Created on: Jul 14, 2022
 *      Author: mohmed salha
 */

#include "timer.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use Timer0 Registers */
#include <avr/interrupt.h> /* For TIMER0 ISR */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)/* isr for ovf*/
{
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER0_COMP_vect)/*isr for comp*/
{
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Timer_init(Timer_config *config_ptr) {
	/*first of all make sure all value of register =0*/
	TCCR0 &= 0x00;
	OCR0 &= 0x00;
	TCNT0 &= 0x00;
	TIMSK &= 0XFC;
	/**start modifing*/
	switch(config_ptr->Mode){
	case Normal:
		TCCR0|=(1<<FOC0);/*non pwm*/
		TCCR0=(TCCR0 & 0XF8 )   |  ((config_ptr->pre_sc)<<CS00);/*put pre scaler*/
		TCNT0=(config_ptr->initial_value);/*put initial value*/
		TIMSK|=(1<<TOIE0);/*enable interrupt for ovf*/
	break;

	case Compare:
		TCCR0|=(1<<FOC0);/*non pwm*/
		TCCR0=(TCCR0 & 0XF8 )   |  ((config_ptr->pre_sc)<<CS00);/*put pre scaler*/
		OCR0=(config_ptr->Compare_value);/*put initial value*/
		TIMSK|=(1<<OCIE0);/*enable interrupt for compare*/
	break;

	}


}
/*timer call back*/
void Timer_Call_back(void(*ptr)(void)){

	g_callBackPtr=ptr;
}

void Timer_deinit(void){

	/*clear all register*/
	TCCR0 &= 0x00;
	OCR0 &= 0x00;
	TCNT0 &= 0x00;
	TIMSK &= 0XFC;


}
