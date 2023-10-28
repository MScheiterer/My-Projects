//
// Created by Micha on 30/11/2022.
//

#ifndef AUFGABENBLOCK_2_FAHRZEUG_H
#define AUFGABENBLOCK_2_FAHRZEUG_H


#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <memory>
#include "SimulationsObjekt.h"

using namespace std;
class Verhalten; //Initialisierung der Klassen
class Weg; //Nicht als include da dies zur Rekursion führen würde

class Fahrzeug : public SimulationsObjekt { // @suppress("Class has a virtual method and non-virtual destructor")
protected:
    double p_dMaxGeschwindigkeit = 0.0; //Maximale Geschwindigkeit des Fahrzeugs
    double p_dGesamtStrecke = 0.0; //Insgesamt gefahrene Strecke
    double p_dAbschnittStrecke = 0.0; //Auf einem Weg gefahrene Abschnittstrecke
    shared_ptr<Verhalten> p_pVerhalten; //Pointer auf das Verhalten des Fahrzeugs, d.h. ob es parkt

public:
    Fahrzeug(); //Standard Konstruktor
    Fahrzeug(string name); //Konstruktor mit Name
    Fahrzeug(string name, double dSpeed); //Konstruktor mit Name und Geschwindigkeit
    Fahrzeug(const Fahrzeug&) = delete; //Copy Konstruktor verboten

    static void vKopf(); //Ausgabe der Tabellen Überschrift
    void vAusgeben(ostream& os = cout) const override; //Ausgabe der Objektvariablen in Form einer Tabelle
    void vSimulieren() override; //Simulationsschritt, Berechnung der gefahrenen Strecke
    virtual double dTanken(double dMenge = numeric_limits<double>::infinity()); //Tank funktion -> returns 0 for Fahrräder and Fahrzeuge, is overridden for PKW
    bool operator<(const Fahrzeug& f1); //Überladung des < Operators
    virtual double dGeschwindigkeit() const; //Berechnet die Geschwindigkeit der Fahrzeuge, overridden für PKW
    double getAbschnittStrecke() const; //Getter für die p_dAbschnittStrecke
    virtual double dGetTankinhalt() const; //Getter für den Tankinhalt, gibt 0 weiter und wird in PKW überschrieben
    void vNeueStrecke(Weg& weg); //Aktualisiert p_pVerhalten basierend auf dem übergebenen Weg
    void vNeueStrecke(Weg& weg, double dStartzeit); //Aktualisiert p_pVerhalten basierend auf dem übergebenen Weg zu Parken
    void increaseGesamtZeit(double dZeit); //Erhöht p_dGesamtZeit um die übergebene Zeit
    Fahrzeug& operator=(const Fahrzeug& f1); //Überladung des '=' Operators -> ID soll nicht kopiert werden, da diese einzigartig sein soll
    virtual void vZeichnen(const Weg& weg) const; //Grafische Darstellung des Fahrzeugs
};

#endif //AUFGABENBLOCK_2_FAHRZEUG_H
