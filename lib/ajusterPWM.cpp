#include <avr/io.h>
void ajusterPWM (uint8_t A, uint8_t B) {

	// TCCR1A et TCCR1B doivent �tre initialis�s avant l'utilisation de cette fonction

	OCR1A = A  ;

	OCR1B = B * 0.873;

}