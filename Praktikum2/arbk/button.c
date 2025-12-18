/*
 * button.c
 *
 * Created: 14.08.2024 16:31:59
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "button.h"
#include "util.h"
#include <avr/io.h>
#include <util/delay.h>

/*!
 * Initialized button pin
 */
void button_init()
{
	// Active-Low-Logik
	
	// DDRC &= 0b11011111;
	// Only set bit 5 as Input
	DDRC &= ~(1 << 5);
	
	// PORTC |= 0b00100000;
	PORTC |= (1 << 5);
	
	// Weil der Taster mit einem Kondensator verbunden ist und sich dieser zunaächst über den Pull-Up-Wiederstand des Mikrocontrollers aufladen muss
	_delay_ms(5);
}

/*!
 * Waits for the button to be pressed for max. timeout_ms milliseconds.
 * After that, it waits until the button is released again
 */
bool button_waitForPressRelease(uint16_t timeout_ms)
{
	while (timeout_ms-- > 0)
	{
		// Check if button has been pressed
		if (!gbi(PINC, PINC5))
		{
			// Wait for button to be released
			while (!gbi(PINC, PINC5));
			return true;
		}
		
		// Wait one millisecond
		_delay_ms(1);
	}
	
	// Timeout expired
	return false;
}