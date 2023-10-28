//
// Created by Micha on 02/01/2023.
//

#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"

//Konstruktor mit Weg und Fahrzeug
Fahrausnahme::Fahrausnahme(Weg& weg, Fahrzeug& fahrzeug) :
p_pWeg(weg),
p_pFahrzeug(fahrzeug) {}


