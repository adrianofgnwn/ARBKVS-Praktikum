/*
 * task3.c
 *
 * LED bar game: Run a light from left to right and vice versa with increasing speed,
 * the player has to press the button in time to change direction. Pressing is allowed
 * while the two outermost LEDs are on
 *
 * Created: 19.07.2024 14:09:26
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "tasks.h"
#include "ledBar.h"
#include "button.h"
#include "sevenSeg.h"

//! Game level
uint8_t level;

//! Forward declarations
void task3_init();
gameover_t task3_game();

/*!
 * Main task that starts and ends a game
 */
void task3()
{
	// Init ports
	task3_init();
	
	while (1)
	{
		// Play game
		gameover_t result = task3_game();
		
		// Game over animation
		gameOverAnimation(result);
		
		// Show reached level (display level / 2)
		showScore(level);
	}
}

/*!
 * Initializes PORTs
 */
void task3_init()
{
	ledBar_init();
	button_init();
	sevenSeg_init();
}

/*!
 * Game logic
 */
gameover_t task3_game()
{
	// Hilfsvariablen
	uint16_t ledBar = 0b0000000001; // First LED
	direction_t direction = DIR_LEFT; // Initial shift direction
	uint16_t delay = DELAY_INITIAL_MS; // Initial shift delay
	uint16_t ledMask = LED_BAR_INNER | LED_BAR_OUTER; // Bits used for LED bar
	level = 0;
	
	// Wait until SW1 is pressed and released
	while (!button_waitForPressRelease(5000)) {}
	
	// Reset game level
	sevenSeg_displayDecimal(level);
	
	while (1)
	{
		// Current state of the LED bar
		ledBar_set(ledBar);
	
		// SW1 is pressed
		if (button_waitForPressRelease(delay)) {
			
			// Invalid: Pressed too early
			if(ledBar & LED_BAR_INNER) {
				return GAME_OVER_TOO_EARLY;
			}
			
			// Valid press
			if ((ledBar & 0b0000000011) && direction == DIR_RIGHT) {
				direction ^= 1; // Toggle direction
				level++; // Update level
				sevenSeg_displayDecimal(level); // Update sevenSeg
				delay *= DELAY_DECREMENT_FACTOR; // Increase speed
					
			} else if ((ledBar & 0b1100000000) && direction == DIR_LEFT) {
				direction ^= 1; // Toggle direction
				level++; // Update level
				sevenSeg_displayDecimal(level); // Update sevenSeg
				delay *= DELAY_DECREMENT_FACTOR; // Increase speed
			}
		}
		
		// LED Shift
		if (direction == DIR_LEFT) {
			ledBar <<= 1;
		} else {
			ledBar >>= 1;
		}
		
		// Invalid: Not pressed / too Late
		if ((ledBar & ledMask) == 0) {
			return GAME_OVER_OUT_OF_BOUNDS;
		}
	}
}