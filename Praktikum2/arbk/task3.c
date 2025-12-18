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
	// Current state of the LED bar
	
	// LED shift direction
	
	// Shift delay of game level 0 in ms
	
	// Reset game level
	
	while (1)
	{
		
	}	
}