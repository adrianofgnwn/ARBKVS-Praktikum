/*
 * ledBar.h
 *
 * Created: 14.08.2024 16:27:00
 * Author : Fachbereich 5 - FH Aachen
 */ 
#ifndef LEDBAR_H_
#define LEDBAR_H_

#include <stdint.h>

//! Initialized PORTs connected to the LED bar
void ledBar_init();

//! Writes the LED bar to the PORTs
void ledBar_set(uint16_t leds);

//! Writes a value in percent as bar-graph
void ledBar_setProgress(uint8_t percent);

#endif /* LEDBAR_H_ */