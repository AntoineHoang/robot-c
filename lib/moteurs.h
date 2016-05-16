#include "moteur.h"
class Moteurs {
private:

  moteur moteur1;
  moteur moteur2;
  

public:

  arreter();
  tourner(uint8_t direction);
  accelerer(uint8_t vitesse);
  avancer();
  reculer();
  
}