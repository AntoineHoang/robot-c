##-------------------------------------------##
#
# 	Sonar Devantech SRF05 Ultra-Sonic Ranger
# 				  Sonar.cpp
#	            Antoine Hoang
#
##-------------------------------------------##

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include "Sonar.h"
#include <avr/interrupt.h>: Interrupts

volatile uint8_t TIMER;							//TIMER->0 si le temps n'est pas arrete, TIMER->1 lorsqu'on l'arrete
volatile uint8_t SonarECHO;						//SonarECHO->0 si l'echo n'est pas intercepte, SonarECHO->1 si on capte l'echo
volatile uint16_t compteTIMER;

void Sonar::interruptTIMER()					//ISR (TIMER2_COMP_vect)							
{												//arrete le timer
	TIMER = 1;
	compteTIMER++;
	//cli();
}

void Sonar::interruptSONAR()					//ISR (INT0_vect)  							
{	
	TCCR2 = 0;									//arreter timer2
	uint8_t SonarECHO = 1;						//anti-rebond pour s'assurer d'avoir bien lu la valeur					
	_delay_ms (10);								
	if (PIND & 0x02)							//si la sortie du Sonar recoit effectivement l'echo, EchoSonar->1
		SonarECHO = 1;
	else
		SonarECHO = 0;
}

void Sonar::initialisation ()
{
	cli();										//routine qui bloque les interruptions pour ne pas etre interrompu lorsqu'il n'est pas pret
	DDRD |= 2;									//effectue un OR logique pour obtenir un 1 au bit 1
	DDRD &=(unsigned char)~1;					//effectue un ET logique pour obtenir un 0 au bit 0 
	GICR |= _BV(INT0);							//initialiser GICR pour maintenant permettre les interruptions externes
	MCUCR |=_BV(ISC01);							//ajuster MCUCR pour qu'il puisse detecter les interruptions externes sur le falling edge
	sei();										//permet de recevoir des interruptions (complementaire a cli())
}

void Sonar::startTIMER (uint8_t TEMPS)
{
	TIMER = 0;									//initialise timer
	TCNT2 = 0;									//initialise Timer/counter2
	OCR2 = TEMPS;								//set OCR2 pour pouvoir comparer avec TEMPS
	TCCR2 = (1<<CS22)|(1<<CS21)|(1<<WGM21); 	//CS22,CS21,CS20 designe un clk/1024 pour le timer2
												//WGM21 pour mode CTC
	TIMSK = _BV(OCIE2);							//Compare Match du timer2					
}

void Sonar::lancerECHO ()
{
	PORTD = 0x01;								//trigger a 1 pour envoyer ECHO
	_delay_us(10);								//10usecondes 
	PORTD = 0x00;
}

uint8_t Sonar::process (uint16_t compteTIMER)
{
	uint8_t instructionSonar;					
	compteTIMER=compteTIMER<<8;					//decalage de 8bit du compteur
	compteTIMER+=TCNT2;							//addition du TCNT2 pour obtenir le temps
	uint16_t distance=compteTIMER*(32/58);		//division par 580000 pour obtenir des cm
	if(sonarECHO==1){
		if (distance<5)							//range qui determine les valeurs de retour
			return instructionSonar=1;
		else
			if (distance>5 && distance<10)
				return instructionSonar=2;
			else
				if (distance>10)
					return instructionSonar=3;
	}
}

8,000,000/1024

1-INITIALISATION DES REGISTRES ET PORTS	
2-INITIALISE TIMER2
3-ENVOI L'ECHO DU SONAR
4-DEMARRER TIMER2
	4a-RECOIT L'ECHO DU SONAR
		5a-ARRET DU TIMER2 PAR INTERRUPT
	4b-NE RECOIT PAS ECHO
		5b-ARRET DU TIMER2 APRES 30ms

