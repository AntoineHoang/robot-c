#ifndef DETECTEURLIGNE_H_
#define DETECTEURLIGNE_H_
#include <avr/io.h> 



class DetecteurLigne {
 
private:
  volatile uint8_t * port;  
  volatile uint8_t * ddr;
  
  uint8_t leftSensor;
  uint8_t centerSensor;
  uint8_t rightSensor;
  void initialiserPort();
  
  uint8_t statutAncien;
  uint8_t statutCourant;
  
  uint8_t getPortVal();

  uint8_t mask;
  
  uint8_t pin1;
  
public:

 DetecteurLigne(volatile uint8_t *portA, volatile uint8_t *ddrA, volatile uint8_t pinJaune, volatile uint8_t pinBleue, volatile uint8_t pinMauve);
 ~DetecteurLigne();
 
 uint8_t getStatutAncien();
 uint8_t getStatutCourant();
  
};

#endif
