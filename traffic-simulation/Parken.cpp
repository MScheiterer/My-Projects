//
// Created by Micha on 30/12/2022.
//

#include "Parken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"
#include "Fahren.h"
#include <iostream>
using namespace std;

//Konstruktor mit Referenz auf einen Weg und Startzeit
Parken::Parken(Weg &weg, double dStartzeit) :
    Verhalten(weg),
    p_dStartzeit(dStartzeit) {}

//Prüft ob das Fahrzeug schon fahren darf, gibt ab Startzeit gefahrene Strecke weiter
double Parken::dStrecke(Fahrzeug &aFzg, double dZeitIntervall) {
    extern double dGlobaleZeit;
	if (dGlobaleZeit < p_dStartzeit) { //Falls Startzeit noch nicht erreicht wurde wird 0 weitergegeben
		return 0.0;
	} else {
		aFzg.increaseGesamtZeit(p_dStartzeit);
		std::cout << "GLOBALEZEIT: " << dGlobaleZeit << std::endl;
		throw Losfahren(*p_pWeg, aFzg);
	}
	/*std::cout << "SHOULDNT BE HERE" << std::endl;
	double dNeuerZeitIntervall = dZeitIntervall - p_dStartzeit; //Berechnet die seit dem Startzeitpunkt vergangene Zeit
	aFzg.increaseGesamtZeit(p_dStartzeit);
	Fahren fahren = Fahren(*p_pWeg);
	return fahren.dStrecke(aFzg, dNeuerZeitIntervall); //Weitergabe der gefahrenen Strecke seit dNeuerZeitIntervall */
}
