uint16_t vitesseLUT[] = {0, 64, 128, 256};

/* Les moteurs sont toujours (ici) sur le port D, le PWM sort sur les pins
 * 18 et 19 du Atmega16 donc PD4 (OC1B) et PD5 (OC1A), sur le board ce sont 
 * respectivement les pins 5 et 6 du port D. La direction prend deux broches (pins) que
 * l'on assigne dans le constructeur (broches du port D),
 * une pour chaque moteur. Logique 1 indique avancer, logique 0 reculer.
 * 
 */

#define avancer 1
#define reculer 0
#define allumer 1
#define eteindre 0

Moteur::Moteur(uint16_t diviseurCompteur, unsigned char OCRv, uint8_t pinDirection) {
 
  if(OCRv=='A') {
    COMPARATEUR = COM1A1;
    
    OCR = OCR1A;
    OCPIN = 5;
    
    
  } else {
    COMPARATEUR = COM1B1;
    OCR = OCR1B;
    OCPIN = 4;
  }
  
  setDiviseur(diviseurCompteur);
  setComparateur(allumer);
  
  TCCR1A |= (1<<WGM10);	
  
  dir = pinDirection;
  
  *OCR=0;
  
  DDRD |= (1<<OCPIN); // OC1B et OC1A en mode sortie.
  
  DDRD |= (1<<dir); // pin directionnelle en sortie.	
  
  setMode(avancer); // direction initiale avancer.
  
  
  // WGM10 = set Waveform Generation Mode to PWM, Phase Correct, 8-bit, TOP = 0x00FF
  // Update de OCR1X = TOP, TOV1 flag set on BOTTOM.
  // COM1A1 et COM1B1 = 
  
  // Phase correct PWM Mode (P.104 ref doc2466.pdf ATMEGA16 datasheet)
  /*
   * High res. phase correct PWM waveform generation.
   * Dual-slope operation.
   * 
   * Le compteur compte de BOTTOM à TOP (0x0000 - 0x00FF ici)
   * Ensuite il compte de TOP à BOTTOM (0x00FF - 0x0000 ici)
   * 
   * De table 46, p 111.
   * COM1A1 et COM1B1 = Clear OC1A and OC1B on compare match (avec TCNT1) when
   * UPCOUNTING, set OC1A and OC1B on compare match (avec TCNT1) when downcounting.
   * 
   *      * --------TOP=0x00FF
   *     * *
   * ---*   *----- OCR1x seuil du compte
   *   *     *
   *  *       *<--------- comptage TCNT1x++ sur chaque CLKtimer (F_CPU/prescaler)
   * *         *____ BOTTOM=0x0000
   * 
   * ___     ___________ +5    
   *    |   |
   *    |___|            GND
   * 
   * 
   * CONCLUSION: plus on augmente OCR1x, moins il y a de temps morts (GND), donc
   * à zéro, il n'y a pas de courant, â 0x00FF, le courant est continu.
   * Entre les deux bornes, le temps à +5v augmente, le duty cycle augmente de façon
   * proportionnelle au seuil OCR1x, la puissance transmise augmente également.
   * 
   * ___     _______     _______     ____  PWMA OCR1A = A
   *    |   |  ON   |   |   ON  |   |
   *    |___|       |___|       |___|
   *    |<----T1--->|
   * ____   _________   _________   _____  PWMB OCR1A = B, B > A --> Duty Cycle B > Duty Cycle A
   *     | |   ON    | |    ON   | |
   *     |_|         |_|         |_|
   *     |<----T2--->|
   * 01234567890123456789012345678901234567890
   * 0         1         2         3         4
   * 
   * Les périodes T1 = T2. La période ne varie pas, donc la fréquence ne varie pas.
   * 
   * La résolution du PWM peut être ajustée avec la valeur de TOP (le maximum jusqu'ou
   * compte le compteur 0x00FF ou 0x01FF ou 0x03FF avec l'éq. ici:
   * 
   * Resolution = log(TOP+1) / log(2). ici LOG10(256)/LOG(2) = 8.
   * Lors du compte TCNT1 aura la valeur de TOP pour seulement un cycle du compteur (un tick du timer).
   * Et non deux (un pour le upcount et un pour le debut du downcount).
   * 
   * LES update sur OCRx ne se font que quand le compteur est rendu à TOP, donc quand on 
   * fait OCR1x = 0xXX ... 
   * 
   * L'onde PWM est générée sur les OC1x pins... En settant COM1x1:0 à 2 (0b10), le PWM est
   * non-inversé, à COM1x1:0 à 3 (0b11), il est inversé.
   * 
   * Attention, l'onde sera que visible si le port est mis en mode sortie (DDR).
   * 
   * La fréquence est:
   * 		Fréq PWM = 
   * 			   Fréq CPU / diviseur = nb tick par sec
   * 			   on compte 0x0000 â TOP et ensuite de TOP à 0x0000 en un cycle PWMA
   * 			   donc 2*TOP ticks.
   * 
   * 			   (2*TOP) ticks = 1 cycle 
   * 			   1 tick en sec = diviseur/F_CPU
   * 			   (2*TOP) ticks en sec =  (2*TOP)*diviseur/F_CPU
   * 			   Donc fréq. PWM = F_CPU/(2*TOP*diviseur).
   * 
   * 
   * 		Fréq = F_CPU / (2 * diviseur * TOP)
   * 		F = 8000000 / (2 * 8 * 255) = 1960.78 Hz
   * 			
   * 	Le diviseur prend 1,8,64,256 ou 1024 comme valeurs.
   * 
   * Nous voyons donc que la fréquence ne dépend pas de OCR1X mais bien de F_CPU, N et TOP. Ici
   * N et TOP étant modifiables si voulu.
   * 
   * 
   * 
   * 
   */
  
}


void Moteur::setMode(uint8_t mode){
  if(mode==avancer)  PORTD |= (1<<dir); 
  else PORTD &= (unsigned char) ~(1<<dir);
}


void Moteur::setComparateur(uint8_t mode) {
 
 if(mode==allumer) TCCR1A |= (1<<COMPARATEUR);
 else TCCR1A &= (unsigned char) ~(1<<COMPARATEUR);
}

void Moteur::setDiviseur(uint16_t diviseurCompteur) {
   TCCR1B |= (unsigned char)~(0b111);
  switch (diviseurCompteur) {
    case 0:
      TCCR1B &= (unsigned char)~(0b111);
      break;
    case 1:
    TCCR1B |= (1);  ; // 1, 8, 64, 256, 1024
  //TCCR1B = (1<<CS11);	 			// CS 12-10 = 010 pour clk/8
      break;
    case 8:
       TCCR1B |= (2);
      break;
    case 64:
       TCCR1B |= (3);
      break;
    case 256:
       TCCR1B |= (4);
      break;
    case 1024:
       TCCR1B |= (5);
      break;
    default:
       TCCR1B |= (2);
       break;
       
  }; 
  
}

void Moteur::arreter() {
  *OCR = 0;
  setComparateur(eteindre);
  allume=0;
}

void Moteur::demarrer() {
  *OCR = 0;
  setComparateur(allumer);
  allume=1;
}

Moteur::accelerer(signed char vitesse, uint8_t temps) 
{
  if(!allume)demarrer();
if(vitesseActuelle>vitesse) dv=1;
if(vitesseActuelle<vitesse) dv=-1;


dt =temps;
compteTotal = vitesseActuelle - vitesse;
if(compteTotal<0)compteTotal*=-1;
compte =dt;

accellerateur(allumer);//compare match enable...

}

Moteur::COMPARE_MATCH() 
{
compte--;
if(compte==0) {
 setVitesse(vitesseActuelle+dv);
compte=dt;
compteTotal--;
if(compteTotal==0) {accellerateur(eteindre);}
};

}


void Moteur::setVitesse(unsigned char vitesse) {
 
  if(vitesse<0)
  {
    vitesse*=-1;
    setMode(reculer);
  } else {setMode(avancer)};
  
  if(vitesse<5)
   

   *OCR = vitesseLUT[vitesse]; 
  vitesseActuelle = vitesse;
  
  }
  
  
  












