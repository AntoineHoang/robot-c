/*
 * Nom: TP3 Probleme 1
 * Marc-Andre Gagnon, Antoine Hoang
 * Description: Machine a etats simples
 */

/* Entree : L'interrupteur est a 0 ou 1
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

int main() {
  
  enum Etat {
    ROUGE,
    AMBRE1,
    VERT,
    AMBRE2,
    ETEINT,
    AMBRE3
  };
  
 
  Etat etat = ROUGE;
  DDRD = 0xfb; // PORT D2 est en mode entree 11111011. D0 et D1 sont utilise en sortie.
  bool interrupteur = false;
  
  for(;;){
    
    if (PIND & 0x04){
      _delay_ms (10);
	if (PIND & 0x04){
	  interrupteur = true;
	}
    } else {
      interrupteur = false;
    }
    
    switch (etat)
    {
    case ROUGE: 
      
	if (interrupteur){
	  etat=AMBRE1;
	} else {
	  etat=ROUGE;
	}
	break;
    case AMBRE1: 
	if (interrupteur){
	  etat=AMBRE1;
	} else {
	  etat=VERT;
	}
	break;
    case VERT: 
	if (interrupteur){
	  etat=AMBRE2;
	} else {
	  etat=VERT;
	}
	break;
    case AMBRE2: 
	if (interrupteur){
	  etat=AMBRE2;
	} else {
	  etat=ETEINT;
	}
	break;
    case ETEINT: 
	if (interrupteur){
	  etat=AMBRE3;
	} else {
	  etat=ETEINT;
	}
	break;
    case AMBRE3: 
	if (interrupteur){
	  etat=AMBRE3;
	} else {
	  etat=ROUGE;
	}
	break;
    default: etat=ROUGE;
	break;
    }
    
    if (etat == ROUGE)
      PORTD = 0x02; // 00 00 00 10
    else if (etat == VERT)
      PORTD = 0x01; // 00 00 00 01
    else if (etat == ETEINT)
      PORTD = 0x00; // 00 00 00 00
    else {
      PORTD = 0x02;
      _delay_ms (10);
      PORTD = 0x01;
      _delay_ms (5);
    }
    
  }
}