#include <avr/io.h> 

#define F_CPU 8000000
#include <util/delay.h>

int main() {
	
	DDRD = 0xfb;
	double temps=1;
//	for(;;){
		while(temps>0){
			PORTD = 0x01;
			_delay_ms (temps);
			PORTD = 0x00;
			_delay_ms (1-temps);
			temps=temps-0.0005;
		}
		temps=1;
		while(temps>0){
			PORTD = 0x02;
			_delay_ms (temps);
			PORTD = 0x00;
			_delay_ms (1-temps);
			temps=temps-0.0005;
		}
		temps=1;
	//}
}

