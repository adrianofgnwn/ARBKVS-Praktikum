/*
 * tasks.c
 *
 * Created: 19.07.2024 14:16:36
 * Author : Fachbereich 5 - FH Aachen
 */
 #include "tasks.h"
 #include "ledBar.h"

/*!
 * Shows a game over animation to the player
 */
void gameOverAnimation(gameover_t type)
{
	uint16_t ledBar;
	
	// Running out of bounds is shown by the outer LEDs on
	// Pressing the button in the inner region is shown by the inner LEDs on
	if (type == GAME_OVER_OUT_OF_BOUNDS) { ledBar = LED_BAR_OUTER; }
	else { ledBar = LED_BAR_INNER; }
	
	// Game over animation
	for (uint8_t i = 0; i < 3; i++)
	{
		// 500 ms: Inner or outer LEDs on (depending on game over reason)
		ledBar_set(ledBar);
		_delay_ms(500);
		
		// 500 ms: All off
		ledBar_set(0);
		_delay_ms(500);
	}
}

/*!
 * Shows the high-score on the LED bar
 */
void showScore(uint8_t level)
{
	ledBar_setProgress(level * 5);
}