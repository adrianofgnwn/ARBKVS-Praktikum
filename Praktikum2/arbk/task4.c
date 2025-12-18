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
		
	}
}