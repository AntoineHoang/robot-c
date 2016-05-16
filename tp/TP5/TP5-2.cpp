

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>: Interrupts

volatile uint8_t minuterieExpiree;

volatile uint8_t boutonPoussoir; 


ISR (TIMER1_COMPA_vect ) {

minuterieExpiree = 1;

}


ISR (INT0_vect) {

boutonPoussoir = 1;

_delay_ms (10);

if (PIND & 0x04)
  boutonPoussoir = 1;
else
  boutonPoussoir = 0;

}


void initialisation ( void ) {

// cli est une routine qui bloque toutes les interruptions.
// Il serait bien mauvais d'etre interrompu alors que
// le microcontroleur n'est pas pret...

cli ();

// configurer et choisir les ports pour les entrees
// et les sorties. DDRx... Initialisez bien vos variables

DDRD = 0xfb;

// cette procédure ajuste le registre GICR
// de ATMega16 pour permettre les interruptions externes

GICR |= _BV(INT0);

// il faut sensibiliser les interruptions externes aux
// changement de niveau du bouton-poussoir
// en ajustant le registre MCUCR

MCUCR |= _BV(ISC00); //Pour activer INT0 sur le port D2

// sei permet de recevoir a nouveau des interruptions.

sei ();

}

void partirMinuterie ( uint16_t duree ) {

minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisee par 1024

// interruption après la duree specifiee

TCNT1 = 0 ; //Compteur commence a 0

OCR1A = duree;

TCCR1A = 0;				// 
						// WGM 13-10 = 0100 pour CTC ( 12 et 13 sur B et 10 et 11 sur A)
TCCR1B = (1<<CS12)|(1<<CS10)|(1<<WGM12) ; 	// CS 12-10 = 101 pour clk/1024

TIMSK = _BV(OCIE1A) ; // OCIE1A = 1 pour enable OCF1A

}

int main () {
  
  
 initialisation();
 
 _delay_ms (2000); //Attendre 2 seconde avant le jeu
 
 PORTD = 0x02;//0000 0001
 _delay_ms (100);
  PORTD = 0x00;//0000 0000
 
 partirMinuterie(7812); // 8M / 1024
 
  do {
  } while (minuterieExpiree == 0 && boutonPoussoir == 0);

  cli ();


  if (boutonPoussoir == 1)
    PORTD = 0x01;//0000 0001
  else
    PORTD = 0x02;//0000 0010

  
}
