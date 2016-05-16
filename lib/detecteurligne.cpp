
#include "detecteurligne.h"


uint8_t getBit(volatile uint8_t val, uint8_t n){ return (val&(1<<n))>>(n);}

// Méthode : DetecteurLigne(volatile uint8_t *portA, volatile uint8_t pinJaune, volatile uint8_t pinBleue, volatile uint8_t pinMauve)
// Intention: Constructeur.
// 
// Paramètres:
//
//	*portA		uint8_t*	Pointeur vers le port utilisé pour le capteur.
//	*ddrA		uint8_t*	Pointeur vers le registre de direction du port utilisé pour le capteur.
//	pinJaune	uint8_t		Numéro de la pin du port branchée au fil jaune (Left Sensor)
//	pinBleue	uint8_t		Numéro de la pin du port branchée au fil bleu (Center Sensor)
//	pinMauve	uint8_t		Numéro de la pin du port branchée au fil mauve (Right Sensor)
//
//

enum {AucuneLigne, LigneGauche, LigneCentre, LigneGaucheCentre, LigneDroite, LigneDroiteGauche, LigneDroiteCentre, LignePartout} statutDetecteurLigne;

DetecteurLigne::DetecteurLigne(volatile uint8_t *portA, volatile uint8_t *ddrA, volatile uint8_t pinJaune, volatile uint8_t pinBleue, volatile uint8_t pinMauve) 
{
  port = portA;
  ddr = ddrA;
  leftSensor = pinJaune;
  centerSensor = pinBleue;
  rightSensor = pinMauve;
  
  // trouve la pin la moin significative. (bit le plus bas)
  if(pinJaune<pinMauve){pin1=pinJaune;}
  else pin1=pinMauve;
  
 
  mask = (1<<leftSensor)+(1<<centerSensor)+(1<<rightSensor);
   initialiserPort();
}

DetecteurLigne::~DetecteurLigne () { }

void DetecteurLigne::initialiserPort() 
{
  *ddr &= (unsigned char) ~(mask); 
}

uint8_t DetecteurLigne::getStatutAncien() 
{
  return statutAncien;
}

uint8_t DetecteurLigne::getPortVal() 
{
 // return (unsigned char)(~((*port)&mask))>>pin1;
 
 uint8_t dport = (unsigned char)(~((*port)&mask));

 return (((getBit(dport, rightSensor))<<2)+((getBit(dport, centerSensor))<<1)+((getBit(dport, leftSensor)))); 

}



uint8_t DetecteurLigne::getStatutCourant() 
{
  
  uint8_t val = getPortVal();
  
  if(statutCourant!=val) {statutAncien = statutCourant; statutCourant = val;};
  return statutCourant;
  
  // Par défaut, le devant du robot est la partie ou se situe le lynxmotion sensor. En regardant de l'arrière à l'avant (des roues vers le senseur), nous établissons notre convention Gauche/Droite).
  // etat 0b0000 = 0 = tous les senseurs indiquent blanc. (pas de ligne)
  // etat 0b0001 = 1 = Left Sensor = noir. (ligne à gauche)
  // etat 0b0010 = 2 = Center Sensor = noir. (ligne au centre)
  // etat 0b0011 = 3 = Left+Center = noir 
  // etat 0b0100 = 4 = Right Sensor = noir. (ligne à droite)
  // etat 0b0101 = 5 = Right + Left = noir. 
  // etat 0b0110 = 6 = Right + Center = noir.
  // etat 0b0111 = 7 = tout noir.
  
  
}

