#include "moteurs.h"

avancer() {
 if(!moteur1.allume)moteur1.demarrer();
 if(!moteur2.allume)moteur2.demarrer();
  
}