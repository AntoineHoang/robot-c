/************************************************************
//				Parcours.hpp
//
// Auteur :		Marc-Andr� Gagnon
// Description:	D�claration de la classe parcours
//
*************************************************************/
#ifndef PARCOURS_H_
#define PARCOURS_H_
#include <avr/io.h> 

class Parcours{

public:

	// Constructeur par parametre
	Parcours (uint8_t numeroDepart) : epreuve_(numeroDepart) { } 
	
	// Methode principale
	void effectuerEpreuve ();

private:

	// M�thodes effectuant les �preuves
	void epreuve12 ();
	void epreuve23 ();
	void epreuve34 ();
	void epreuve45 ();
	void epreuve51 ();

	// Attribut correspondant � l'�preuve suivante
	uint8_t epreuve_;
};
#endif
