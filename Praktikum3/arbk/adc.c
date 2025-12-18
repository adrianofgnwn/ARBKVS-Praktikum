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
	
}

/*!
 * Returns the ADC value of the last conversion
 * \return The converted voltage (0 = 0V, 1023 = AVCC)
 */
uint16_t adc_getValue()
{
	
}