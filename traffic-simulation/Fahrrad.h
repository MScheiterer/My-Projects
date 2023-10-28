//
// Created by Micha on 28/11/2022.
//

#ifndef AUFGABENBLOCK_2_FAHRRAD_H
#define AUFGABENBLOCK_2_FAHRRAD_H
#include "Fahrzeug.h"
#include "Weg.h"
#include <string>


class Fahrrad : public Fahrzeug
{
public:
    Fahrrad(string name, double speed); //Konstruktor

    double dGeschwindigkeit() const override; //Bestimmt die abnehmende Geschwindigkeit des Fahrrads
    void vZeichnen(const Weg& weg) const override; //Grafische Darstellung des Fahrrads auf dem übergebenen Weg
};


#endif //AUFGABENBLOCK_1_FAHRRAD_H
