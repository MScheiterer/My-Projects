//
// Created by Micha on 02/01/2023.
//

#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"
#include "SimulationsObjekt.h"
//Konstruktor mit Referenzen auf einen Weg und ein Fahrzeug
Streckenende::Streckenende(Weg& weg, Fahrzeug& fahrzeug) : Fahrausnahme(weg, fahrzeug) {}

//Ausgabe von Weg und Fahrzeug sowie Nachricht "Streckenende erreicht."
void Streckenende::vBearbeiten() {
	extern double dGlobaleZeit;

    auto pZiel = p_pWeg.pGetZiel();
    if (pZiel != nullptr){
		pZiel->vTanken(p_pFahrzeug);

		unique_ptr<Fahrzeug> tempFahrzeug = p_pWeg.pAbgabe(p_pFahrzeug);

		shared_ptr<Weg> tempWeg = pZiel->pZufaelligerWeg(p_pWeg);

		std::cout << "ZEIT      : " << dGlobaleZeit << std::endl;
		std::cout << "KREUZUNG  : " << pZiel->getName() << std::endl;
		std::cout << "WECHSEL   : " << p_pWeg.getName() << " --> " << tempWeg->getName() << std::endl;
		std::cout << "FAHRZEUG  : " << *tempFahrzeug << std::endl;
		tempWeg->vAnnahme(move(tempFahrzeug));
    }
}


