//
// Created by Micha on 25/12/2022.
//

#ifndef AUFGABENBLOCK_2_VERHALTEN_H
#define AUFGABENBLOCK_2_VERHALTEN_H

class Weg;
class Fahrzeug;

class Verhalten { // @suppress("Class has a virtual method and non-virtual destructor")
protected:
    Weg* p_pWeg; //Pointer auf den Weg des Fahrzeugs

public:
    Verhalten(Weg& weg); //Konstruktor mit Weg

    Weg* getWeg(); //Getter für p_pWeg
    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0; //Berechnet die gefahrene Strecke und prüft ob das Wegende erreicht wurde
};


#endif //AUFGABENBLOCK_2_VERHALTEN_H
