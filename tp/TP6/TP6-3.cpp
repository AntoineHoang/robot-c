
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

// De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {

	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = donnee;

}

int main(){
	
	// Equivalent au TP6-1, pour ecrire un message en memoire
	Memoire24CXXX mem;
	DDRB = 0xFF;
	
	char a[100]="Voici un message secret de la part de Antoine : QQ\n";
	char temp;

	mem.ecriture(0x00,(unsigned char*)&a[0],strlen(a));
	_delay_ms(5);
	mem.ecriture(strlen(a),0xFF); // Pour la fin de la lecture
	_delay_ms(5);
	
	// Eqiovalent au TP6-2, pour envoyer un message vers le PC
	
	initialisationUART();
	
	uint8_t i=0;
	
	mem.lecture(i,(unsigned char*)&temp);

	while (temp != 0xFF) {
		
		transmissionUART ( temp );
		i++;
		mem.lecture(i,(unsigned char*)&temp);
	}
	PORTB=0x01; //Verifiaction de la sortie du while apres la lecture du 0xFF
}
