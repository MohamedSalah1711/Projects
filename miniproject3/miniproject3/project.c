/*
 * project.c
 *
 *  Created on: May 26, 2022
 *      Author: mohmed salha
 */
#include"PWM.h"
#include"ADC.h"
#include "lm35.h"
#include "lcd.h"
#include "motor.h"
#include "std_types.h"
int Reading_Sensor = 0; /*global vaiable to put reading sensor in*/
int main() {

	ADC_ConfigType Configration = { F_CPU_8, pooling, INTERNAL };/*ADC driver  configure to operate using the internal reference voltage 2.56
	 voltage and prescaler F_CPU/8*/
	ADC_init(&Configration); /*init the adc*/
	LCD_init(); /*init lcd*/
	LCD_displayStringRowColumn(0, 4, "FAN IS OFF"); /*display fan is of at the beggining*/
	LCD_displayStringRowColumn(1, 4, "TEMP =    C");
	DcMotor_Init(); /*init the dc motor*/
	while (1) {
		Reading_Sensor = LM35_getTemperature();/*get sensor temprature*/
		LCD_moveCursor(1, 10);/*move cursor at row 1 and coulmn 10*/
		/*******************************************************************************
		 *	                 SOLVE LCD PROBLEM WHEN READING >100 THEN <100				*
		 *******************************************************************************/
		if (Reading_Sensor >= 100) {
			LCD_intgerToString(Reading_Sensor);
		} else {
			LCD_intgerToString(Reading_Sensor);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		/*******************************************************************************
		 *                                PWM/ON/OF MOTOR                                  *
		 *******************************************************************************/
		if (Reading_Sensor >= 120) {
			LCD_displayStringRowColumn(0, 4, "FAN IS ON ");

			DcMotor_Rotate(CW, 100);

		} else if (Reading_Sensor < 120 && Reading_Sensor >= 90) {
			LCD_displayStringRowColumn(0, 4, "FAN IS ON ");

			DcMotor_Rotate(CW, 75);

		} else if (Reading_Sensor < 90 && Reading_Sensor >= 60) {
			LCD_displayStringRowColumn(0, 4, "FAN IS ON ");

			DcMotor_Rotate(CW, 50);

		} else if (Reading_Sensor < 60 && Reading_Sensor >= 30) {
			LCD_displayStringRowColumn(0, 4, "FAN IS ON ");

			DcMotor_Rotate(CW, 25);
		} else if (Reading_Sensor < 30) {

			LCD_displayStringRowColumn(0, 4, "FAN IS OFF");

			DcMotor_Rotate(off, 0);

		} else {
		}

	}

}
