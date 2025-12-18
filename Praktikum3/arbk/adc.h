/*
 * adc.h
 *
 * Created: 19.07.2024 14:46:42
 * Author : Fachbereich 5 - FH Aachen
 */ 
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

//! This method initializes the necessary registers for using the ADC module
void adc_init();

//! Enables ADC. Needs to be called after adc_init()
void adc_enable();

//! Disables ADC
void adc_disable();

//! Executes one conversion of the ADC and returns its value
uint16_t adc_getValue();

#endif /* ADC_H_ */