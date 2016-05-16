#include <avr/io.h>
#include "memoire_24.h"
#include "del.h"
#include "midi.h"
#include "FonctionGlobales.h"
#include <avr/interrupt.h>
#include <util/delay.h>



void initialiser(void)
{

  TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10);	// COM1A1 pour comparaison sur OC1A

						// WGM 13-10 = 0001 pour PWM 1 ( 12 et 13 sur B et 10 et 11 sur A)

  TCCR1B = (1<<CS11);	 			// CS 12-10 = 010 pour clk/8

  TCNT1 = 1;


  DDRD = 0xff;					//PORT D est en sortie
  
  DDRB =  0xff;					//PORT B est en sortie
}


int main()
{
  initialiser();
  
  del led(0);
  midi piezzo(&PORTB, &DDRB, 2, 0);
  Memoire24CXXX mem;  // objet mémoire
 
  uint8_t lu = 0, pointLecture = 0; // variables de lecture
  uint8_t compteur = 0, temp = 0; // variable boucle
  bool verifBoucle = false;
  led.clignoter(10,10);
    while(lu != 0x01)   //dbt
    {
        mem.lecture(pointLecture,&lu);
        pointLecture ++ ;
    }
    
    pointLecture++;
    mem.lecture(pointLecture, &lu);
    pointLecture++;

    while(lu != 0xFF)  //fin
    {
        switch(lu)
        {
            case 0x02 : //att
            mem.lecture(pointLecture, &lu);
            delais(25*(uint16_t)lu);
            pointLecture++;
            break ;

            case 0x44 :  //dal
            mem.lecture(pointLecture, &lu);
            led.allumer(1);
            pointLecture++;
            break;

            case 0x45 :  //det
            mem.lecture(pointLecture, &lu);
            led.eteindre();
            pointLecture++;
            break;

            case 0x48 :  //sgo
            mem.lecture(pointLecture, &lu);
            piezzo.jouerNote(lu-40);
            pointLecture ++;
            break;

            case 0x09 : //sar
            piezzo.arreterNote();
            pointLecture++;
            break;

            case 0x62 :  // mav
            mem.lecture(pointLecture, &lu);
	    PORTD |= 0x0C;     //0000 1100
            ajusterPWM(lu<<1, lu<<1);
            pointLecture++;
            break;

            case 0x60 :  //mar1

            case 0x61 :  //mar2

            ajusterPWM(0, 0);
	    delais(400);
            pointLecture++;
            break;

            case 0x63 : //mre
            mem.lecture(pointLecture, &lu);
	    PORTD &= (unsigned char) ~(3<<(2));

	    ajusterPWM(lu<<1, lu<<1);
            pointLecture++;
	    break;

            case 0x64 :  //trd
            ajusterPWM(200, 0);
	    _delay_ms(985);
	    ajusterPWM(0, 0);
	    delais(400);
            pointLecture++;
            break;

            case 0x65 :  //trg
            ajusterPWM(0, 200);
	    _delay_ms(831);
	    ajusterPWM(0, 0);
	    delais(400);
            pointLecture++;
            break;

            case 0xC0 :  //dbc
            mem.lecture(pointLecture, &lu);
            pointLecture++;
            compteur = lu + 1;
            temp = pointLecture;
            verifBoucle = true;

            case 0xC1 :  //fbc
            if(verifBoucle && compteur)
            {
                compteur-- ;
                pointLecture = temp;
            }
            else
	    {
	      pointLecture++;
	      verifBoucle = false;
	    }
            break;
        }

        mem.lecture(pointLecture, &lu);
        pointLecture ++;
    }

    return 0;
}
