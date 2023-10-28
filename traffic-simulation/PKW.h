//
// Created by Micha on 28/11/2022.
//

#ifndef AUFGABENBLOCK_2_PKW_H
#define AUFGABENBLOCK_2_PKW_H
#include "Fahrzeug.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;


class PKW : public Fahrzeug
{
private:
    const double p_dVerbrauch; //Liter pro 100km
    const double p_dTankvolumen; //Liter
    double p_dTankinhalt;
    double p_dGesamtVerbrauch = 0; //Liter

public:
    PKW(string name, double speed, double verbrauch, double tankvolumen = 55); //Konstruktor
    double dTanken(double dMenge = numeric_limits<double>::infinity()) override; //Lässt den PKW tanken
    void vSimulieren() override; //Simuliert den PKW und prüft den Tankinhalt
    void vAusgeben(ostream& os = cout) const override; //Schriftliche Ausgabe der Werte des PKWs
    double dGeschwindigkeit() const override; //Gibt die Geschwindigkeit basierend auf dem Tempolimit aus
    double dGetTankinhalt() const override; //Getter für den aktuellen Tankinhalt
    void vZeichnen(const Weg& weg) const override; //Grafische Darstellung des PKWs auf dem übergebenen Weg
};


#endif //AUFGABENBLOCK_1_PKW_H
