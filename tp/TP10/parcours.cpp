/***************************************************************************************************
//					Parcours.cpp
//
// Auteur :			Marc-André Gagnon
// Description:		Implémentation de la classe parcours
//
****************************************************************************************************/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#define PINS12 0
#define PINS34 1
#define PINS56 2
#define PINS78 3


#include "FonctionGlobales.h"
#include "parcours.hpp"
#include "del.h"
#include "detecteurligne.h"

// enum utilisé comme retour du detecteurligne pour simplifier le code et le rendre lisible
enum {AucuneLigne=0, LigneGauche=1, LigneCentre=2, LigneGaucheCentre=3, LigneDroite=4, LigneDroiteGauche=5, LigneDroiteCentre=6, LignePartout=7} statutTracker;


/***************************************************************************************************
// Méthode :			EffectuerEpreuve()
// Description :		Appel les méthodes privées qui effectuent les épreuves. Modifie l'attribut
//						epreuve_ en conséquence
//
// Paramètres :			Aucuns
// Valeur de retour :	Aucune
****************************************************************************************************/
void Parcours::effectuerEpreuve(){

	if (epreuve_==1)		// Structure de if - elseif pour le choix de l'épreuve
		epreuve12();
	else if (epreuve_ ==2)
		epreuve23();
	else if (epreuve_ ==3)
		epreuve34();
	else if (epreuve_ ==4)
		epreuve45();
	else if (epreuve_ ==5)
		epreuve51();

	epreuve_++;				// Incrément de l'attribut
	if (epreuve_ == 6){
		epreuve_ = 1;
	}
}

/***************************************************************************************************
// Méthode :			epreuve12()
// Description :		Effectue l'épreuve entre le point 1 et 2
//						Simple déplacement entre les lignes
//
// Paramètres :			Aucuns
// Valeur de retour :	Aucune
****************************************************************************************************/
void Parcours::epreuve12(){
	
	// Met les directions vers l'avant
	PORTD |= (1<<7)|(1<<6);

	// Classe du détecteur de lignes
	DetecteurLigne lecteur(&PINA, &DDRA, 1, 3, 5);

	// Variables de lecture de la classe du détecteur
	uint8_t lecture;
	uint8_t ancienneLecture;

	// Variables utilisés pour la fin de l'épreuve
	bool fini = false;
	uint8_t compteur = 0;

	// Boucle principale
	while (compteur!=40){
		
		lecture = lecteur.getStatutCourant();
		ancienneLecture = lecteur.getStatutAncien();
		
		// Structure if - elseif pour le réajustement du robot vers le centre des lignes
		if (lecture == LigneCentre){ 
			ajusterPWM (110,150);
		}
		else if (lecture == LigneGauche){
			ajusterPWM (110,70);
		}
		else if (lecture == LigneDroite){
			ajusterPWM (50,150);
		}
		else {
			//ajusterPWM (90,140);
		}

		// Compte 40 itérations après la fin, soit 0,2 seconde, pour dépasser un peu la fin de l'épreuve.
		if (ancienneLecture == LignePartout){
			fini = true;
		}
		if (compteur != 40 && fini == true){
			compteur ++;
		}

		// Chaque réajustement prend 1/200 de seconde
		_delay_ms (5);

	}
	ajusterPWM(0,0);
	_delay_ms (150);
}

/***************************************************************************************************
// Méthode :			epreuve23()
// Description :		Effectue l'épreuve entre le point 2 et 3
//						Simple déplacement entre les lignes, comme l'épreuve 1.
//						Le seul ajout est le réajustement à la fin
//
// Paramètres :			Aucuns
// Valeur de retour :	Aucune
****************************************************************************************************/
void Parcours::epreuve23(){
	
	// Met les directions vers l'avant
	DDRD |= (1<<7)|(1<<6);

	// Classe du détecteur de lignes
	DetecteurLigne lecteur(&PORTA, &DDRA, 0, 2, 4);

	// Variables de lecture de la classe du détecteur
	uint8_t lecture;
	uint8_t ancienneLecture;

	// Variables utilisés pour la fin de l'épreuve
	bool fini = false;
	uint8_t compteur = 0;

	// Boucle principale
	while (compteur!=40){
		
		lecture = lecteur.getStatutCourant();
		ancienneLecture = lecteur.getStatutAncien();
		
		// Structure if - elseif pour le réajustement du robot vers le centre des lignes
		if (lecture == LigneCentre){ 
			ajusterPWM (110,150);
		}
		else if (lecture == LigneGauche){
			ajusterPWM (110,70);
		}
		else if (lecture == LigneDroite){
			ajusterPWM (50,150);
		}
		else {
			//ajusterPWM (90,140);
		}

		// Compte 40 itérations après la fin, soit 0,2 seconde, pour dépasser un peu la fin de l'épreuve.
		if (ancienneLecture == LignePartout){
			fini = true;
		}
		if (compteur != 40 && fini == true){
			compteur ++;
		}
	}
		// Chaque réajustement prend 1/200 de seconde
		_delay_ms (5);
	
	// Réajustement de 90° vers la droite
	PORTD |= (0<<6);
	while (lecture != LigneCentre && ancienneLecture != AucuneLigne){
		
		lecture = lecteur.getStatutCourant();
		ancienneLecture = lecteur.getStatutAncien();
		ajusterPWM (110,150);
	}

	ajusterPWM(0,0);
	_delay_ms (150);
	
}

void Parcours::epreuve34(){ }

void Parcours::epreuve45(){ }

void Parcours::epreuve51(){ }
