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
	static bool showOnes = false;     // toggles between ones and tens
	uint8_t digitValue;
	uint8_t segMask;

	// toggle active display
	showOnes = !showOnes;

	if (showOnes) {
		// Activate display for ones digit
		cbi(SEVENSEG_PORT_SW, SEVENSEG_IDX_SW);   // one display
		digitValue = sevenSegValue % 10;         // ones
		segMask = digits[digitValue];
		
	} else {
		// Activate display for tens digit
		sbi(SEVENSEG_PORT_SW, SEVENSEG_IDX_SW);   // other display
		digitValue = sevenSegValue / 10;         // tens
		segMask = digits[digitValue];
		
		// Optional decimal point on the FIRST digit
		if (sevenSegDot) {
			// DP is highest bit; set to 0 to turn it on
			segMask &= ~(1 << 7);
		}
	}

	// Output bitmask to the segment pins
	sevenSeg_set(segMask);
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
	
	// Timer/Counter0 Control Register A - configures Waveform mode, output compare, etc.
	TCCR0A = 0x00; // Select normal mode, no PWM, no CTC
	
	// Timer/Counter0 Control Register B - controls prescaler & more mode bits
	// Reset the prescaler settings before choosing a new prescaler
	TCCR0B = 0x00;
	
	// Timer/Counter0 - actual 8-bit timer counting register
	// Initializes the actual 8-bit counter to 0
	TCNT0  = 0x00; // Count from 0

	// Prescaler 256 -> CS02 = 1, CS01 = 0, CS00 = 0
	// Timer0 runs at 16MHz / 256 = 62,500 Hz
	// Timer0 counts 256 steps (0 - 255), so overflow happens at 62,500 / 256 = 244 Hz 
	sbi(TCCR0B, CS02); // TCCR0B |= (1 << CS02);

	// Enable overflow interrupt
	// Timer/Counter Interrupt Mask Register 0 - enables interrupts for Timer0
	// Whenever Timer0 overflows (255 -> 0), the AVR will call: ISR(TIMER0_OVF_vect)
	sbi(TIMSK0, TOIE0); // TIMSK0 |= (1 << TOIE0); 
	
	
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