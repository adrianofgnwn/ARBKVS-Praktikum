/*
 * sevenSeg.c
 *
 * Created: 19.07.2024 14:44:45
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "sevenSeg.h"
#include "util.h"
#include <avr/interrupt.h>
#include <stdbool.h>

//! Port definitions
//! 7-Segment switch
#define SEVENSEG_DDR_SW		DDRB
#define SEVENSEG_PORT_SW	PORTB
#define SEVENSEG_IDX_SW		PORTB4

//! 7-Segment a, b, c, d, e, f, g, DP
const uint8_t sevenSeg_segIdxTable[8] = { PORTB5, PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTB2, PORTB3 };

//! Returns pin-index for given segment index
inline volatile uint8_t sevenSeg_segIDX(uint8_t idx)
{
	return sevenSeg_segIdxTable[idx];
}

//! Returns DDR-reference for given segment index
inline volatile uint8_t* sevenSeg_segDDR(uint8_t idx)
{
	if (idx > 0 && idx < 6) { return &DDRC; }
	else                    { return &DDRB; }
}

//! Returns PORT-reference for given segment index
inline volatile uint8_t* sevenSeg_segPORT(uint8_t idx)
{
	if (idx > 0 && idx < 6) { return &PORTC; }
	else                    { return &PORTB; }
}

//! Bit masks for 7-seg
uint8_t digits[10] =
{
	0b11000000, // 0
	0b11111001, // 1
	0b10100100, // 2
	0b10110000, // 3
	0b10011001, // 4
	0b10010010, // 5
	0b10000010, // 6
	0b11111000, // 7
	0b10000000, // 8
	0b10010000, // 9
};

//! Currently shown value
volatile uint8_t sevenSegValue;

//! Needs the dot of first 7-seg to be switched on?
volatile bool sevenSegDot;

//! Forward declarations
void sevenSeg_set(uint8_t segment);

/*!
 * Switches between both 7-seg and displays either tens or ones digit
 * on correspondig 7-seg.
 * Switching is done with 16 MHz / prescaler 256 / OVF 256 = ~244 Hz
 */
ISR(TIMER0_OVF_vect)
{

}

/*!
 * Takes a bit-mask with DP, a - f and writes it to the individual hardware pins
 */
void sevenSeg_set(uint8_t segment)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		ubi(*sevenSeg_segPORT(i), sevenSeg_segIDX(i), gbi(segment, i));
	}
}

/*!
 * Initializes 7-segment pins and update timer
 */
void sevenSeg_init()
{
	// Init switch between tens and ones digit
	sbi(SEVENSEG_DDR_SW, SEVENSEG_IDX_SW);
	
	// Set all 7-Seg pins to output
	for (uint8_t i = 0; i < 8; i++)
	{
		sbi(*sevenSeg_segDDR(i), sevenSeg_segIDX(i));
	}
	
	// Init Timer 0
	
	// Enable global interrupts
	sei();
}

/*!
 * Displays a decimal on the 7-segments
 */
void sevenSeg_displayDecimal(uint8_t value)
{
	if (value > 99) { value = 99; }
	
	sevenSegValue = value;
	sevenSegDot = false;
}

/*!
 * Displays a float on the 7-segments
 */
void sevenSeg_displayFloat(float value)
{
	
}