/***************************************************************************************************
//					Parcours.cpp
//
// Auteur :			Marc-Andr� Gagnon
// Description:		Impl�mentation de la classe parcours
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

// enum utilis� comme retour du detecteurligne pour simplifier le code et le rendre lisible
enum {AucuneLigne=0, LigneGauche=1, LigneCentre=2, LigneGaucheCentre=3, LigneDroite=4, LigneDroiteGauche=5, LigneDroiteCentre=6, LignePartout=7} statutTracker;


/***************************************************************************************************
// M�thode :			EffectuerEpreuve()
// Description :		Appel les m�thodes priv�es qui effectuent les �preuves. Modifie l'attribut
//						epreuve_ en cons�quence
//
// Param�tres :			Aucuns
// Valeur de retour :	Aucune
****************************************************************************************************/
void Parcours::effectuerEpreuve(){

	if (epreuve_==1)		// Structure de if - elseif pour le choix de l'�preuve
		epreuve12();
	else if (epreuve_ ==2)
		epreuve23();
	else if (epreuve_ ==3)
		epreuve34();
	else if (epreuve_ ==4)
		epreuve45();
	else if (epreuve_ ==5)
		epreuve51();

	epreuve_++;				// Incr�ment de l'attribut
	if (epreuve_ == 6){
		epreuve_ = 1;
	}
}

/***************************************************************************************************
// M�thode :			epreuve12()
// Description :		Effectue l'�preuve entre le point 1 et 2
//						Simple d�placement entre les lignes
//
// Param�tres :			Aucuns
// Valeur de retour :	Aucune
****************************************************************************************************/
void Parcours::epreuve12(){
	
	// Met les directions vers l'avant
	PORTD |= (1<<7)|(1<<6);

	// Classe du d�tecteur de lignes
	DetecteurLigne lecteur(&PINA, &DDRA, 1, 3, 5);

	// Variables de lecture de la classe du d�tecteur
	uint8_t lecture;
	uint8_t ancienneLecture;

	// Variables utilis�s pour la fin de l'�preuve
	bool fini = false;
	uint8_t compteur = 0;

	// Boucle principale
	while (compteur!=40){
		
		lecture = lecteur.getStatutCourant();
		ancienneLecture = lecteur.getStatutAncien();
		
		// Structure if - elseif pour le r�ajustement du robot vers le centre des lignes
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

		// Compte 40 it�rations apr�s la fin, soit 0,2 seconde, pour d�passer un peu la fin de l'�preuve.
		if (ancienneLecture == LignePartout){
			fini = true;
		}
		if (compteur != 40 && fini == true){
			compteur ++;
		}

		// Chaque r�ajustement prend 1/200 de seconde
		_delay_ms (5);

	}
	ajusterPWM(0,0);
	_delay_ms (150);
}

/***************************************************************************************************
// M�thode :			epreuve23()
// Description :		Effectue l'�preuve entre le point 2 et 3
//						Simple d�placement entre les lignes, comme l'�preuve 1.
//						Le seul ajout est le r�ajustement � la fin
//
// Param�tres :			Aucuns
// Valeur de retour :	Aucune
****************************************************************************************************/
void Parcours::epreuve23(){
	
	// Met les directions vers l'avant
	DDRD |= (1<<7)|(1<<6);

	// Classe du d�tecteur de lignes
	DetecteurLigne lecteur(&PORTA, &DDRA, 0, 2, 4);

	// Variables de lecture de la classe du d�tecteur
	uint8_t lecture;
	uint8_t ancienneLecture;

	// Variables utilis�s pour la fin de l'�preuve
	bool fini = false;
	uint8_t compteur = 0;

	// Boucle principale
	while (compteur!=40){
		
		lecture = lecteur.getStatutCourant();
		ancienneLecture = lecteur.getStatutAncien();
		
		// Structure if - elseif pour le r�ajustement du robot vers le centre des lignes
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

		// Compte 40 it�rations apr�s la fin, soit 0,2 seconde, pour d�passer un peu la fin de l'�preuve.
		if (ancienneLecture == LignePartout){
			fini = true;
		}
		if (compteur != 40 && fini == true){
			compteur ++;
		}
	}
		// Chaque r�ajustement prend 1/200 de seconde
		_delay_ms (5);
	
	// R�ajustement de 90� vers la droite
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
