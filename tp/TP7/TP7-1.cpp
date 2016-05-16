
#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>


int main () {
  
  DDRD = 0xfb; // 1111 1011 port d2 en entre
  uint8_t compteur = 0;
  bool compteurActive = false;
  uint8_t temps = 0;
  
  while(1){
   
   if (!(PIND & 0x04)){
     compteurActive = true;
   }
   
   while ((compteurActive == true) && (compteur < 120)){
     compteur++;
     _delay_ms (100);
     if (PIND & 0x04)
       compteurActive = false;
   }
   
   if (compteur != 0){
     while (temps != 10){
       PORTD = 0x01;
       _delay_ms (25);
       PORTD = 0x00;
       _delay_ms (25);
       temps++;
     }
     PORTD = 0x00;
     _delay_ms (2000);
     temps = 0;
     
     while (temps != compteur/2){
       PORTD = 0x02;
       _delay_ms (250);
       PORTD = 0x00;
       _delay_ms (250);
       temps++;
     } 
     temps = 0;
     PORTD = 0x01;
     _delay_ms (1000);
     PORTD = 0x00;
     compteur = 0;
     compteurActive = false;
  }
 }
}
