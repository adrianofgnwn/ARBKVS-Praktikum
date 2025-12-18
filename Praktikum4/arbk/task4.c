/*
 * task4.c
 *
 * ADC: Convert a voltage and display it on the seven segment and on the LED bar
 *
 * Created: 19.07.2024 15:03:03
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "tasks.h"
#include "adc.h"
#include "sevenSeg.h"
#include "ledBar.h"

/*!
 * Display poti value on led-bar and 7-segments
 */
void task4()
{
	ledBar_init();
	adc_init();
	sevenSeg_init();
	
	while (1)
	{
		// Get adc value
		uint16_t adcValue = adc_getValue();
		
		// Convert adc value into LED value
		uint16_t ledValue = (adcValue * 10) / 1000;
		
		// Convert adc into float value
		float voltageValue = (adcValue * 5.0f) / 1023.0f;
		
		// Show LED
		ledBar_set(bar(ledValue));
	
		// Show SevenSeg
		sevenSeg_displayFloat(voltageValue);
		
		_delay_ms(100);
		
	}
}