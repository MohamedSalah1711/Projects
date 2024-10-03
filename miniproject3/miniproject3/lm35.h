/*
 * lm35.h
 *
 *  Created on: May 26, 2022
 *      Author: mohmed salha
 */

#ifndef LM35_H_
#define LM35_H_
#include "gpio.h"
#include "std_types.h"
#include "commonmacro.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LM35_pin PIN2_ID
#define LM35_port PORTA_ID
#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void);
#endif /* LM35_H_ */
