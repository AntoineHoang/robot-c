/*
 * Nom: TP3 Probleme 1
 * Marc-Andre Gagnon, Antoine Hoang
 * Description: Machine a etats simples
 */

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

int main() {
 
  uint8_t etat = 0, prochainEtat = 0, sortie = 0;
  DDRD = 0xfb; // PORT D2 est en mode entree 11111011. D0 et D1 sont utilise en sortie.
  bool interrupteur = false;
  
  for(;;){  // boucle sans fin
    
    if (PIND & 0x04){
      _delay_ms (10);
	if (PIND & 0x04){
	  interrupteur = true;
	} else {
	  interrupteur = false;
	}
    }
    
    switch (etat)
    {
    case 0: 
	if (interrupteur){
	  prochainEtat=1;
	} else {
	  prochainEtat=0;
	}
	break;
    case 1: 
	if (interrupteur){
	  prochainEtat=1;
	} else {
	  prochainEtat=2;
	}
	break;
    case 2: 
	if (interrupteur){
	  prochainEtat=3;
	} else {
	  prochainEtat=2;
	}
	break;
    case 3: 
	if (interrupteur){
	  prochainEtat=3;
	} else {
	  prochainEtat=4;
	}
	break;
    case 4: 
	if (interrupteur){
	  prochainEtat=5;
	} else {
	  prochainEtat=4;
	}
	break;
    case 5: 
	if (interrupteur){
	  prochainEtat=5;
	} else {
	  prochainEtat=0;
	}
	break;
    default: prochainEtat=0;
	break;
    }
    etat = prochainEtat;
    
    if (etat == 0)
      PORTD = 0x10; // 00 00 00 10
    else if (etat == 2)
      PORTD = 0x01; // 00 00 00 01
    else if (etat == 4)
      PORTD = 0x00; // 00 00 00 00
    else {
      PORTD = 0x10;
      _delay_ms (2);
      PORTD = 0x01;
      _delay_ms (2);
    }
    
  }
}