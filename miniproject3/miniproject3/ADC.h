	/*
 * ADC.h
 *
 *  Created on: May 25, 2022
 *      Author: mohmed salah
 */

#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"
#define ADC_MAXIMUM_VALUE    1023
#define Vref 2.56
/*******************************************************************************
 *                      ENUMS                                                  *
 *******************************************************************************/
typedef enum {
	F_CPU_2 = 1, F_CPU_4, F_CPU_8, F_CPU_16, F_CPU_32, F_CPU_64, F_CPU_128
} F_ADC;
typedef enum {
	pooling, interrupt
} ADC_FLAG;
typedef enum {
	AREF, AVCC, REVERSED, INTERNAL
} ADC_Ref;
/*******************************************************************************
 *                      STRUCTURES                                             *
 *******************************************************************************/
typedef struct {
	F_ADC Frequency;
	ADC_FLAG Flag;
	ADC_Ref REFRENCE;
} ADC_ConfigType;
/*******************************************************************************
 *                      Functions DEClration                                  *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType *Config_Ptr);
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver BY POOLING.
 */
uint16 ADC_readChannel(uint8 channel);
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver BY interrupt.
 */

void ADC_readChannelInterrupt(uint8 channel);

#endif /* ADC_H_ */
