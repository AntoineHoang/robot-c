/* 
 * Detecteur de champ magnetique Allegro A1321
 * Magnet.cpp
 * Auteur: Phannarat Willy Horng 
 */

#include <avr/io.h>
#include <util/delay.h>
#include "FonctionGlobales.h"

uint8_t pos;
uint16_t volt;
uint8_t champ;

void magnet::initialiser()
{
  DDRA = 0x00;			//Port A est en entree
  can capteur;
  
  champ = 0;			//Aucun champ magnetique
}

int main()
{
  initialiser();
  
  for(;;)
  {
    volt = capteur.lecture(pos)>>2;
  
    if(volt > 2.5)		//Pole nord
    {
      champ = 1;
    }
    else if(volt < 2.5)		//Pole sud
    {
      champ = 2;
    }
    else			//Aucun champ magnetique
    {
      champ = 0;
    }
  }
  return champ;
}