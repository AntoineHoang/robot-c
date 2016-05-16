#include <avr/io.h>
#include <util/delay.h>
#include <avr/signal.h>
#include <avr/interrupt.h>
#include "del.h"
#include "midi.h"
#include "FonctionGlobales.h"
#define PINS12 0
#define PINS34 1
#define PINS56 2
#define PINS78 3

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






#define setOCR1A 0b00100000
#define setOCR1B 0b00010000
#define nOCR1A 0b11011111
#define nOCR1B 0b11101111

#define setBitM(port, n) ((port) |= (1<<(n)))
#define unsetBitM(port, n) ((port) &= (0xff<<(n))+(0xff>>((n)+1)))

void setBit(volatile uint8_t* port, uint8_t n){ *port|=(1<<n);}
void unsetBit(volatile uint8_t* port,uint8_t n){ *port&=(0xFF<<n)+(0xFF>>(n+1));};

volatile uint8_t furelise[] = {E4,Dd4,E4,Dd4,E4,B4,D4,C4,A4,C4,E4,A4,B4,E4,Gd4,B4,C4,E3,E5,Dd4,E4,Dd4,E4,B4,D4,C4,A4};
volatile uint8_t fureliseT[] = {4,4,4,4,4,4,4,4,8,4,4,4,6,4,4,4,6,4,4,4,4,4,4,4,4,4,8};//27 notes 
  
volatile uint8_t musiq1[] = {B3, B4, B5, A6, C3, C4, C5, B3, D4, D5, Fd5, F4, G4, C4 };
volatile uint8_t musiq1T[] = {5,   5,  5,  5,  5,  5,  5, 3,   5,  2,  7,  2,  8,  3 };
  
volatile uint8_t mario[] = {E4,SIL,E4,SIL,E4,SIL,C4,SIL,E4,SIL,G4,SIL,C4,G3,E3,A4,B4,Ad4,G3,E4,G4,A5,F4,G4,E4,C4,D4,B4,C4,G3,E3,A4,B4,Ad4,A4,G3,E4,G4,A5,F4};  
volatile uint8_t marioT[] = {3,  1, 2,  1, 3,  3, 3,  1, 2,  2, 8,  5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};
//L=37
  midi musique(&PORTB, &DDRB, 4,1);


void initialiser(void) {

  DDRB = 0xff; 			// PORT B est en mode sortie. (Pour la DEL).
  DDRD = 0x00; 			// PORT D est en mode entrée. (Pas utilise ici).
  DDRD |= setOCR1A;
  sei();

}


ISR(TIMER0_COMP_vect) {
  musique.ISR_compareAlternative();
  
}


ISR(TIMER1_COMPA_vect) {
  musique.OCR1_Sine();
  
}

int main() 
{
  initialiser();
  del del1(PINS12);


  do 
  {
    
  
    musique.jouerSequenceT(0,1,furelise, fureliseT, 27);
      _delay_ms(8000);    
      
    musique.jouerSequenceT(9,1,mario, marioT, 40);
   // ;
    del1.clignoter(10,100);
    _delay_ms(8000);
    musique.jouerSequenceT(0,1,musiq1, musiq1T, sizeof(musiq1));
   //musique.initSine();
   //musique.playSine(6,10);
     del1.clignoter(10,100);
    del1.clignoter(100,6);
      _delay_ms(8000);
    
       
   

      
  
  } while(1);
  



  return 0;
}