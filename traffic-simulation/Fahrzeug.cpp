//
// Created by Micha on 30/11/2022.
//

#include "Fahrzeug.h"
#include "Weg.h"
#include "Parken.h"
#include "Fahren.h"

//Standard Konstruktor
Fahrzeug::Fahrzeug() : SimulationsObjekt() {}

//Konstruktor mit Name
Fahrzeug::Fahrzeug(string name) : SimulationsObjekt(name) {}

//Konstruktor mit Name und Geschwindigkeit
Fahrzeug::Fahrzeug(string name, double dSpeed) : SimulationsObjekt(name) {
    p_dMaxGeschwindigkeit = (dSpeed > 0) ? dSpeed : 0.0; //? operator returns speed if speed > 0 else returns 0.0
}

//Ausgabe der Tabellen Überschrift
void Fahrzeug::vKopf() {
    cout << setfill(' ')
         << setw(2) << setiosflags(ios_base::right) << "ID" << resetiosflags(ios_base::right)
         << setw(8) << setiosflags(ios_base::right) << "Name" << resetiosflags(ios_base::right)
         << setw(22) << setiosflags(ios_base::right) << "MaxGeschwindigkeit" << resetiosflags(ios_base::right)
         << setw(17) << setiosflags(ios_base::right) << "Gesamtstrecke" << resetiosflags(ios_base::right)
         << setw(19) << setiosflags(ios_base::right) << "Gesamtverbrauch" << resetiosflags(ios_base::right)
         << setw(15) << setiosflags(ios_base::right) << "Tank Inhalt" << resetiosflags(ios_base::right)
         << "\n";
    cout << setfill('-') << setw(87) << "\n";
}

//Ausgabe der Objektvariablen in Form einer Tabelle
void Fahrzeug::vAusgeben(ostream& os) const {
    SimulationsObjekt::vAusgeben();
    os << setw(22) << setiosflags(ios_base::right) << dGeschwindigkeit() << resetiosflags(ios_base::right)
       << setw(17) << setiosflags(ios_base::right) << p_dGesamtStrecke << resetiosflags(ios_base::right);
}

//Simulationsschritt, Berechnung der gefahrenen Strecke
void Fahrzeug::vSimulieren() {
    extern double dGlobaleZeit;
    p_dZeit = dGlobaleZeit - p_dGesamtZeit; //Berechnet die seit dem letzten Simulationsschritt vergangene Zeit
    double strecke = p_pVerhalten->dStrecke(*this, p_dZeit);
    //Aktualisiert Membervariablen um die neu gefahrene Distanz
    p_dAbschnittStrecke = p_dAbschnittStrecke + strecke;
    p_dGesamtStrecke = p_dGesamtStrecke + strecke;
}

//Tank funktion -> returns 0 for Fahrräder and Fahrzeuge, is overridden for PKW
double Fahrzeug::dTanken(double dMenge) {
    return 0;
}

//Berechnet die Geschwindigkeit der Fahrzeuge, overridden für PKW
double Fahrzeug::dGeschwindigkeit() const {
    return p_dMaxGeschwindigkeit;
}

//Überladung des '=' Operators -> ID soll nicht kopiert werden, da diese einzigartig sein soll
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& f1) {
    p_sName = f1.p_sName;
    p_dGesamtStrecke = f1.p_dGesamtStrecke;
    p_dMaxGeschwindigkeit = f1.p_dMaxGeschwindigkeit;
    p_dGesamtZeit = f1.p_dGesamtZeit;
    p_dZeit = f1.p_dZeit;
    return *this;
}

//Überladung des < Operators
bool Fahrzeug::operator<(const Fahrzeug& f1) {
    return (p_dGesamtStrecke < f1.p_dGesamtStrecke);
}

//Erhöht p_dGesamtZeit um die übergebene Zeit
void Fahrzeug::increaseGesamtZeit(double dZeit) {
    p_dGesamtZeit += dZeit;
}

//Aktualisiert p_pVerhalten basierend auf dem übergebenen Weg
void Fahrzeug::vNeueStrecke(Weg& weg) {
    p_pVerhalten = make_shared<Fahren>(weg);
    p_dAbschnittStrecke = 0.0; //Abschnittstrecke wird auf 0 gesetzt da dies ein neuer Weg ist
}

//Aktualisiert p_pVerhalten basierend auf dem übergebenen Weg zu Parken
void Fahrzeug::vNeueStrecke(Weg& weg, double dStartzeit) {
    p_pVerhalten = make_shared<Parken>(weg, dStartzeit);
    p_dAbschnittStrecke = 0.0; //Abschnittstrecke wird auf 0 gesetzt weil dies ein neuer Weg ist
}

//Getter für die p_dAbschnittStrecke
double Fahrzeug::getAbschnittStrecke() const {
    return p_dAbschnittStrecke;
}

//Getter für den Tankinhalt, gibt 0 weiter und wird in PKW überschrieben
double Fahrzeug::dGetTankinhalt() const {
	return 0.0;
}

//Grafische Darstellung des Fahrzeugs, overloaded in PKW und Fahrrad
void Fahrzeug::vZeichnen(const Weg& weg) const {}
