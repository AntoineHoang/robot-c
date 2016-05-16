#include <avr/io.h>
#include <util/delay.h>
#include <avr/signal.h>
#include <avr/interrupt.h>
#include "del.h"
#include "midi.h"
#include "FonctionGlobales.h"
#include "detecteurligne.h"
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
  
enum  {AucuneLigne=0, LigneGauche=1, LigneCentre=2, LigneGaucheCentre=3, LigneDroite, LigneDroiteGauche, LigneDroiteCentre, LignePartout} maligne;




void initialiser(void) {

  DDRB = 0xff; 			// PORT B est en mode sortie. (Pour la DEL).
  //DDRD = 0x00; 			// PORT D est en mode entrée. (Pas utilise ici).
  DDRD |= setOCR1A;
  sei();
  
  
  
  TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10);	// COM1A1 pour comparaison sur OC1A

						// WGM 13-10 = 0001 pour PWM 1 ( 12 et 13 sur B et 10 et 11 sur A)

  TCCR1B = (1<<CS11);	 			// CS 12-10 = 010 pour clk/8

  TCNT1 = 1;


  DDRD = 0xff;					//PORT D est en sortie
  
  DDRB =  0xff;					//PORT B est en sortie
  

}


ISR(TIMER0_COMP_vect) {

}


ISR(TIMER1_COMPA_vect) {

  
}

int main() 
{
  initialiser();
  del del1(PINS12);
  DetecteurLigne detecteurligne(&PINA, &DDRA, 1,3,5);

  do 
  {
    
  
//del1.clignoter(10,100);
//      _delay_ms(1000);

      
      switch(detecteurligne.getStatutCourant()) {
	
	case(AucuneLigne):
	   ajusterPWM(0,0);
	  del1.allumer(0);
	  
	  break;
	  
	  case(LigneGauche):
	  del1.allumer(1);
	  break;
	  
	  case(LigneCentre):
	  PORTD |= 0x0C;     //0000 1100
          ajusterPWM(150, 150);
	  del1.clignoter(50,2);
	  	   
	  
	  break;
	  
	  case(LigneGaucheCentre):
	
	  break;
	  
	  case(LigneDroite):
	      del1.allumer(2);
	        PORTD = 0x00;     //0000 1100
          ajusterPWM(150, 150);
	  del1.clignoter(50,2);
	  break;
	  
	  case(LigneDroiteGauche):
	  
	  break;
	  
	  case(LigneDroiteCentre):
	  
	  break;
	  
	  case(LignePartout):
	
	    
	    break;
	  default:
	    ajusterPWM(0,0);
	
      };
       
         _delay_ms(500);

      
  
  } while(1);
  



  return 0;
}