/*
 * Second_Ecu.c
 *
 *  Created on: Jul 22, 2022
 *      Author: mohmed salha
 */
#include "Second_Ecu.h"
int main() {

	/***********************UART INITIZLIZE*********************************/
	UART_ConfigType Uart_config = { DATA_BIT_8, DISABLED, STOP_BIT_1, 9600 };
	UART_init(&Uart_config);
	/*****************************************************************/
	/*****************************twi init**********************************/
	TWI_init(400000, 0b00000010);
	SREG |= (1 << 7);

	Timer_config Config = { Normal, F_CPU_1024, 0, 0 };
	while (1) {
		recived_command = Uart_RecieveCommand();
		if (recived_command == PASS_SEND) {
			UART_RecivePASS(Global_pass);
		}
		if (recived_command == SECOND_PASS) {
			UART_RecivePASS(Re_Global_pass);
			if (Compare_two_pass_in_state0(Global_pass, Re_Global_pass)) {
				write_pass_EEprom(Global_pass);
				read_pass_eeprom_store_it(passeeprom);
				_delay_ms(500);

				Uart_SENDCommand(PASS_MATCH);
			} else {
				Uart_SENDCommand(PASS_NOT_MATCH);
			}
		}
		if (recived_command == Pass_check) {
			UART_RecivePASS(Global_pass);
			if (Compare_two_pass_in_state0(Global_pass, passeeprom)) {

				Uart_SENDCommand(PASS_MATCH);
			} else {

				Uart_SENDCommand(PASS_NOT_MATCH);

			}

		}
		if (recived_command == OPEN_DOOR) {
			DcMotor_Init();

			Timer_init(&Config);
			Timer_Call_back(&tick_for_motor);
			DcMotor_Rotate(CW);
			while (tick != fifteen_sec)
				;
			DcMotor_Rotate(off);
			while (tick != (fifteen_sec + three_sec))
				;
			DcMotor_Rotate(A_CW);
			while (tick != (fifteen_sec + fifteen_sec + three_sec))
				;
			DcMotor_Rotate(off);
			Timer_deinit();

		}
		if (recived_command == activate_alert) {
			Buzzer_init();
			Timer_init(&Config);
			Timer_Call_back(&tick_for_motor);
			Buzzer_On();
			while (tick != one_min_ticks)
				;
			Buzzer_off();
		}
		if (recived_command == Check_saved) {
			read_pass_eeprom_store_it(passeeprom);
			uint8 count = 0;
			for (uint8 i = 0; i < NUMBER_OF_PASS; i++) {
				if (passeeprom[i] == 255) {
					count++;
				}

			}

			if (count == NUMBER_OF_PASS) {
				Uart_SENDCommand(Not_Exist);

			} else {

				Uart_SENDCommand(Exist);
			}

		}

	}
	return 0;
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
void UART_RecivePASS(uint8 arr[]) {
	uint8 count;
	while (UART_recieveByte() != READY)
		;
	UART_sendByte(READY);
	for (count = 0; count < NUMBER_OF_PASS; count++) {
		arr[count] = UART_recieveByte();
	}

	UART_sendByte(DONE);

}
uint8 Compare_two_pass_in_state0(uint8 arr[], uint8 arr1[]) {
	uint8 count = 0, flag = 0;
	for (count = 0; count < NUMBER_OF_PASS; count++) {
		if (arr[count] != arr1[count]) {
			flag++;
			break;
		}
	}
	if (flag == 1) {
		flag = 0;
		return FALSE;
	} else
		return TRUE;

}
void write_pass_EEprom(uint8 arr[]) {
	uint8 count = 0;
	for (count = 0; count < NUMBER_OF_PASS; count++) {
		EEPROM_writeByte(0x0311 + count, arr[count]);
		_delay_ms(20);
	}

}
void read_pass_eeprom_store_it(uint8 arr[]) {
	uint8 count = 0;
	for (count = 0; count < NUMBER_OF_PASS; count++) {
		EEPROM_readByte(0x0311 + count, &arr[count]);
		_delay_ms(100);
	}

}

void tick_for_motor(void) {
	tick++;
}

