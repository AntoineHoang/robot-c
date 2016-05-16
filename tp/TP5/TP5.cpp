/*
 * Nom: TP3 Probleme 1
 * Marc-Andre Gagnon, Antoine Hoang
 * Description: Machine a etats simples
 *
 *
 * Entree : L'interrupteur est a 0 ou 1
 * 
 * Etats :	000 : Rouge et initial
 *		001 : Ambre vers Vert
 * 		010 : Vert
 * 		011 : Ambre vers Eteint
 * 		100 : Eteint
 * 		101 : Ambre vers Rouge
 * 
 * Sortie :	00 : Eteint
 * 		01 : Vert
 * 		10 : Rouge
 * 		11 : Ambre
 * 
 * Dans le tableau qui suit, la sortie est associee a l'Etat suivants.
 *
 *
 * Entree	Etats presents	Etats suivants	Sortie
 * 
 * 0		000		000		10
 * 1		000		001		11
 * 0		001		010		01
 * 1		001		001		11
 * 0		010		010		01
 * 1		010		011		11
 * 0		011		100		00
 * 1		011		011		11
 * 0		100		100		00
 * 1		100		101		11
 * 0		101		000		10
 * 1		101		101		11
 * 
 * 
 */

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>: Interrupts

volatile uint8_t etat = 0;

ISR (INT0_vect) {

// laisser un delai avant de confirmer la reponse du
// bonton-poussoir: environ 30 ms (anti-rebond)

bool interrupteur = false;

_delay_ms (10);

// Se souvenir ici si le bouton est presse ou relache

if (PIND & 0x04){
      interrupteur = true;
  }

// changements d'etats tels que ceux de la
// semaine precedente

 switch (etat)
    {
    case 0: 
      
	if (interrupteur){
	  etat=1;
	} else {
	  etat=0;
	}
	break;
    case 1: 
	if (interrupteur){
	  etat=1;
	} else {
	  etat=2;
	}
	break;
    case 2: 
	if (interrupteur){
	  etat=3;
	} else {
	  etat=2;
	}
	break;
    case 3: 
	if (interrupteur){
	  etat=3;
	} else {
	  etat=4;
	}
	break;
    case 4: 
	if (interrupteur){
	  etat=5;
	} else {
	  etat=4;
	}
	break;
    case 5: 
	if (interrupteur){
	  etat=5;
	} else {
	  etat=0;
	}
	break;
    default: etat=0;
	break;
    }

// Voir la note plus bas pour comprendre cette instruction et son role

GIFR |= (1 << INTF0) ;

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




int main() {

  initialisation();
  
  for(;;){
    
    if (etat == 0)
      PORTD = 0x02; // 00 00 00 10
    else if (etat == 2)
      PORTD = 0x01; // 00 00 00 01
    else if (etat == 4)
      PORTD = 0x00; // 00 00 00 00
    else {
      PORTD = 0x02;
      _delay_ms (10);
      PORTD = 0x01;
      _delay_ms (5);
    }
    
  }
}