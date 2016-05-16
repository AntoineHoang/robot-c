
#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>: Interrupts


void ajustementPWM (uint8_t A) {

// mise a un des etat sortie OC1A et OC1B sur comparaison

// reussie en mode PWM 8 bits, phase correcte

// et valeur de TOP fixe a 0xFF (mode #1 de la table 47

// page 112 de la description technique du ATMega16)

TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10);	// COM1A1 pour comparaison sur OC1A
						// WGM 13-10 = 0001 pour PWM 1 ( 12 et 13 sur B et 10 et 11 sur A)
TCCR1B = (1<<CS11);	 			// CS 12-10 = 010 pour clk/8

OCR1A = A ;

OCR1B = A ;


}

int main () {
  
  DDRD = 0xff;
  
  PORTD = 0xC0; // 1100 0000
  
  ajustementPWM (150);
  
  _delay_ms (100);
  
  ajustementPWM (60);
  
  _delay_ms (3000);
  
  ajustementPWM (110);
  
  _delay_ms (3000);
  
  ajustementPWM (160);
  
  _delay_ms (3000);
  
  ajustementPWM (210);
  
  _delay_ms (2000);
  
  ajustementPWM (0);
  
}