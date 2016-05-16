/*
 * Nom: TP3 Probleme 2
 * Marc-Andre Gagnon, Antoine Hoang
 * Description: Machine a etats simples
 */



/* Entree : 	L'interrupteur est a 0 ou 1
 * 		Les delais font aussi changer les etats
 * 
 * Etats :	000 : Clignotement
 *		001 : Attente d'une seconde pour reussir
 * 		010 : Reussite
 * 		011 : Attente apres une seconde (perdu)
 * 		100 : Perdu
 * 
 * Sortie :	00 : Eteint
 * 		01 : Vert
 * 		10 : Rouge
 * 
 * Dans le tableau qui suit, la sortie est associee a l'Etat suivants.
 *
 *
 * Entree		Etats presents	Etats suivants	Sortie
 * 
 * 1/10 de seconde	000		001		10
 * 
 * Interrupteur 1	001		010		00
 * Interrupteur 0
 * pendant 1 seconde	001		011		00
 * 
 * 			010		010		01
 * 
 * Interrupteur 0	011		011		00
 * 
 * Interrupteur 1	011		100		00
 * 
 * 			100		100		10
 * 
 * 
 */

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

int main () {
  
  enum Etat {
    DEBUT,
    JEU,
    REUSSI,
    ATTENTE,
    PERDU
  };
  
  enum Etat etat = DEBUT;
  uint8_t t;

  DDRD = 0xfb; // PORT D2 est en mode entree 11111011. D0 et D1 sont utilise en sortie.
  _delay_ms (10000);




for(;;){
     

 switch (etat)
    {
    case DEBUT: 
	PORTD = 0x02; // 00 00 00 10
	_delay_ms (100);
	etat=JEU;
	break;
    case JEU:
	PORTD = 0x00; // 00 00 00 00
	etat = ATTENTE;
	for (t = 0; t < 200; t++){
	  _delay_ms(5.0);
	  if (PIND & 0x04){
	      etat = REUSSI;
	      break;
	  }
	}
	break;
    case REUSSI:
	  PORTD = 0x01; // 00 00 00 01
	  break;
    case ATTENTE:
        PORTD = 0x00; // 00 00 00 00
        if (PIND & 0x04){
	  etat=PERDU;
	}
        break;
    case PERDU:
	PORTD = 0x02; // 00 00 00 10  
	break;
    default: etat=DEBUT;
	break;
    } 
    
}

  
  
  
}