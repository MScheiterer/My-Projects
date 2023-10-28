/*
 * Fahren.cpp
 *
 *  Created on: 13 Jan 2023
 *      Author: Micha
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

Fahren::Fahren(Weg& weg) : Verhalten(weg) {}

//Berechnet die gefahrene Strecke und prüft ob das Wegende erreicht wurde
double Fahren::dStrecke(Fahrzeug &aFzg, double dZeitIntervall) {
	double dDistanz = aFzg.dGeschwindigkeit() * dZeitIntervall; //ZeitIntervall in Stunden, berechnet die neu gefahrene Strecke
	aFzg.increaseGesamtZeit(dZeitIntervall); //Erhöht p_dGesamtZeit um die seit dem letzten Simulationsschritt vergangene Zeit

	if (dDistanz >= p_pWeg->dGetLaenge() - aFzg.getAbschnittStrecke()) { //Falls Wegende erreicht wurde
		throw Streckenende(*p_pWeg, aFzg);
	} else {
		return dDistanz; //Falls Wegende nicht erreicht wurde wird die gefahrene Distanz ausgegeben
	}
	return p_pWeg->dGetLaenge() - aFzg.getAbschnittStrecke(); //Gibt Strecke bis Wegende aus
}

