#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>: Interrupts

void initialisationPWM() {
	
	TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10);	// COM1A1 pour comparaison sur OC1A
													// WGM 13-10 = 0001 pour PWM 1 ( 12 et 13 sur B et 10 et 11 sur A)
	TCCR1B = (1<<CS11);								// CS 12-10 = 010 pour clk/8
													
}

void ajustementPWM (uint8_t A, uint8_t B) {

	OCR1A = A ;

	OCR1B = B ;

}
