
#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include "can.h"
#include "can.cpp"

int main (){
  
  DDRA = 0x00; // Le port A1 en entree 1111 1110
  DDRB = 0xFF;
  uint8_t valeur=5;
  uint16_t valeur2;
  valeur2= valeur2 >> 2;
  // Le port A1 est utilise en entree et les ports A3 et A4 pour la DEL
  //uint16_t valeur;
 
  can conv;
   valeur2= conv.lecture(valeur);
  valeur2= valeur2 >> 2;
  
 while(1){
   valeur2=conv.lecture(valeur); 
    valeur2= valeur2 >> 2;
   
      if (valeur2 < 80){
	PORTB = 0x01;
	_delay_ms (20);
      } else if (valeur2 > 170){
	PORTB = 0x02;
	_delay_ms (20);
      } else {
	PORTB = 0x01;
	_delay_ms (10);
	PORTB = 0x02;
	_delay_ms (10);
      }
    
    
    
    
    
    
    
    
    
    
    /*
    //valeur = convertisseur.lecture(0);

      if (convertisseur.lecture(0) < 85){
	PORTB = 0x01;
	_delay_ms (20);
      } else if (convertisseur.lecture(0) > 170){
	PORTB = 0x02;
	_delay_ms (20);
      } else {
	PORTB = 0x01;
	_delay_ms (10);
	PORTB = 0x02;
	_delay_ms (10);
      }
    */
  }
  
}