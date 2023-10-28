/*
 * Kreuzung.h
 *
 *  Created on: 11 Jan 2023
 *      Author: Micha
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include <list>
#include <memory>
#include "SimulationsObjekt.h"
#include "Tempolimit.h"

class Weg;
class Fahrzeug;

class Kreuzung : public SimulationsObjekt { // @suppress("Class has a virtual method and non-virtual destructor")
private:
	std::list<shared_ptr<Weg>> p_pWege = {}; //Speichert alle von der Kreuzung wegführenden Wege (Hin umd zurück)
	double p_dTankstelle = 0.0; //Speichert das verfügbare Tankvolumen an der Kreuzung

public:
	Kreuzung() = default;
	Kreuzung(string sName, double dTankVolumen);

	void vSimulieren() override; //noch nicht implementiert, muss deklariert werden wegen abstrakter Oberklasse
	static void vVerbinde(string sHinWeg, string sRueckWeg, double dStrassenLaenge, shared_ptr<Kreuzung> startKreuzung, shared_ptr<Kreuzung> zielKreuzung, Tempolimit tempolimit = Tempolimit::Autobahn); //Überholverbot als Parameter muss noch eingeführt werden
	void vTanken(Fahrzeug& fahrzeug);
	void vAnnahme(unique_ptr<Fahrzeug> fahrzeug, double dStartZeit);
	shared_ptr<Weg> pZufaelligerWeg(Weg& weg);

};

#endif /* KREUZUNG_H_ */
