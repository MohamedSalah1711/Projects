/*
 * ECU1.c
 *
 *  Created on: Jul 17, 2022
 *      Author: mohmed salha
 */

#include "ECU1.h"
#define F_CPU 8000000UL
int main() {
	/***********************UART INITIZLIZE*********************************/
	UART_ConfigType Uart_config = { DATA_BIT_8, DISABLED, STOP_BIT_1, 9600 };
	UART_init(&Uart_config);
	/*****************************************************************/
	/******************************LCD INITIAZLIZE********************/
	LCD_init();
	/***************************************************************/
	/*IF state = 0 call create_password_and_store() */
	/*IF state =1 call Main_option()*/
	SREG |= (1 << 7);

	Saved_PassBeforRun();


	while (1) {
		if (state == 0) {
			create_password_and_store();
		}
		if (state == 1) {
			Main_option();
		}

	}

}
void create_password_and_store(void) {
	uint8 count;
	if (flag_state == 0) {
		LCD_clearScreen();/*CLEAR SCREEN OF LCD*/
		LCD_displayString("Please enter password:");
		LCD_moveCursor(1, 8);
		for (count = 0; count < NUMBER_OF_PASS; count++) {
			global_pass[count] = KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
			_delay_ms(500);
		}
		Uart_SENDCommand(PASS_SEND);
		UART_SENDPASS(global_pass);
		flag_state = 1;
	}
	/***********************************/
	if (flag_state == 1) {
		LCD_clearScreen();/*CLEAR SCREEN OF LCD*/
		LCD_displayString("Please re_enter password:");
		LCD_moveCursor(1, 11);
		for (count = 0; count < NUMBER_OF_PASS; count++) {
			global_pass[count] = KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
			_delay_ms(500);
		}

		Uart_SENDCommand(SECOND_PASS);
		UART_SENDPASS(global_pass);
		flag_state = 2;
	}
	if (flag_state == 2) {
		switch (Uart_RecieveCommand()) {

		case PASS_MATCH:
			LCD_clearScreen();
			LCD_displayString("pass match_welcome!! ");
			_delay_ms(3000);
			flag_state = 3;
			state = 1;

			break;

		case PASS_NOT_MATCH:
			LCD_clearScreen();
			LCD_displayString("pass dosent match");
			_delay_ms(3000);
			flag_state = 0;
			state = 0;
			break;
		}
	}
}
void Uart_SENDCommand(uint8 command) {
	UART_sendByte(READY);
	while (UART_recieveByte() != READY)
		;
	UART_sendByte(command);
	while (UART_recieveByte() != DONE)
		;

}
uint8 Uart_RecieveCommand() {
	while (UART_recieveByte() != READY) {
	};
	UART_sendByte(READY);
	command = UART_recieveByte();
	UART_sendByte(DONE);
	return command;

}
void UART_SENDPASS(uint8 array[]) {
	uint8 count;

	UART_sendByte(READY);
	while (UART_recieveByte() != READY)
		;
	for (count = 0; count < NUMBER_OF_PASS; count++) {
		UART_sendByte(array[count]);
	}
	while (UART_recieveByte() != DONE)
		;

}
void Main_option(void) {
	uint8 opertaor, count;
	LCD_clearScreen();/*CLEAR SCREEN OF LCD*/
	LCD_displayString("+:OPEN DOOR");
	LCD_moveCursor(1, 0);
	LCD_displayString("-:CHANGE PASS");
	opertaor = KEYPAD_getPressedKey();
	_delay_ms(500);
	switch (opertaor) {

	case '+':
		LCD_clearScreen();/*CLEAR SCREEN OF LCD*/
		LCD_displayString("please enter pass:");
		LCD_moveCursor(1, 6);
		for (count = 0; count < NUMBER_OF_PASS; count++) {
			global_pass[count] = KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
			_delay_ms(500);
		}

		Uart_SENDCommand(Pass_check);
		UART_SENDPASS(global_pass);

		_delay_ms(200);

		if (Uart_RecieveCommand() == PASS_MATCH) {
			Uart_SENDCommand(OPEN_DOOR);
			/*screen is opening code*/
			LCD_clearScreen();/*CLEAR SCREEN OF LCD*/
			Timer_config Config = { Normal, F_CPU_1024, 0, 0 };
			Timer_init(&Config);
			Timer_Call_back(&tickk);
			LCD_displayString("door is unlocking");
			while (tick != fifteen_sec) {

			}
			LCD_clearScreen();
			while (tick != (fifteen_sec + three_sec)) {

			}
			LCD_displayString("door is locking");
			while (tick != (fifteen_sec + three_sec + fifteen_sec)) {

			}
			Timer_deinit();
			wrong_time = 0;
			state = 1;

		} else {
			wrong_time++;
			LCD_clearScreen();/*CLEAR SCREEN OF LCD*/
			LCD_displayString("wrong_pass");
			_delay_ms(500);
			Uart_SENDCommand(WRONG_PASS);
			if (wrong_time == 3) {
				wrong_time = 0;
				Uart_SENDCommand(activate_alert);
				LCD_Alert();

			}

		}

		break;

	case '-':

		LCD_clearScreen();/*CLEAR SCREEN OF LCD*/
		LCD_displayString("Enter old pass");
		LCD_moveCursor(1, 5);
		for (count = 0; count < NUMBER_OF_PASS; count++) {
			global_pass[count] = KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
			_delay_ms(500);
		}
		Uart_SENDCommand(Pass_check);
		UART_SENDPASS(global_pass);
		comm = Uart_RecieveCommand();
		if (comm == PASS_MATCH) {
			wrong_time = 0;
			flag_state = 0;
			state = 0;

		}
		if (comm == PASS_NOT_MATCH) {
			wrong_time++;
			state = 1;
			LCD_clearScreen();/*CLEAR SCREEN OF LCD*/
			LCD_displayString("wrong_pass");
			_delay_ms(500);
			if (wrong_time == 3) {
				wrong_time = 0;
				Uart_SENDCommand(activate_alert);
				LCD_Alert();

			}

		}

		break;
	}

}
void LCD_Alert(void) {

	LCD_clearScreen();/*CLEAR SCREEN OF LCD*/
	Timer_config Config = { Normal, F_CPU_1024, 0, 0 };
	Timer_init(&Config);
	tick = 0;
	Timer_Call_back(&tickk);
	LCD_displayString("ALERT!!");
	while (tick != one_min_ticks) {

	}
	LCD_clearScreen();
	tick = 0;
	wrong_time = 0;
	Timer_deinit();
	state = 1;

}
void tickk(void) {
	tick++;

}

void Saved_PassBeforRun(void) {
	uint8 Command_return;
	Uart_SENDCommand(Check_saved);
	Command_return=Uart_RecieveCommand();
	if(Command_return==Exist){
		state=1;

	}else{
		state=0;
	}



}
