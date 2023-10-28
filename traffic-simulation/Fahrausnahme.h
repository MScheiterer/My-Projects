//
// Created by Micha on 02/01/2023.
//

#ifndef AUFGABENBLOCK_2_FAHRAUSNAHME_H
#define AUFGABENBLOCK_2_FAHRAUSNAHME_H
#include <iostream>

class Weg; //Initialisiert Weg als Objekt, aufruf ohne include Weg.h stellt sicher dass es nicht zur Rekursion fürht
class Fahrzeug; //Initialisiert Fahrzeug als Objekt

class Fahrausnahme : public std::exception { //Erbt von der Standard C++ Klasse Exception
protected:
    Weg& p_pWeg; //Referenz eines Weges
    Fahrzeug& p_pFahrzeug; //Referenz eines Fahrzeugs

public:
    Fahrausnahme(Weg& weg, Fahrzeug& fahrzeug); //Konstruktor mit Weg und Fahrzeug
    Fahrausnahme() = delete;
    virtual void vBearbeiten() = 0; //Rein virtuelle Methode, macht Fahrausnahme zu einer Abstrakten Klasse
};


#endif //AUFGABENBLOCK_2_FAHRAUSNAHME_H
