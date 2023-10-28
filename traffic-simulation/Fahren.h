/*
 * Fahren.h
 *
 *  Created on: 13 Jan 2023
 *      Author: Micha
 */

#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"

class Fahrzeug;
class Weg;

class Fahren : public Verhalten { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	Fahren(Weg& weg);

	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override; //Berechnet die gefahrene Strecke und prüft ob das Wegende erreicht wurde
};

#endif /* FAHREN_H_ */
