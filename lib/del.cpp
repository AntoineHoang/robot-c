/*  Librairie pour le contrôle des diodes électroluminescentes.
 * 
 * 
 * 
 */
#include "del.h"


#ifndef DELPORT
#define DELPORT PORTB
#endif

#ifndef DELDDR
#define DELDDR DDRB

#endif
//enum {ROUGE, VERT, ETEINT} couleurLED;
#include <avr/io.h>
#include <util/delay.h>


int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {}; 

void __cxa_pure_virtual(void) {}; 

//Ci-bas est la version qui permet de changer les pins facilement.
void allumerDel(uint8_t couleur, int delpins) 
{
  DELDDR |= (1<<delpins)+(1<<(1+delpins)); 
  DELPORT = (DELPORT | ((0b11)<<(delpins<<1))) & (((0b11111100 + couleur)<<(delpins<<1)) + ((1<<(delpins<<1))-1));  
	
}

void del::allumer(uint8_t couleur) 
{
	//DELPORT |= ((0b11)<<(delpins<<1)); 
	//La fonction ci-bas place la valeur de couleur (2bit) à l'endroit désigné par delpins.
	//Elle est une concaténation uniligne d'une manipulation originellement pluriligne.
	  *port = (*port | ((0b11)<<(delpins<<1))) & (((0b11111100 + couleur)<<(delpins<<1)) + ((1<<(delpins<<1))-1));  
	
  
}


void * del::operator new(size_t size)
{
  return malloc(size);
}

void del::operator delete(void * ptr)
{
  free(ptr);
} 

void * operator new[](size_t size)
{
    return malloc(size);
}

void operator delete[](void * ptr)
{
    free(ptr);
} 

void del::initialiser() 
{
  *portddr |=  (1<<delpins)+(1<<(1+delpins)); 
  
}

del::del(volatile uint8_t *portA, volatile uint8_t *portAddr, uint8_t pins) 
{
    delpins=pins;
    port =portA;
    portddr = portAddr;
    
};

del::del(uint8_t delN)
{
  delpins=delN;
  port = &DELPORT;  
  
};

void del::eteindre() {
	allumer(0); 
}

void delais(uint16_t ms) 
{
  for(uint16_t i = 0; i<ms; i++) _delay_ms(1);
  
}

void del::clignoter(uint8_t delai, uint8_t nbFois) 
{
  for(uint8_t i=0; i<nbFois; i++) 
  {
	allumer(1);
	delais(delai);
	allumer(2);
	delais(delai);
  }
  eteindre();
}

