#include <avr/io.h>
#include <util/delay.h>
#include "FonctionGlobales.h"

void initialiser(void)
{
  TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10);	// COM1A1 pour comparaison sur OC1A
						// WGM 13-10 = 0001 pour PWM 1 ( 12 et 13 sur B et 10 et 11 sur A)
  TCCR1B = (1<<CS11);	 			// CS 12-10 = 010 pour clk/8
  
  DDRD = 0xff;					//PORT D est en sortie
  
  PORTD = 0xC0;
}


int main()
{
  initialiser();
  
  ajusterPWM(150, 0);
  _delay_ms(1500);
  ajusterPWM(0, 0);
}