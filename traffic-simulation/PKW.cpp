//
// Created by Micha on 28/11/2022.
//

#include "PKW.h"
#include "Verhalten.h"
#include "Weg.h"
#include "SimuClient.h"

//Konstruktor
PKW::PKW(string name, double speed, double verbrauch, double tankvolumen) :
    Fahrzeug(name, speed),
    p_dVerbrauch(verbrauch),
    p_dTankvolumen(tankvolumen),
    p_dTankinhalt(p_dTankvolumen / 2) {};

//Lässt den PKW tanken
double PKW::dTanken(double dMenge) { //dMenge set to infinity as it should fill any tank
    if (dMenge + p_dTankinhalt > p_dTankvolumen) { //Volltanken
        p_dTankinhalt = p_dTankvolumen;
        return p_dTankvolumen - p_dTankinhalt;
    }
    else { //Falls nicht vollgetankt wird, wird um eine bestimmte Menge erhört
        p_dTankinhalt += dMenge;
        return dMenge;
    }
} //getankte Menge wird weitergegeben

//Simuliert die Fahrt des PKWs und prüft den Tankinhalt
void PKW::vSimulieren() {
    double dStrecke = p_dGesamtStrecke;

    if (p_dTankinhalt > 0) { //prüft ob der PKW fahren kann
        Fahrzeug::vSimulieren(); //Simuliert wie ein Fahrzeug, Tank wird im Folgenden aktualisiert

        //Berechnung des verbrauchten Sprits sowie aktualisierung des Tankinhalts
        dStrecke = p_dGesamtStrecke - dStrecke; //p_dGesamtStrecke wurde in Fahrzeug::vSimulieren() aktualisiert,
        										//sodass dStrecke nun die Zwischenstrecke speichert
        p_dTankinhalt -= (dStrecke * p_dVerbrauch / 100 < p_dTankinhalt) ?
                         (dStrecke * p_dVerbrauch / 100) : p_dTankinhalt; //da der Verbrauch in L/100km is
        p_dGesamtVerbrauch = (p_dGesamtStrecke / 100) * p_dVerbrauch;
        if (p_dTankinhalt < 0) {
            p_dTankinhalt = 0;
        }
    }

    else { //Falls der PKW nicht fahren kann
        cout << "Bitte Tanken." << endl;
    }
}

//Schriftliche Ausgabe der Werte des PKWs
void PKW::vAusgeben(ostream& os) const {
    Fahrzeug::vAusgeben();
    os << setw(19) << setiosflags(ios_base::right) << p_dGesamtVerbrauch << resetiosflags(ios_base::right)
    << setw(15) << setiosflags(ios_base::right) << p_dTankinhalt << resetiosflags(ios_base::right);
}

//Gibt die Geschwindigkeit basierend auf dem Tempolimit aus
double PKW::dGeschwindigkeit() const {
    Weg* weg = p_pVerhalten->getWeg(); //Weg wird geholt um das Tempolimit zu bestimmen

    if (weg->getTempolimit() == numeric_limits<int>::max()) { //Falls unbegrenzt
    	return p_dMaxGeschwindigkeit;
    }
    else { //Falls ein Tempolimit existiert
    	return weg->getTempolimit();
    }
}

//Getter für den aktuellen Tankinhalt
double PKW::dGetTankinhalt() const {
	return p_dTankinhalt;
}

//Grafische Darstellung des PKWs auf dem übergebenen Weg
void PKW::vZeichnen(const Weg& weg) const {
	double dRelPos = (this->getAbschnittStrecke())/(weg.dGetLaenge()); //Berechnet die relative Position auf dem Weg
	bZeichnePKW(this->p_sName, weg.getName(), dRelPos, this->dGeschwindigkeit(), this->p_dTankinhalt);
}
