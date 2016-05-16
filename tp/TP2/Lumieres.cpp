/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */

#include <avr/io.h> 

#define F_CPU 8000000
#include <util/delay.h>
//_delay_ms (double ms);


int main() {
  
  //DDRA = 0xff; // PORT A est en mode sortie 11111111
  //int toggle = 0;
  DDRD = 0xfb; // PORT D2 est en mode entree 11111011
  
  for(;;){  // boucle sans fin
    
  /*  if (toggle==0){
      PORTA = 0xA4;//Nombre binaire 10100100
      toggle = 1;
      _delay_ms (3);
    }
    else{
      PORTA = 0x64;//Nombre binaire 01100100
      toggle = 0;
      _delay_ms (1);
    }
   */
  
/*    if ( PIND & 0x04 && toggle==0)
    {
      PORTD = 0x01; //00000001
      toggle = 1;
      _delay_ms (1);
    }
    else if (toggle ==1)
    {
      PORTD = 0x02;    //00000010
      toggle = 0;
      _delay_ms (1);
    } 
    else
      PORTD = 0x00; //00000000
*/

    if ( PIND & 0x04){
      
      _delay_ms (10);
      
	if ( PIND & 0x04){
	    PORTD = 0x01;   //00000001
	    _delay_ms (4);
	    PORTD = 0x02;    //00000010
	    _delay_ms (2);
	 }
    }
    else {
      PORTD = 0x00; //00000000
    }

   
  }
}
