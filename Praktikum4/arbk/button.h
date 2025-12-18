/*
 * button.h
 *
 * Created: 14.08.2024 16:32:07
 * Author : Fachbereich 5 - FH Aachen
 */ 
#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdbool.h>
#include <stdint.h>

//! Initialized button pin
void button_init();

//! Waits for the button to be pressed for max. timeout_ms milliseconds.
bool button_waitForPressRelease(uint16_t timeout_ms);

#endif /* BUTTON_H_ */