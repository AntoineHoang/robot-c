
#ifndef MOTEUR_H
#define MOTEUR_H

#include "roue.h"
#include <avr/io.h>
class Moteur {

private:

  uint8_t vitesseActuelle;
  accelerer();
  setMode(); //avancer ou reculer.
  
 
public: 

  arreter();
  setVitesseA(uint8_t direction, uint8_t vitesse);
  
  
  Moteur(uint16_t diviseurCompteur, unsigned char OCRv, uint8_t direction) {
  ~Moteur();
    
}

#endif