//
// Created by Micha on 24/12/2022.
//

#ifndef AUFGABENBLOCK_2_SIMULATIONSOBJEKT_H
#define AUFGABENBLOCK_2_SIMULATIONSOBJEKT_H
#include <string>
#include <iostream>
using namespace std;

class SimulationsObjekt {
protected:
    double p_dGesamtZeit = 0.0; //gesamte Fahrzeit des Objektes
    double p_dZeit = 0.0; //Zeit zu der das Objekt zuletzt simuliert wurde
    static inline int p_iMaxID = 0; //ID counter
    const int p_iID = p_iMaxID++; //ID
    string p_sName = ""; //Name

public:
    SimulationsObjekt(); //Konstruktor
    SimulationsObjekt(string name); //Konstruktor mit Name
    SimulationsObjekt(const SimulationsObjekt&) = delete; //Copy Konstruktor gelöscht

    virtual ~SimulationsObjekt(); //Destruktor

    virtual void vSimulieren() = 0; //Rein virtuelle Methode, macht SimulationsObjekt zu einer rein virtuellen Klasse.
    virtual void vAusgeben(ostream& os = cout) const; //Tabellarische Ausgabe der Daten
    string getName() const; //Getter für p_sName

    bool operator==(const SimulationsObjekt& f1) const; //Überladung des Vergleichs Operators
};

ostream& operator<<(ostream& os, const SimulationsObjekt& f1); //Überladung des Ausgabe Operators

#endif //AUFGABENBLOCK_2_SIMULATIONSOBJEKT_H
