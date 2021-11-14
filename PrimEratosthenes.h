/*
 * main.cpp
 *
 * Copyright 2020 Hans Ulrich Ritter <uli.ritter@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 * Hier werden Primzahlen nach dem Sieb des Erastosthenes gerechnet
 */

#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iterator>
  
//#define WINDOWS
#define C_WRITE
//*******************************************************
//  Schreibe die Primzahlen in eine Datei
//*******************************************************
#ifdef WINDOWS
    #define DATNAMTEMP  "C:\\tmp\\test.dat"
    #define DATNAM ".\\test.dat"
    #define DATNAM1TEMP  "C:\\tmp\\test1.dat"
    #define DATNAM1 ".\\test1.dat"
#else
    #define DATNAMTEMP  "/tmp/test.dat"
    #define DATNAM "./test.dat"
    #define DATNAM1TEMP  "/tmp/test1.dat"
    #define DATNAM1 "./test1.dat"
#endif

  using namespace std;
// die Zahl läuft noch ohne SWAP (8GB-RAM)
//            44333222111  -> 55 Milliarden
#define ZAHL  55000000000ULL

class PrimEratosthenes
{

public:

//*******************************************************
// Konstruktor
//*******************************************************
PrimEratosthenes (unsigned long long f) {
    zahl = f;
    berechne();
    cout << "Schreibe raus ..." << endl;
    SetCachedPrim ();
    schreibeAufPlatte();
    kopiere_datei(DATNAM1TEMP, DATNAM1);
}

//*******************************************************
// Destruktor
//*******************************************************
~PrimEratosthenes() {
	a.clear();
}

private:

//*******************************************************
//  Die Primzahlen in eine tmp-Datei
//*******************************************************
void SetCachedPrim ()
{
  // oeffne die Datei zum schreiben
#ifdef C_WRITE
  FILE*  fout = fopen (DATNAMTEMP, "w");
#else
  ofstream fout (DATNAMTEMP);
#endif
  
  // laufe ueber alle Primzahlfelder
  unsigned long long s = a.size();
  for (unsigned long long i = 2; i < s; i++) {
      // schreibe in die Datei
#ifdef C_WRITE
      if (a[i] == true) fprintf (fout,"%llu\n",i);
#else
      if (a[i] == true)  fout <<  i << endl;
#endif
  }

  // schliesse die Datei
#ifdef C_WRITE
  fclose (fout);
#else
  fout.close ();
#endif

  kopiere_datei(DATNAMTEMP, DATNAM);
}

//*******************************************************
//  Schreibe das Array auf Platte
//*******************************************************
void schreibeAufPlatte() {
	cout << "Schreibe ..." << endl;
	ofstream fout(DATNAM1TEMP, ios::out | ios::binary);
	std::ostream_iterator<unsigned long long>  out_iter(fout);
	copy (a.begin(), a.end(), out_iter);
}
/**
*******************************************************
  Lese das Array von Platte
*******************************************************
void leseVonPlatte() {
	cout << "Lade ..." << endl;
	ifstream fin(DATNAM1TEMP,ios::in | ios::binary);
	std::istream_iterator<unsigned long long>  in_iter(fin);
	copy (a.begin(), a.end(), in_iter);
}
**/
//*******************************************************
//  kopiere die Temp-Datei in das Verzeichnis
//*******************************************************
void kopiere_datei(const char* quelle, const char* ziel) {
	
	cout << "Kopiere Datei von " << quelle << " nach " << ziel << endl;
#ifdef C_WRITE
  FILE*  fin  = fopen (quelle, "r");
  FILE*  fout = fopen (ziel, "w");
  int c = 0;
  do {
	  c = fgetc(fin);
	  fputc (c,fout);
  } while (c != EOF);
  fclose (fin);
  fclose (fout);
#else
    // lösche die Zieldatei
    remove (ziel);
    // Die Eingabe-Datei
    ifstream fin(quelle,ios::in);
    // Die Ausgabe-Datei
    ofstream fout(ziel,ios::out);

	// laufe über den gesamten Strom
    while (fin.good()) {
		
		// entnehme ein Zeichen aus dem Strom
		s = fin.get();
		// setze das Zeichen in den neuen Strom
		if (!fin.eof()) fout.put(s);

    }
    fin.close();
    fout.close();
    // lösche die Temp-Datei
    remove (quelle);
#endif
}

//*******************************************************
//  Die Funktion für das Multi-Theading
//*******************************************************
void Sieb_Fuellen(unsigned long long i) {

        // Der Faktor des Durchlaufes (i) begrenzt durch die
        // Multiplikation in der Schleife
        unsigned long long mult = (unsigned long long) zahl / i;

        // zeig mal den Stand
        cout << "aktuelle Zahl : " << i << endl;

	// laufe über den gesamten Zahlenstrahl
	// und streiche die Vielfachen heraus
	for (unsigned long long k = 17ULL; k < mult; k++) {
		a[i*k] = false;  // hier werden die Vielfachen markiert
	}	
}

//*******************************************************
//  Belege vor
//*******************************************************
void belegeVor(unsigned long long zahl) {

    cout << "Init Vector..." << endl;
    
    for (unsigned long long i = 4ULL; i < zahl; i++) {
        // es ist keine Primzahl
        a[i] = false;
        // nächstes i, wenn modulo erfolgreich (immernoch keine Primzahl)
        if (i % 2ULL  == 0ULL)      { continue; }
        else if (i % 3ULL  == 0ULL) { continue; }
        else if (i % 5ULL  == 0ULL) { continue; }
        else if (i % 7ULL  == 0ULL) { continue; }
        else if (i % 11ULL == 0ULL) { continue; }
        else if (i % 13ULL == 0ULL) { continue; }
        // es ist doch eine Primzahl
        a[i] = true;
    }
    // belege vor
    a[2]=true;
    a[3]=true;
    a[5]=true;
    a[7]=true;
    a[11]=true;
    a[13]=true;
}

//*******************************************************
//  berechne
//*******************************************************
void berechne () {

    cout << "Hole Speicherplatz ..." << endl;
    a.clear();
    a.resize (zahl);
    
    belegeVor(zahl);

    // laufe mit den Primzahlen nur bis zur Wurzel
    unsigned long long ende = (unsigned long long) sqrt(zahl) +100ULL;

    cout << "Sieben bis : " << ende << endl;

    // laufe über alle zahlen deren
    // Vielfache herausgestrichen werden sollen
    for (unsigned long long i = 17ULL; i < ende; i++) {

        // eine Nicht-Primzahl soll keinen
        // Stamm für einen Durchlauf begründen
        if (a[i] == false) continue;

		//Setze die Vielfachen in das Sieb
		Sieb_Fuellen(i);
    }
}

// das leistungsfähigste Speichermodell
// malloc und co. kommen nicht bis ULL
// das ist eine spezielle Klasse auf Bit-Ebene
vector<bool> a;
unsigned long long zahl;

}; // end class
