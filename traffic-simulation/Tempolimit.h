//
// Created by Micha on 24/12/2022.
//

#ifndef AUFGABENBLOCK_2_TEMPOLIMIT_H
#define AUFGABENBLOCK_2_TEMPOLIMIT_H

#include <limits>
using namespace std;

enum class Tempolimit { //Enum Objekt kann genau einen der definierten Werte annehmen
    Innerorts = 50,
    Landstrasse = 100,
    Autobahn = numeric_limits<int>::max()
};


#endif //AUFGABENBLOCK_2_TEMPOLIMIT_H
