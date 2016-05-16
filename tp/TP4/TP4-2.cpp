#include <avr/io.h> 

#define F_CPU 8000000
#include <util/delay.h>

void attendre(int temps){
	for (temps;temps>0;--temps){
		_delay_ms (1);
	}
}

int main() {
	
	DDRB = 0xff;
	int temps=1000/60;
	int per;
	uint32_t compteur=0;
	
	for(per=2;per<=10;per+=2){
		
		for(compteur=0;compteur<120;compteur++){
			PORTB = 0x02; 					//0000 0010
			attendre(temps*per/10);
			PORTB = 0x00; 					//0000 0000
			attendre(temps*(1-per)/10);
		}
	}
	_delay_ms (1000);
	
	temps=1000/400;
	
	for(per=2;per<=10;per+=2){
		
		for(compteur=0;compteur<800;compteur++){
			PORTB = 0x02; 					//0000 0010
			attendre(temps*per/10);
			PORTB = 0x00; 					//0000 0000
			attendre(temps*(1-per)/10);
		}
	}
	
}
