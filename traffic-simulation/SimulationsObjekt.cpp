//
// Created by Micha on 24/12/2022.
//

#include <iostream>
#include "SimulationsObjekt.h"
#include <iomanip>
using namespace std;

//Konstruktor
SimulationsObjekt::SimulationsObjekt() {
    cout << "Simulations Objekt: " << p_sName << "\t\t\t\t ID: " << p_iID << " was created." << endl;
}

//Konstruktor mit Name
SimulationsObjekt::SimulationsObjekt(string name) : p_sName(name) {
    cout << "Simulations Objekt: " << p_sName << "\t\t\t\t ID: " << p_iID << " was created." << endl;
}

//Destruktor
SimulationsObjekt::~SimulationsObjekt() {
    cout << "Simulations Objekt: " << p_sName << "\t\t\t\t ID: " << p_iID << " was destroyed." << endl;
}

//Tabellarische Ausgabe der Daten
void SimulationsObjekt::vAusgeben(std::ostream &os) const {
    os << setfill(' ') << setw(100);
    os << setw(2) << setiosflags(ios_base::right) << p_iID << resetiosflags(ios_base::right)
       << setw(13) << setiosflags(ios_base::right) << p_sName << resetiosflags(ios_base::right);
}

//Überladung des Vergleichs Operators
bool SimulationsObjekt::operator==(const SimulationsObjekt &simObj) const {
	if (&simObj != nullptr) {
		return (p_iID == simObj.p_iID);
	}
    return false;
}

//Getter für p_sName
string SimulationsObjekt::getName() const {
	if (this != nullptr) {
		return p_sName;
	}
	return "-";
}

//Überladung des << Operators
ostream& operator<<(ostream& os, const SimulationsObjekt& simObj) {
    simObj.vAusgeben(os);
    return os;
}


