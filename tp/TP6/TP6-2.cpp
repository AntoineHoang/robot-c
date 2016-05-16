
#define F_CPU 8000000
#include <avr/io.h>
//#include <util/delay.h>
//#include <memoire_24.h>
//#include <memoire_24.cpp>


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

// De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {

	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = donnee;

}

int main(){
	
	initialisationUART();
	
	char mots[21] = "Le robot en INF1995\n";

	uint8_t i, j;

	for ( i = 0; i < 100; i++ ) {
		
		for ( j=0; j < 20; j++ ) {

			
			transmissionUART ( mots[j] );

		}
	}
}
