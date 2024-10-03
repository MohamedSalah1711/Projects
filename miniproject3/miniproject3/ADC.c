#include "ADC.h"
#include "gpio.h"
#include "commonmacro.h"
#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint16 g_adcResult = 0; /*global variable shared in many files*/
ISR(ADC_vect) /*ISR function*/
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}
void ADC_init(const ADC_ConfigType *Config_Ptr) {
	ADMUX = ((Config_Ptr->REFRENCE) << 6); /*Choose refernce*/
	ADCSRA |= (1 << ADEN); /*ENABLE ADC*/
	if ((Config_Ptr->Flag) == interrupt) {

		ADCSRA |= (1 << ADIE); /*Enable interrupt*/

	}
	ADCSRA |= (Config_Ptr->Frequency); /*choose pre_scaler*/
}

uint16 ADC_readChannel(uint8 channel) {
	channel &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX |= channel; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADCSRA |= (1 << ADSC); /* Start conversion write '1' to ADSC */
	while (BIT_IS_CLEAR(ADCSRA, ADIF)); /*pooling loop*/
	ADCSRA |= (1 << ADIF); /*clear flag*/
	return ADC; /*return the value of ADC*/
}

void ADC_readChannelInterrupt(uint8 channel) {
	channel &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX |= channel; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADCSRA |= (1 << ADSC);/* Start conversion write '1' to ADSC */

}
