#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <memoire_24.h>
#include <memoire_24.cpp>
#include <string.h>


int main (){
	
	Memoire24CXXX mem;
	DDRB = 0xFF;
	char a[50]="*E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E*";
	char b[50]={'\0'};
	uint8_t temp;
	uint8_t i=0;
	bool egalite=true;
	mem.ecriture(0x00,(unsigned char*)&a[0],strlen(a));
	_delay_ms(5);
	mem.ecriture(strlen(a),0x00);
	_delay_ms(5);
	mem.lecture(0,&temp);
	
	while(temp!=0){
		b[i]=temp;
		i++;
		mem.lecture(i,&temp);
	}
	//b[5]='a'; //Test pour non-egalite
	
	for (uint8_t j = 0; j<strlen(a); j++){
		if (a[j]!=b[j])
			egalite=false;
	}
	
	if(egalite)
		PORTB=0x01;
	else
		PORTB=0x02;
		
	return 0;
}
		
		
		
		
		
	
	
                    
      

	
	
	
	
