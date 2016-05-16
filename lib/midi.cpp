
/*
 * Implementation de la classe midi.
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
 * 	Format
 * 
 * 		Les valeurs de comparaisons dans le tableau sont des approximations pour
 * 		un cpu cadencé à 8000000hz avec un diviseur de clk de 64.
 * 
 * 		Ces valeurs sont les TOP de chaque note débutant par B3 ou la note 0.
 * 		Quand le TOP est atteint par le compteur/timer, une interruption est générée.
 * 		À cette interruption, la pin OC0 est bifurquée, xor ou toggled.
 * 		Ainsi donc le temps entre deux interruptions correspond à la moitié d'une période
 * 		ce qui crée une onde carée avec 50% duty cycle.
 * 
 * 		Les valeurs sont des approximations basées sur la relations logarithmique
 * 		de base 2 entre les fréquences des notes consécutives.
 * 
 * 		Le délais occasionné par les instructions dans jouerNote et la routine
 * 		d'interruption devront être compensées dans une version future.
 * 
 * 		Pré-conditions:
 * 
 * 		La routine midi::ISR_compare() doit être appelée par la bonne interruption 
 * 		dans le programme principal (sur TIM0_COMP_vect).
 * 
 * 		Les interruptions doivent être enabled : sei();
 * 
 * 		Attention: les sons joués le sont de manière asynchrone aux autres processus.
 * 		Seules les instructions dans l'interruption vont marquer la cadence synchrone
 * 		des autres processus. Pour l'instant, nous sommes limités à une seule voix et
 * 		la nécessité de réguler parfois les séquences manuellement avec des délais.
 * 
 * 
 */

#define timer TIMER1
#include "midi.h"
#include <stdlib.h>
#include <avr/delay.h>
#include <avr/signal.h>
#include <avr/interrupt.h>

// -------------------------- DEFINITIONS POUR FICHIER OU ON UTILISE LA CLASSE. -----------------
/*enum midi_notes { B3,C3,Cd3,D3,Dd3,E3,F3,Fd3,G3,Gd3, \
	     A4,Ad4,B4,C4,Cd4,D4,Dd4,E4,F4,Fd4,G4,Gd4, \
	     A5,Ad5,B5,C5,Cd5,D5,Dd5,E5,F5,Fd5,G5,Gd5, \
	     A6, S };*/
#define B3 0
#define C3 1
#define Cd3 2
#define D3 3
#define Dd3 4
#define E3 5
#define F3 6
#define Fd3 7
#define G3 8 
#define Gd3 9
#define A4 10
#define Ad4 11
#define B4 12
#define C4 13
#define Cd4 14
#define D4 15
#define Dd4 16
#define E4 17
#define F4 18
#define Fd4 19
#define G4 20
#define Gd4 21
#define A5 22
#define Ad5 23
#define B5 24
#define C5 25
#define Cd5 26
#define D5 27
#define Dd5 28
#define E5 29
#define F5 30
#define Fd5 31
#define G5 32
#define Gd5 33
#define A6 34

#define SIL 35
// ------------------------ FIN -----------------------------------------------------------------


//35 notes élémentaires par valeur de compte TOP avec un prescale de 64.
 // compte avec prescaler de 64.
 // valeurs pour 100ms
static uint8_t valsOrig[] = {253,239,226,213,201,190,179,169,160,151,142,134,127,120,113,106,101,95,90,85,80,75,71,67,63,60,56,53,50,47,45,42,40,38,36,253}; // premiere note = B3

//ci-dessous sont les valeurs compensées après expérimentations sur oscilloscope. (En phase expérimentale)
static uint8_t vals[] = {252,239,226,213,201,190,179,169,160,151,142,134,127,120,113,106,101,95,90,85,80,75,71,67,63,60,56,53,50,47,45,42,40,38,36,253};

//35 valeurs correspondantes de répétitions du comptage / nb d'interruptions pour atteindre un temps de 100ms.
static uint8_t valsRep[] = {25,26,28,29,31,33,35,37,39,42,44,47,49,52,55,59,62,66,70,74,78,83,88,93,99,105,111,117,124,132,140,148,157,166,176,25};

void midi::resetPins() {
 	*port |= (1<<(pins+1));		// mettre 0b10 sur les deux pins utilisées.
	*port &= (unsigned char) ~(1<<(pins));  
  
}

midi::midi(uint8_t timer, volatile uint8_t *portA, volatile uint8_t *ddr, uint8_t pinsA, uint8_t alternative) 
{
  
	utiliserSortieAlternative = alternative;
  	pins = pinsA;
	port = portA;
	*ddr|=(1<<pinsA);	// Réserver 2 pin en mode sortie à partir de pinsA
	*ddr|=(1<<(pinsA+1));
	resetPins();
	


	
	if(timer==0)
	{
	  TCControlReg = &TCCR0;
	  TCCountReg = &TCNT0;
	  OutputCompReg = &OCR0;
	  IntEnable = 1;
	  *TCControlReg = (1<<WGM01)|(1<<CS01)|(1<<CS00)|(1<<COM00);
	} else
	{
	  TCControlReg = &TCCR2;
	  TCCountReg = &TCNT2;
	  OutputCompReg = &OCR2;	 
	  IntEnable = 7;
	  *TCControlReg = (1<<WGM21)|(1<<CS22)|(1<<COM20);
	}
	  
		; // mode CTC : quand counter atteind TOP (OCR0) clear counter, 64 prescale
							   // toggle pin OC0 quand counter atteind TOP
							   // générer une interruption quand counter atteind TOP.
		*OutputCompReg =0;	// Valeur initiale de comparaison = 0, compteur éteint.
		seqPlay = 0;	// En mode sequence = 0;
		*TCCountReg = 0;	// Valeur initiale du counter = 0;
	
  
}

midi::~midi() 
{
  
}



void midi::jouerNote(uint8_t note, uint8_t duree) {
      
      resetPins();
      noteMask=3;
      
 if((note>=0) && (note<35)) 
 {
      *TCControlReg |=(1<<COM00);
      compte = valsRep[note]*duree;
      *OutputCompReg  = vals[note];
      TIMSK |= (1<<IntEnable);

} else
 {
  switch(note)
  {
   
    case(35):
      noteMask = 0;
      compte = valsRep[note]*duree;
      *OutputCompReg = vals[note]; 
      *TCControlReg &= (unsigned char)~(1<<COM00);
    break;
    
  };
 }
  
}

void midi::silence(uint8_t duree) 
{
  
}

void midi::jouerSequenceT(uint8_t cut,uint8_t nbrepetitions,volatile uint8_t * sequence,volatile uint8_t * duree, uint8_t longueur) 
{

  if(seqPlay==0) {
    seqC = cut;
    seq = sequence;
    seqPlay = 1;
    seqT = duree;
    seqL = longueur;
    notePresente = 0;
    jouerNote(*(seq), *(seqT));
  }
}

  

void midi::ISR_compareAlternative() // Utiliser comme routine lors d'un ISR(TIM2_COMP_vect) 
{
  if(utiliserSortieAlternative)*port ^= (unsigned char)(noteMask << pins);
  
  ISR_compare();
}



void midi::ISR_compare() // Utiliser comme routine lors d'un ISR(TIM0_COMP_vect) 

{
  compte--;
  
  if(seqC!=0)
    if(compte==seqC){
         *TCControlReg &=(unsigned char)~(1<<COM00);
	 noteMask = 0;
    }
  if(compte==0)
  { 
      *TCControlReg |=(1<<COM00);

  if(seqPlay==1) 
  {
      notePresente++;

      if(notePresente<seqL) 
      {
	  *TCCountReg = 0;
	  jouerNote(*(seq+notePresente),*(seqT+notePresente));
	
      }else 
      {
	  seqPlay=0; 
	  stoptimer();
	  *TCCountReg = 0;
      }
      
    } else {stoptimer(); *TCCountReg = 0;}
  };
  
}

void midi::arreterNote() {
	
	stoptimer();
	
}

void midi::stoptimer() 
{
 *OutputCompReg = 0; 
 TIMSK &= ~(1<<IntEnable);
 *port &= (unsigned char) ~(3<<(pins)); 
  
}
