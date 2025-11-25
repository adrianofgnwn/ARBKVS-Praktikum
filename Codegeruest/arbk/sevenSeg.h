/*
 * sevenSeg.h
 *
 * Created: 19.07.2024 14:45:44
 * Author : Fachbereich 5 - FH Aachen
 */ 
#ifndef SEVENSEG_H_
#define SEVENSEG_H_

#include <stdint.h>

//! Initializes 7-segment pins and update timer
void sevenSeg_init();

//! Displays a decimal on the 7-segments
void sevenSeg_displayDecimal(uint8_t value);

//! Displays a float on the 7-segments
void sevenSeg_displayFloat(float value);


#endif /* SEVENSEG_H_ */