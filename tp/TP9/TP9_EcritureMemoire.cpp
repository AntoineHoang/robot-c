
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <memoire_24.h>
#include <memoire_24.cpp>
#include <string.h>


void initialisationUART ( void ) {

	// 2400 bauds. Nous vous donnons la valeur des deux
	
	// premier registres pour vous éviter des complications
	
	UBRRH = 0;
	
	UBRRL = 0xCF;
	
	// permettre la reception et la transmission par le UART
	
	UCSRA = 0 ;
	
	UCSRB = (1<<RXEN)|(1<<TXEN); // Read et Transmit enabled
	
	// Format des trames: 8 bits, 1 stop bits, none parity
	
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);

}

// Du PC vers l'USART

unsigned char receptionUART( void ) {
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}

int main(){
	
	// Ecrire un message en memoire
	Memoire24CXXX mem;
	initialisationUART();
	
	unsigned char donnee;
	uint8_t adresse = 0;
	
	while (1){
		
		donnee = receptionUART();
		mem.ecriture(adresse, donnee);
		_delay_ms (5);
		adresse ++;
		
	}
	
}
