//
// Created by Micha on 02/01/2023.
//

#ifndef AUFGABENBLOCK_2_LOSFAHREN_H
#define AUFGABENBLOCK_2_LOSFAHREN_H
#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
    Losfahren(Weg& weg, Fahrzeug& fahrzeug); //Konstruktor mit Weg und Fahrzeug

    void vBearbeiten() override; //Ausgabe von Weg und Fahrzeug sowie Nachricht "Losfahren"
};


#endif //AUFGABENBLOCK_2_LOSFAHREN_H
