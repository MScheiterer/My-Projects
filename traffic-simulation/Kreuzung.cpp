/*
 * Kreuzung.cpp
 *
 *  Created on: 11 Jan 2023
 *      Author: Micha
 */

#include <random>
#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"

Kreuzung::Kreuzung(string sName, double dTankVolumen) : SimulationsObjekt(sName), p_dTankstelle(dTankVolumen) {}

void Kreuzung::vVerbinde(string sHinWeg, string sRueckWeg, double dStrassenLaenge, shared_ptr<Kreuzung> startKreuzung, shared_ptr<Kreuzung> zielKreuzung, Tempolimit tempolimit) {
	shared_ptr<Weg> hinWeg = make_shared<Weg>(sHinWeg, dStrassenLaenge, nullptr, zielKreuzung, tempolimit);
	shared_ptr<Weg> rueckWeg = make_shared<Weg>(sRueckWeg, dStrassenLaenge, hinWeg, startKreuzung, tempolimit);
	hinWeg->vSetRWeg(rueckWeg);

	startKreuzung->p_pWege.push_back(hinWeg);
	zielKreuzung->p_pWege.push_back(rueckWeg);
}

void Kreuzung::vTanken(Fahrzeug& fahrzeug) {
	if (p_dTankstelle > 0) {
		std::cout << "Getankt bei Kreuzung: " << this->getName() << std::endl;
		double dGetankteMenge = fahrzeug.dTanken();
		(p_dTankstelle - dGetankteMenge < 0) ? p_dTankstelle = 0 : p_dTankstelle -= dGetankteMenge;
	} else {
		std::cout << "Keine Tankstelle vorhanden auf Kreuzung: " << this->getName() << std::endl;
	}
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> fahrzeug, double dStartZeit) {
	this->vTanken(*fahrzeug);
	std::list<shared_ptr<Weg>>::iterator it = p_pWege.begin();
	shared_ptr<Weg> tempWeg = *it;
	tempWeg->vAnnahme(move(fahrzeug), dStartZeit);
}

void Kreuzung::vSimulieren() {
	for (auto& p : p_pWege) {
		p->vSimulieren();
	}
}

shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& weg) {

	if (p_pWege.size() == 1) { //falls die Kreuzung eine Sackgasse ist wird der Rückweg (einziges Element in p_pWege) gewählt
		return (*p_pWege.begin());

	} else { //Sonst wird ein zufälliger weg gewählt
		//Notwendig für Zufallsgenerator
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0,p_pWege.size()-1); // distribution in range [0, List size]

		std::list<shared_ptr<Weg>>::iterator it = p_pWege.begin();
		advance(it, dist6(rng));
		while ((*it) == weg.pGetRWeg()) {
		    it = p_pWege.begin(); //iterator wieder als List Anfang declared damit advance nicht out of range ist
			advance(it, dist6(rng));
		}
		return (*it);
	}
}


