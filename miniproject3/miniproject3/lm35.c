/*
 * lm35.c
 *
 *  Created on: May 26, 2022
 *      Author: mohmed salah
 */

#include "lm35.h"
#include "ADC.h"
/**/
uint8 LM35_getTemperature(void) {
	uint8 temp_value = 0;
	uint16 adc_readingValue = 0;
	adc_readingValue = ADC_readChannel(SENSOR_CHANNEL_ID);/* Read ADC channel where the temperature sensor is connected */
	temp_value = (uint8)(((uint32)adc_readingValue*SENSOR_MAX_TEMPERATURE*Vref)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));
	/*SENSOR READING EQUATION*/
	return temp_value;
}
