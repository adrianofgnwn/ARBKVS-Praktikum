/*
 * tasks.h
 *
 * Created: 18.07.2024 15:53:04
 * Author : Fachbereich 5 - FH Aachen
 */ 
#ifndef TASKS_H_
#define TASKS_H_

#include "util.h"
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

//! Game over types
typedef enum
{
	GAME_OVER_OUT_OF_BOUNDS,
	GAME_OVER_TOO_EARLY
} gameover_t;

//! Direction of moving light
typedef enum
{
	DIR_LEFT  = 0,
	DIR_RIGHT = 1
} direction_t;

//! Outer region is where the player can change direction, inner where he should not
#define LED_BAR_OUTER			0b1100000011
#define LED_BAR_INNER			0b0011111100

//! Speed of LED bar starts at 200 ms and is decreased by 10 % per level
#define DELAY_INITIAL_MS		200
#define DELAY_DECREMENT_FACTOR	0.9

//! Shows a game over animation to the player
void gameOverAnimation(gameover_t type);

//! Shows the high-score on the LED bar
void showScore(uint8_t level);

//! Task 2
void task2();

//! Task 3
void task3();

//! Task 4
void task4();

#endif /* TASKS_H_ */