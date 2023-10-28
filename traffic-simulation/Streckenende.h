//
// Created by Micha on 02/01/2023.
//

#ifndef AUFGABENBLOCK_2_STRECKENENDE_H
#define AUFGABENBLOCK_2_STRECKENENDE_H

#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme {
public:
    Streckenende(Weg& weg, Fahrzeug& fahrzeug); //Konstruktor mit Referenzen auf einen Weg und ein Fahrzeug

    void vBearbeiten() override; //Ausgabe von Weg und Fahrzeug sowie Nachricht "Streckenende erreicht."
};


#endif //AUFGABENBLOCK_2_STRECKENENDE_H
