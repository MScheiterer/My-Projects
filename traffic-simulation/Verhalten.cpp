//
// Created by Micha on 25/12/2022.
//

#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"
#include "Losfahren.h"

//Konstruktor mit Weg
Verhalten::Verhalten(Weg& weg) {
    p_pWeg = &weg;
}

//Getter für p_pWeg
Weg* Verhalten::getWeg() {
    return p_pWeg;
}
