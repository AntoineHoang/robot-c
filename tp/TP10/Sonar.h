##-------------------------------------------##
#
# 	Sonar Devantech SRF05 Ultra-Sonic Ranger
# 				  Sonar.h
#	            Antoine Hoang
#
##-------------------------------------------##

#ifndef SONAR_H
#define SONAR_H

#include <avr/io.h>

class Sonar 
{
	public:
		Sonar() { };
		~Sonar() { };
		void lancerECHO();
		uint8_t process(uint16_t compteTIMER)
	private:
		void initialisation();
		void startTIMER(uint16_t TEMPS);
		void interruptTIMER();
		void interruptSONAR();
};

#endif //SONAR_H