/*
 * Classe	: midi
 * 
 * Language	: C++ selon avrlibc pour avr-gcc. iso std98.
 * 
 * Dependances	: Interrupt
 * 
 * Format 	: midi5Alive 1.0
 * 
 * Auteurs	: Bartholomew Chwalek,
 * 
 * Date 	: 16-mars-2012 
 * 
 * Description :
 * 
 * 
 * 
 * 
 * 
 */

#ifndef MIDI_H
#define MIDI_H

#include <avr/io.h>


class midi {

private:
  
  volatile uint16_t compte2;
  uint8_t pins;
  uint8_t noteMask;
  
  volatile uint8_t *TCControlReg;
  volatile uint8_t *TCCountReg;
  volatile uint8_t *OutputCompReg;
  
  volatile uint8_t *port;
  uint8_t utiliserSortieAlternative;
  volatile uint16_t compte;
  uint8_t notePresente;
  uint8_t repetitions;
  volatile uint8_t * seq;
  volatile uint8_t * seqT;
  uint8_t seqC;
  uint8_t seqL;
  uint8_t seqPlay;
  uint8_t IntEnable;
  
public:

  midi(uint8_t timer,volatile uint8_t *portA, volatile uint8_t *ddr, uint8_t pinsA, uint8_t alternative);
 
  ~midi();
  

  void jouerNote(uint8_t note=0, uint8_t duree=0);
  void jouerSequenceT(uint8_t cut,uint8_t nbrepetitions,volatile uint8_t * sequence,volatile uint8_t * duree, uint8_t longueur);

  void resetPins();
  void ISR_compare(); 
  void ISR_compareAlternative();
  void arreterNote();
  void stoptimer();
  void silence(uint8_t duree);
  
};

#endif
