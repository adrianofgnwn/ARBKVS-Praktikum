/*
 * util.h
 *
 * Created: 18.07.2024 15:55:00
 * Author : Fachbereich 5 - FH Aachen
 */ 
#ifndef UTIL_H_
#define UTIL_H_

//! Set bit with index b in x
#define sbi(x, b) (x |= (1 << (b)))

//! Clear bit with index b in x
#define cbi(x, b) (x &= ~(1 << (b)))

//! Get bit with index b in x
#define gbi(x, b) (((x) >> (b)) & 1)

//! Invert bit with index b in x
#define ibi(x, b) (x ^= (1 << (b)))

//! Update bit with index b in x with value v
#define ubi(x, b, v) ((v) ? sbi(x, b) : cbi(x, b))

#endif /* UTIL_H_ */