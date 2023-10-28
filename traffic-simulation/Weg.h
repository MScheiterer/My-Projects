//
// Created by Micha on 24/12/2022.
//

#ifndef AUFGABENBLOCK_2_WEG_H
#define AUFGABENBLOCK_2_WEG_H

#include <iostream>
#include <list>
#include <memory>
#include "Tempolimit.h"
#include "SimulationsObjekt.h"
#include "SimuClient.h"
#include "vertagt_liste - Vorlage.h"

class Fahrzeug; //Initialisierung von Fahrzeug, Aufruf von Fahrzeug.h würde zur Rekursion führen
class Kreuzung;

class Weg : public SimulationsObjekt { // @suppress("Class has a virtual method and non-virtual destructor")
private:
    double p_dLaenge = 0.0; //Länge des Weges
    vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge = {}; //Liste aller sich auf dem Weg befindenden Fahrzeuge
    const weak_ptr<Kreuzung> p_pZielKreuzung; //Pointer auf den Knoten zu dem der Weg führt
    weak_ptr<Weg> p_pRueckWeg; //Pointer auf den zugehörigen Rückweg, nicht const da 2 Wege nicht gleichzeitig erstellt werden können (setter benötigt)
    Tempolimit p_eTempolimit = Tempolimit::Autobahn; //Enum Objekt, entweder Innerorts (50), Außerorts (100) oder Autobahn (Unbegrenzt)


public:
    Weg(); //Konstruktor
    Weg(string name, double laenge, shared_ptr<Weg> rueckWeg, shared_ptr<Kreuzung> zielKreuzung, Tempolimit tempolimit = Tempolimit::Autobahn); //Konstruktor mit Name, Länge, Zielkreuzung, Rückweg und optionalem Tempolimit

    shared_ptr<Kreuzung> pGetZiel();
    shared_ptr<Weg> pGetRWeg();
    void vSetRWeg(shared_ptr<Weg> rWeg);
    double getTempolimit() const; //Getter für p_eTempolimit
    void vSimulieren() override; //Ruft Fahrzeug::vSimulieren für jedes Fahrzeug auf dem Weg
    void vAusgeben(ostream& os = cout) const override; //Tabellarische Ausgabe der Daten
    static void vKopf(); //Ausgabe der Tabellenüberschrift
    double dGetLaenge() const; //Getter für p_dLaenge
    void vFAusgeben(); //Ruft Fahrzeug::vAusgeben für jedes Fahrzeug auf dem Weg
    void vAnnahme(unique_ptr<Fahrzeug> f1); //Setzt ein Fahrzeug auf den Weg und aktualisiert p_pFahrzeuge
    void vAnnahme(unique_ptr<Fahrzeug> f1, double dStartzeit); //Setzt ein Parkendes Fahrzeug auf den Weg und aktualisiert p_pFahrzeuge
    unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);
};


#endif //AUFGABENBLOCK_2_WEG_H
