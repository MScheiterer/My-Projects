//
// Created by Micha on 30/12/2022.
//

#ifndef AUFGABENBLOCK_2_PARKEN_H
#define AUFGABENBLOCK_2_PARKEN_H

#include "Verhalten.h"

class Parken : public Verhalten { // @suppress("Class has a virtual method and non-virtual destructor")
private:
    double p_dStartzeit = 0.0; //Zeit wann das Fahrzeug losfährt

public:
    Parken(Weg& weg, double dStartzeit); //Konstruktor mit Referenz auf einen Weg und Startzeit

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override; //Prüft ob das Fahrzeug schon fahren darf, gibt ab Startzeit gefahrene Strecke weiter
};


#endif //AUFGABENBLOCK_2_PARKEN_H
