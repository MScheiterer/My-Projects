//
// Created by Micha on 02/01/2023.
//

#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"

//Konstruktor mit Weg und Fahrzeug
Losfahren::Losfahren(Weg &weg, Fahrzeug &fahrzeug) : Fahrausnahme(weg, fahrzeug) {}

//Ausgabe von Weg und Fahrzeug sowie Nachricht "Losfahren"
void Losfahren::vBearbeiten() {
    std::cout << "Losfahren." << std::endl;
    Weg::vKopf();
    //std::cout << p_pWeg << std::endl;
    Fahrzeug::vKopf();
    std::cout << p_pFahrzeug << std::endl;

    unique_ptr<Fahrzeug> tempFahrzeug = p_pWeg.pAbgabe(p_pFahrzeug); //temp speichert das aus dem Weg gelöschte Fahrzeug
    p_pWeg.vAnnahme(move(tempFahrzeug)); //Fahrzeug wird hinten wieder auf den Weg gesetzt
}
