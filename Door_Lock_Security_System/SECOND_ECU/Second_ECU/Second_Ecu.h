/*
 * Second_Ecu.h
 *
 *  Created on: Jul 22, 2022
 *      Author: mohmed salha
 */

#ifndef SECOND_ECU_H_
#define SECOND_ECU_H_
#include "gpio.h"
#include "motor.h"
#include "twi.h"
#include "timer.h"
#include "uart.h"
#include "common_macros.h"
#include "external_eeprom.h"
#include "Buzzer.h"
#include "std_types.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/*definiton of command*/
#define   READY				2
#define   DONE         		3
#define   PASS_SEND    		4
#define   SECOND_PASS		5
#define   PASS_MATCH		6
#define   PASS_NOT_MATCH 	7
#define   OPEN_DOOR			8
#define   WRONG_PASS		9
#define   NUMBER_OF_PASS    5
#define   activate_alert	10
#define		Pass_check      11
#define     one_min_ticks   1831
#define     fifteen_sec     457
#define     three_sec		91
#define     Check_saved     12
#define     Exist           13
#define     Not_Exist       14

uint8 Global_pass[NUMBER_OF_PASS],Re_Global_pass[NUMBER_OF_PASS],return_command,command,recived_command;
uint16 tick=0;
uint8 passeeprom[NUMBER_OF_PASS];


void Uart_SENDCommand(uint8 command);/*function to send command*/
uint8 Uart_RecieveCommand(void);/*receive command function by uart*/
void UART_RecivePASS(uint8 arr []);/*recive password from keypad*/
uint8 Compare_two_pass_in_state0(uint8 arr0[],uint8 arr1[]);/*compare 2 passes send match or not*/
void  write_pass_EEprom(uint8 arr[]);/*write passworn in eeprom*/
void read_pass_eeprom_store_it(uint8 arr[]);/*read password from eeprom and store it in array*/
void tick_for_motor(void);/*count ticks*/
#endif /* SECOND_ECU_H_ */
