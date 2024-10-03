/*
 * ECU1.h
 *
 *  Created on: Jul 17, 2022
 *      Author: mohmed salha
 */

#ifndef ECU1_H_
#define ECU1_H_
#include "gpio.h"
#include "keypad.h"
#include "lcd.h"
#include "timer.h"
#include "uart.h"
#include "common_macros.h"
#include "std_types.h"
#include <util/delay.h>
#include <avr/interrupt.h>
/*Definiton in command*/
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
/*global variable*/
uint8 global_pass[5], wrong_time=0,state=0,flag_state=0,command;
uint16 tick=0;
uint8 comm; /*variable to store command*/
void create_password_and_store(void);/*in first state get password from keypad and send it by uart*/
void Uart_SENDCommand(uint8 command);/*sending command by uart*/
uint8 Uart_RecieveCommand(void);/*recive command by uart*/
void UART_SENDPASS(uint8 array[]);/*sending pass by uart*/
void Main_option(void);/*second state open door or change password*/
void LCD_Alert(void);/*print alert on lcd for 1 min*/
void tickk(void);/*ticks count*/

void Saved_PassBeforRun(void);/*check if that a password saved in eeprom or not*/

#endif /* ECU1_H_ */
