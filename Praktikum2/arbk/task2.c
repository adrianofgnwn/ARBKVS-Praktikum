/*
 * task2.c
 *
 * LED bar animation: Run a light from left to right and vice versa with increasing speed
 *
 * Created: 18.07.2024 15:53:14
 * Author : Fachbereich 5 - FH Aachen
 */
#include "tasks.h"
#include "ledBar.h"
#include "button.h"

//! Forward declarations
void task2_init();
void task2_barAnimation();

/*!
 * Main task that starts and ends a game
 */
void task2()
{
	// Init ports
	task2_init();
	
	while (1) { task2_barAnimation(); }
}

/*!
 * Initializes PORTs
 */
void task2_init()
{
	ledBar_init();
	button_init();
}

/*!
 * Animation of the LED bar
 */
void task2_barAnimation()
{
	// Hilfsvariablen
	uint16_t ledBar = 0b0000000001;
	direction_t direction = DIR_LEFT;
	uint16_t delay = DELAY_INITIAL_MS;
	
	// Start: wait for button press and release
	// Keep looping until button is pressed
	// PINC reads pin states
 	while (PINC & 0b00100000) {}
 	while (!(PINC & 0b00100000)) {}
	
	while (1)
	{
		 // uint16_t ledBar = gbi ( PINC , PINC5 ) ? 0x00 : 0x3FF ;
		 // ledBar_set ( ledBar ) ;
		 
		 
		 ledBar_set(ledBar);
		 
		 // Manual Loop for Delay
		 for (uint16_t i = 0; i < delay; i++) {
			 _delay_ms(1); // _delay_ms() only accepts constants
		 }
		 
		 // Direction Change
		 if ((ledBar == 0b0000000001 && direction == DIR_RIGHT) || (ledBar == 0b1000000000 && direction == DIR_LEFT)) {
			 if (direction == DIR_LEFT) {
				 direction = DIR_RIGHT;
			 } else {
				 direction = DIR_LEFT;
			 }
			 // Delay Faster
			 delay *= DELAY_DECREMENT_FACTOR;
		 }
		 
		 // Shift
		 if (direction == DIR_LEFT) {
			 ledBar <<= 1;
		 } else {
			 ledBar >>= 1;
		 }
		 
		 // Safety mask so only lower 10 bits are used
		 ledBar &= 0b0000001111111111;
		 
		 // If too fast
		 if (delay < 2) {
			 // Turn on all LEDs
			 ledBar_set(0b0000001111111111);
			 return;
		 }
		 
	}
}