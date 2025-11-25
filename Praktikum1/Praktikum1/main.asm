;
; Praktikum1.asm
;
; Created: 22.10.2025 13:48:43
; Author : ag4621s
;

;define
.include "m328pdef.inc"

.org 0x000		;reset vector
	rjmp setup


setup:
	;initialize stack pointer
    ldi r16, LOW( RAMEND )
	out SPL, r16
	ldi r16, HIGH( RAMEND )
	out SPH, r16

	;set LED port direction as output 
	ldi r16, 0b11111111
	ldi r17, 0b00000011
	out DDRD, r16				
	out DDRB, r17

start:
	;turn on first LED
	ldi r16, 0b00000001
	out PORTD, r16
	rcall delay200ms

Dshiftleft:
	;shift LED left
	lsl r16
	out PORTD, r16
	rcall delay200ms

	;branch or loop
	ldi r18, 0b10000000
	cp r16, r18
	breq Bshiftleft
	rjmp Dshiftleft

Bshiftleft:
	;turn off PORTD and turn on PORTB
	ldi r16, 0b00000000
	ldi r17, 0b00000001
	out PORTD, r16
	out PORTB, r17
	rcall delay200ms

	;shift LED left
	lsl r17
	out PORTB, r17
	rcall delay200ms

Bshiftright:
	;shift LED right
	lsr r17
	out PORTB, r17
	rcall delay200ms

	;turn off PORTB and turn on PORTD
	ldi r16, 0b10000000
	ldi r17, 0b00000000
	out PORTD, r16
	out PORTB, r17
	rcall delay200ms

Dshiftright:
	;shift LED right
	lsr r16
	out PORTD, r16
	rcall delay200ms

	;branch or loop
	ldi r18, 0b0000010
	cp r16, r18
	breq start
	rjmp Dshiftright
	
delay200ms:
	
	ldi r20, 32				; 1 Takt

	L1: ldi r21, 100		; 1 Takt
		
		L2: ldi r22, 250	; 1 Takt
			
			L3: nop			; 1 Takt
				dec r22		; 1 Takt
				brne L3		; 2 Takt beim Sprung, sonst 1 Takt

			dec r21			; 1 Takt
			brne L2			; 2 Takt beim Sprung, sonst 1 Takt

		dec r20				; 1 Takt
		brne L1				; 2 Takt beim Sprung, sonst 1 Takt

	ret						; 4 Takte
				

; TCycle = 1/FCPU = 1/16 MHz = 62,5 ns
; Cycles = TDelay/TCycle = 200 ms/62,5 ns = 3.200.000 Takte

;L3
;r22 wird mit 250 initialisiert		1	* 1 Takt
;nop								250 * 1 Takt
;r22 wird dekrementiert				250 * 1 Takt
;(brne)
;Wenn r22 > 0	-> Sprung zu L3		249 * 2 Takte
;Sonst			-> Nächste Zeile	1	* 1 Takt
;Insgesamt = 1000 Takte

;L2
;r21 wird mit 100 initialisiert		1	* 1 Takt
;Innere Schleife wird ausgeführt	100	* 1000 Takte
;r22 wird dekrementiert				100 * 1 Takt
;(brne)
;Wenn r22 > 0	-> Sprung zu L2		99	* 2 Takte
;Sonst			-> Nächste Zeile	1	* 1 Takt
;Insgesamt = 100.300 Takte

;L1
;r20 wird mit 32 initialisiert		1	* 1 Takt
;Innere Schleife wird ausgeführt	32	* 100.300 Takte
;r22 wird dekrementiert				32	* 1 Takt
;(brne)
;Wenn r22 > 0	-> Sprung zu L2		31	* 2 Takte
;Sonst			-> Nächste Zeile	1	* 1 Takt
;Insgesamt = 3.209.696 Takte

;rcall	3 Takte
;ret	4 Takte
;Gesamtlaufzeit = 3.209.696 + 4 + 3 = 3.209.703

; TDelay =  Cycles * TCycle = 3.209.703 * 62,5 ns = 200,6 ms
	

