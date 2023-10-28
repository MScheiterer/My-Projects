//
// Created by Micha on 24/12/2022.
//

#include "Weg.h"
#include "Fahrzeug.h"
#include "vertagt_liste - Vorlage.h"
#include "Kreuzung.h"
#include "Fahrausnahme.h"

//Konstruktor
Weg::Weg() : SimulationsObjekt() {}

//Konstruktor mit Name, Länge, Zielkreuzung, Rückweg und optionalem Tempolimit
Weg::Weg(std::string name, double laenge, shared_ptr<Weg> rueckWeg, shared_ptr<Kreuzung> zielKreuzung, Tempolimit tempolimit):
SimulationsObjekt(name),
p_dLaenge(laenge),
p_pZielKreuzung(zielKreuzung),
p_pRueckWeg(rueckWeg),
p_eTempolimit(tempolimit) {}

void Weg::vSetRWeg(shared_ptr<Weg> rWeg) {
	p_pRueckWeg = rWeg;
}

shared_ptr<Kreuzung> Weg::pGetZiel() {
	return p_pZielKreuzung.lock();
}

shared_ptr<Weg> Weg::pGetRWeg() {
	return p_pRueckWeg.lock();
}

//Getter für p_eTempolimit
double Weg::getTempolimit() const {
    return static_cast<double>(p_eTempolimit);
}

//Ruft Fahrzeug::vSimulieren für jedes Fahrzeug auf dem Weg
void Weg::vSimulieren() {
	p_pFahrzeuge.vAktualisieren();

    for (auto& p : p_pFahrzeuge) { //Iterates through every element in p_pFahrzeuge
    	try {
    		p->vSimulieren();
    		p->vZeichnen(*this);
    	}
    	catch (Fahrausnahme& e){
    		e.vBearbeiten();
    	}
    }
    p_pFahrzeuge.vAktualisieren();
}

//Tabellarische Ausgabe der Daten
void Weg::vAusgeben(ostream& os) const {
    SimulationsObjekt::vAusgeben(os);
    os << setw(17) << setiosflags(ios_base::right) << p_dLaenge << resetiosflags(ios_base::right);
    os << setw(9) << setiosflags(ios_base::right) << "(" << resetiosflags(ios_base::right);
    for (auto& p : p_pFahrzeuge) {
    	os << setiosflags(ios_base::right) << p->getName() << ", " << resetiosflags(ios_base::right);
    }
    os << ")" << std::endl;
}

//Ausgabe der Tabellenüberschrift
void Weg::vKopf() {
    cout << setfill(' ')
         << setw(2) << setiosflags(ios_base::right) << "ID" << resetiosflags(ios_base::right)
         << setw(8) << setiosflags(ios_base::right) << "Name" << resetiosflags(ios_base::right)
         << setw(22) << setiosflags(ios_base::right) << "Laenge" << resetiosflags(ios_base::right)
         << setw(17) << setiosflags(ios_base::right) << "Fahrzeuge" << resetiosflags(ios_base::right)
         << "\n";
    cout << setfill('-') << setw(87) << std::endl;
}

//Getter für p_dLaenge
double Weg::dGetLaenge() const {
    return p_dLaenge;
}

//Setzt ein Fahrzeug auf den Weg und aktualisiert p_pFahrzeuge
void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug) {
	if (this != nullptr) {
		fahrzeug->vNeueStrecke(*this); //Aktualisiert p_pVerhalten und p_dAbschnittstrecke des Fahrzeugs
		p_pFahrzeuge.push_back(move(fahrzeug)); //Schiebt das Fahrzeug ans Ende von p_pFahrzeuge
	}
}

//Setzt ein Parkendes Fahrzeug auf den Weg und aktualisiert p_pFahrzeuge
void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug, double dStartzeit) {
	if (this != nullptr) {
		fahrzeug->vNeueStrecke(*this, dStartzeit); //Aktualisiert p_pVerhalten (Parken) und p_dAbschnittstrecke des Fahrzeugs
    	p_pFahrzeuge.push_front(move(fahrzeug)); //Schiebt das Fahrzeug an den Anfang Ende von p_pFahrzeuge
	}
}
//Ruft Fahrzeug::vAusgeben für jedes Fahrzeug auf dem Weg
void Weg::vFAusgeben() {
    for (auto& p : p_pFahrzeuge) { //Iterates through every element in p_pFahrzeuge
        p->vAusgeben();
        cout << endl;
    }
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug) {
	unique_ptr<Fahrzeug> tempFahrzeug;
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) { //Iterates through every element in p_pFahrzeuge
		if (*it != nullptr) {
			if (fahrzeug == **it) {
				tempFahrzeug = move(*it);
				p_pFahrzeuge.erase(it);
				return tempFahrzeug;
			}
		}
	}
	std::cout << "ERROR - No matching car in list - ERROR" << std::endl;
	return nullptr;
}

