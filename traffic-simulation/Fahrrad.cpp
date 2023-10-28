//
// Created by Micha on 28/11/2022.
//

#include "Fahrrad.h"
//Konstruktor
Fahrrad::Fahrrad(string name, double speed) : Fahrzeug(name, speed) {}

//Berechnet die abnehmende Geschwindigkeit
//Geschwindigkeit nimmt alle 20km um 10% ab bis Min 12kmh
double Fahrrad::dGeschwindigkeit() const {
    double dCurSpeed = p_dMaxGeschwindigkeit;
    for (int i = 1; i <= p_dGesamtStrecke/20; i++) {
        if (dCurSpeed*0.9 >= 12) {
            dCurSpeed *= 0.9;
        }
        else {
            return 12;
        }
    }
    return dCurSpeed;
    }

//Grafische Darstellung des Fahrrads auf dem übergebenen Weg
void Fahrrad::vZeichnen(const Weg& weg) const {
	double dRelPos = (this->getAbschnittStrecke())/(weg.dGetLaenge()); //Berechnet die relative Position auf dem Weg
	bZeichneFahrrad(this->p_sName, weg.getName(), dRelPos, this->dGeschwindigkeit());
}
