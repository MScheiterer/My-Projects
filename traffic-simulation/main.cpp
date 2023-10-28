#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimulationsObjekt.h"
#include "Weg.h"
#include "Verhalten.h"
#include "Streckenende.h"
#include "Losfahren.h"
#include "SimuClient.h"
#include "vertagt_liste - Vorlage.h"
#include "vertagt_aktion - Vorlage.h"
#include "Kreuzung.h"

double dGlobaleZeit = 0.0;
/*

//Testet neue Klasse "Weg" sowie überladenen Operator. Aufgabenblock_1 funktioniert immernoch.
void vAufgabe_4() {
    Weg weg = Weg("weg", 10);
    cout << weg << endl;
    Weg::vKopf();
    weg.vAusgeben();
}

//Testet Simulation von Fahrzeugen auf Wegen sowie die Implementierung von Parkenden Fahrzeugen
void vAufgabe_5() {
    Weg weg = Weg("Brahmsweg", 30, Tempolimit::Innerorts);
    unique_ptr<Fahrzeug> audi = make_unique<Fahrzeug>("Audi A6", 200);
    unique_ptr<Fahrzeug> BMW = make_unique<Fahrzeug>("BMW i8", 220);
    unique_ptr<Fahrzeug> golf = make_unique<Fahrzeug>("VW Golf", 160);

    Weg::vKopf();
    weg.vAusgeben();

    cout << endl;
    cout << "Fahrzeuge fahren auf den Weg" << endl;

    //Fahrzeuge bekommen eine Startzeit
    double AudiZeit = 0.0;
    double BMWZeit = 0.05;
    double VWZeit = 0.15;

    dGlobaleZeit = 0.01;

    //Fahrzeuge werden auf den Weg gesetzt
    weg.vAnnahme(audi, AudiZeit);
    weg.vAnnahme(BMW, BMWZeit);
    weg.vAnnahme(golf, VWZeit);

    cout << endl;

    dGlobaleZeit = 0.15; //0.1, 0.2 to show functionality

    //Fahrzeuge werden simuliert und die Werte ausgegeben
    weg.vSimulieren();
    Weg::vKopf();
    weg.vAusgeben();
    weg.vFAusgeben();
}

//Streckenende und Losfahren implementiert via Exception handling
//Tempolimit wird beim befahren eines Weges berücksichtigt
//Testet auch Grafik Ausgabe
void vAufgabe_6() {
    Weg weg1 = Weg("weg1", 500, Tempolimit::Autobahn);
    Weg weg2 = Weg("weg2", 500, Tempolimit::Autobahn);

    unique_ptr<Fahrzeug> Audi = make_unique<PKW>("Audi", 200, 5, 50);
    unique_ptr<Fahrzeug> Porsche = make_unique<PKW>("P911", 280, 5, 50);

    double PorscheZeit = 1.0; //Startzeit für Porsche

    weg1.vAnnahme(Audi); //PKWs werden auf den Weg platziert
    weg2.vAnnahme(Porsche, PorscheZeit); //Porsche parkt anfangs


    //Test der Grafik Ausgabe
    int GroesseX = 800;
    int GroesseY = 500; //X und Y bestimmen die Fenster Größe
    int zeit_ms = 500; //Pausiert den Code damit die Grafik AUsgabe leichter zu verfolgen ist
    int Koordinaten[] = {750, 250, 100, 250}; //Koordinaten des Polygonzugs der zur Darstellung eines Weges verwendet wird

    bInitialisiereGrafik(GroesseX, GroesseY); //Öffnet ein Fenster
    bZeichneStrasse("weg1", "weg2", 500, 2, Koordinaten); //Zeichnet eine Strasse mit Hilfe von 2 Wegen

    while (dGlobaleZeit <= 3.000000001) {

    	vSetzeZeit(dGlobaleZeit); //Aktualisiert die Globale Zeit im Grafik Fenster

    	weg1.vSimulieren(); //Fahrzeuge werden simuliert
    	weg2.vSimulieren();

    	weg1.vFZeichnen(); //Fahrzeuge werden auf der Strasse gezeichnet
    	weg2.vFZeichnen();

    	vSleep(zeit_ms);

    	dGlobaleZeit += 0.2;
    }

    vSleep(9999); //kurze Pause erleichtert Analyse der Grafik


    //Alter code ohne Grafik Ausgabe

    while (dGlobaleZeit < 3.0) {
        dGlobaleZeit += 0.6;
        weg1.vSimulieren();
        weg2.vSimulieren();
    }

    //Ausgabe der Werte im Terminal
    Weg::vKopf();
    weg1.vAusgeben();
    weg2.vAusgeben();

    cout << endl;

    Fahrzeug::vKopf();
    weg1.vFAusgeben();
    weg2.vFAusgeben();

}*/

//Testet Implementierung von VListe und vAktualisieren()
void vAufgabe_6a() {
	vertagt::VListe<int> liste;

	//Notwendig für Zufallsgenerator
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1,10); // distribution in range [1, 6]

	for (int i = 0; i < 10; i++) { //Füllt die VListe mit zufälligen Zahlen zwischen 1 und 10
		liste.push_back(dist6(rng));
	}

	liste.vAktualisieren();

	std::cout << "Schritt 1: " << endl;
	for (auto p : liste) { //Ausgabe der Elemente in der Liste
		std::cout << p << std::endl;
	}

	for (vertagt::VListe<int>::iterator it = liste.begin(); it != liste.end(); ++it) {
		if (*it > 5) {
			liste.erase(it); //Gibt Auftrag weiter alle Elemente größer als 5 zu löschen
		}
	}

	std::cout << "Schritt 2: " << endl;
	for (auto p : liste) { //Ausgabe der Elemente in der Liste, immernoch gleich da noch nicht aktualisiert wurde
		std::cout << p << std::endl;
	}

	liste.vAktualisieren();

	std::cout << "Schritt 3: " << endl;
	for (auto p : liste) { //Ausgabe der Elemente in der Liste, jetzt aktualisiert
		std::cout << p << std::endl;
	}
}

void vAufgabe_7() {
	shared_ptr<Kreuzung> Kr1 = make_shared<Kreuzung>("Kr1", 0);
	shared_ptr<Kreuzung> Kr2 = make_shared<Kreuzung>("Kr2", 1000);
	shared_ptr<Kreuzung> Kr3 = make_shared<Kreuzung>("Kr3", 0);
	shared_ptr<Kreuzung> Kr4 = make_shared<Kreuzung>("Kr4", 0);

	Kreuzung::vVerbinde("W12", "W21", 40.0, Kr1, Kr2, Tempolimit::Innerorts);
	Kreuzung::vVerbinde("W23a", "W32a", 115.0, Kr2, Kr3);
	Kreuzung::vVerbinde("W23b", "W32b", 40.0, Kr2, Kr3, Tempolimit::Innerorts);
	Kreuzung::vVerbinde("W24", "W42", 55.0, Kr2, Kr4, Tempolimit::Innerorts);
	Kreuzung::vVerbinde("W44a", "W44b", 130.0, Kr4, Kr4, Tempolimit::Landstrasse);

	unique_ptr<Fahrzeug> auto1 = make_unique<PKW>("auto1", 150, 10, 100);
//	unique_ptr<Fahrzeug> auto2 = make_unique<PKW>("auto2", 200, 15, 100);
//	unique_ptr<Fahrzeug> auto3 = make_unique<PKW>("auto3", 250, 20, 100);
//	unique_ptr<Fahrzeug> auto4 = make_unique<PKW>("auto4", 125, 10, 100);
//	unique_ptr<Fahrzeug> auto5 = make_unique<PKW>("auto5", 175, 15, 100);
//	unique_ptr<Fahrzeug> auto6 = make_unique<PKW>("auto6", 225, 20, 100);

	double startZeit1 = 3.0;
//	double startZeit2 = 0.4;
//	double startZeit3 = 2.0;
//	double startZeit4 = 0.0;
//	double startZeit5 = 0.15;
//	double startZeit6 = 0.0;

	Kr1->vAnnahme(move(auto1), startZeit1);
//	Kr1->vAnnahme(move(auto2), startZeit2);
//	Kr1->vAnnahme(move(auto3), startZeit3);
//	Kr2->vAnnahme(move(auto4), startZeit4);
//	Kr4->vAnnahme(move(auto5), startZeit5);
//	Kr3->vAnnahme(move(auto6), startZeit6);

	//Test der Grafik Ausgabe
	int GroesseX = 1000;
	int GroesseY = 800; //X und Y bestimmen die Fenster Größe
	int Koordinaten12[] = {680, 40, 680, 300}; //Strasse 1, 2 Paare
	int Koordinaten23a[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570}; //Strasse 2, 6 Paare
	int Koordinaten23b[] = {680, 300, 680, 570}; //Strasse 3, 2 Paare
	int Koordinaten24[] = {680, 300, 320, 300}; //Strasse 4, 2 Paare
	int Koordinaten34[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300}; //Strasse 5, 5 Paare
	int Koordinaten44[] = {320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300}; //Strasse 6, 7 Paare

	bInitialisiereGrafik(GroesseX, GroesseY); //Öffnet ein Fenster

	bZeichneKreuzung(680, 40); //Kr1
	bZeichneKreuzung(680, 300); //Kr2
	bZeichneKreuzung(680, 570); //Kr3
	bZeichneKreuzung(320, 300); //Kr4
	bZeichneStrasse("W12", "W21", 40, 2, Koordinaten12); //Strasse 1
	bZeichneStrasse("W23a", "W32a", 115, 6, Koordinaten23a); //Strasse 2
	bZeichneStrasse("W23b", "W32b", 40, 2, Koordinaten23b); //Strasse 3
	bZeichneStrasse("W24", "W42", 55, 2, Koordinaten24); //Strasse 4
	bZeichneStrasse("W34", "W43", 85, 5, Koordinaten34); //Strasse 5
	bZeichneStrasse("W44a", "W44b", 130, 7, Koordinaten44); //Strasse 6

	while (dGlobaleZeit <= 20) {
		std::cout << " ------------ \nTime: " << dGlobaleZeit << std::endl;
		vSetzeZeit(dGlobaleZeit); //Aktualisiert die Globale Zeit im Grafik Fenster

		Kr1->vSimulieren(); //Kreuzungen werden simuliert
		Kr2->vSimulieren();
		Kr3->vSimulieren();
		Kr4->vSimulieren();

		vSleep(200); //Pausiert den Code damit die Grafik AUsgabe leichter zu verfolgen ist

		dGlobaleZeit += 0.3;
	}

	vSleep(1000); //kurze Pause erleichtert Analyse der Grafik
	vBeendeGrafik();
}

int main() {
    //vAufgabe_4();
    //vAufgabe_5();
    //vAufgabe_6();
	//vAufgabe_6a();
	vAufgabe_7();
}


