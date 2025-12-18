/*
 * ledBar.c
 *
 * Created: 14.08.2024 16:26:52
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "ledBar.h"
#include <avr/io.h>

/*!
 * Initialized PORTs connected to the LED bar
 */
void ledBar_init()
{
	DDRD = 0b11111111;
	// DDRB |= 0b00000011;
	DDRB |= (1 << 0) | (1 << 1); 
	
}

/*!
 * Writes the LED bar to the PORTs
 */
void ledBar_set(uint16_t leds)
{
	// Lower 8 Bits from leds to PORTD
	PORTD = (uint8_t) leds;
	
	// Only change bit 0 and 1 of PORTB
	PORTB = (PORTB & ~((1 << 0) | (1 << 1))) | ((leds >> 8) & ((1 << 0) | (1 << 1)));
}

/*!
 * Takes a number from 0 to 10 and returns a bar with the given number of ones
 */
uint16_t bar(uint8_t n) { return ((int16_t)0x8000 >> (15 - n)) ^ 0xFFFF; }

/*!
 * Writes a value in percent as bar-graph
 */
void ledBar_setProgress(uint8_t percent)
{
	// Round 0 - 100 to 0 - 10 and get a bar graph 
	ledBar_set(bar((percent + 5) / 10));
}