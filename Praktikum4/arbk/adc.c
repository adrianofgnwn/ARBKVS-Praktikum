/*
 * adc.c
 *
 * Created: 19.07.2024 14:46:29
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "adc.h"
#include "util.h"
#include <avr/io.h>

/*!
 * This method initializes the necessary registers for using the ADC module.
 * Reference voltage:    internal
 * Input channel:        PORTA7
 * Conversion frequency: 125kHz
 */
void adc_init()
{
	/* - - - ADMUX = ADC Multiplexer Selection Register - - -
	
	Bits 7:6 - REFSn = Reference Selection [n = 1:0]
	AVCC with external capacitor on AREF pin -> REFS[1:0] = 01
	
	Bits 3:0 - MUXn = Analog Channel Selection [n = 3:0]
	ADC7 -> MUX[3:0] = 0111
	
	*/
	ADMUX = (1 << REFS0) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
	
	/* - - - ADCSRA = ADC Control and Status Register A - - -
	
	Bit 7 - ADEN = ADC Enable
	
	Bit 5 - ADATE = ADC Auto Trigger Enable
	
	Bits 2:0 - ADPSn = ADC Prescaler Select [n = 2:0]
	128 -> ADPS[2:0] = 111
	
	*/
	ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	/* - - - ADCSRA = ADC Control and Status Register B - - -
	
	Bits 2:0 - ADTSn = ADC Auto Trigger Source [n = 2:0]
	ADATE in ADCSRA must be written to 1
	Free Running Mode -> ADTS[2:0] = 000; 
	
	*/
	ADCSRB = 0x00;
	
	/* - - - ADCSRA = ADC Control and Status Register A - - -
	
	Bit 6 - ADSC = ADC Start Conversation
	
	*/
	ADCSRA |= (1 << ADSC);
	
	 
	
}

/*!
 * Returns the ADC value of the last conversion
 * \return The converted voltage (0 = 0V, 1023 = AVCC)
 */
uint16_t adc_getValue()
{
	/* 
	ATmega locks both result register when ADCL is read.
	Reading ADCH unlocks them again. Correct order is required.
	*/
	
	uint8_t low = ADCL;
	uint8_t high = ADCH;
	
	return (high << 8) | low;
	
}