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

  using namespace std;
// die Zahl läuft noch ohne SWAP (8GB-RAM)
//            44333222111  -> 50 Milliarden
#define ZAHL  50000000000ULL

class PrimEratosthenes
{
public:
PrimEratosthenes (unsigned long long f) {
    zahl = f;
    berechne();
    cout << "Schreibe raus ..." << endl;
    SetCachedPrim ();
    //if (a != NULL) free(a);
}

private:
//*******************************************************
//  Schreibe die Primzahlen in eine Datei
//*******************************************************
void SetCachedPrim ()
{
  //if (a == NULL) return;
  // oeffne die Datei zum schreiben
  ofstream fout ("./test.dat");
/**
  // laufe ueber alle Primzahlfelder, gibt die falsche zahl heraus
  for (auto f = std::begin(a); f != std::end(a); ++f) {
      // schreibe in die Datei
      if (*f == true)  fout <<  *f. << endl;
  }
  **/
  // laufe ueber alle Primzahlfelder
  unsigned long long s = a.size();
  for (unsigned long long i = 2; i < s; i++) {
      // schreibe in die Datei
      if (a[i] == true)  fout <<  i << endl;
  }

  // schliesse die Datei
  fout.close ();
}


void berechne () {

    cout << "Hole Speicherplatz ..." << endl;
    a.clear();
    a.resize (zahl);
    cout << "Init Vector..." << endl;
    for (unsigned long long i = 0ULL; i < zahl; i++) {
        // wir nehmen eine Primzahl an
        bool bStat = true;
        // wenn wir schon initialisieren, dann
        // sparen wir doch direkt ein paar Durchläufe
        if (i % 2ULL  == 0ULL)      { bStat = false; }
        else if (i % 3ULL  == 0ULL) { bStat = false; }
        else if (i % 5ULL  == 0ULL) { bStat = false; }
        else if (i % 7ULL  == 0ULL) { bStat = false; }
        else if (i % 11ULL == 0ULL) { bStat = false; }
        else if (i % 13ULL == 0ULL) { bStat = false; }
        // setze den Wert, einmalig
        a[i] = bStat;
    }
    // belege vor
    a[2]=true;
    a[3]=true;
    a[5]=true;
    a[7]=true;
    a[11]=true;
    a[13]=true;

    // laufe mit den Primzahlen nur bis zur Wurzel
    unsigned long long ende = (unsigned long long) sqrt(zahl);

    cout << "Sieben bis : " << ende << endl;

    // laufe über alle zahlen deren
    // Vielfache herausgestrichen werden sollen
    for (unsigned long long i = 14ULL; i < ende; i++) {

        // eine Nicht-Primzahl soll keinen
        // Stamm für einen Durchlauf begründen
        if (a[i] == false) continue;

        // Der Faktor des Durchlaufes (i) begrenzt durch die
        // Multiplikation in der Schleife
        unsigned long long mult = (unsigned long long) zahl / i;

        // zeig mal den Stand
        cout << "aktuelle Zahl : " << i << endl;

        // laufe über den gesamten Zahlenstrahl
        // und streiche die Vielfachen heraus
        for (unsigned long long k = 14ULL; k < mult; k++) {
            a[i*k] = false;  // hier werden die Vielfachen markiert
        }
    }
}

// das leistungsfähigste Speichermodell
// malloc und co. kommen nicht bis ULL
// das ist eine spezielle Klasse auf Bit-Ebene
vector<bool> a;
unsigned long long zahl;

}; // end class

int main(int argc, char **argv)
{
    if (argc < 2) {
	    cout << "Eingabe der Grenze vergessen ?" << endl;
	    return EXIT_FAILURE;
    }
    unsigned long long zahl = atoll(argv[1]);
    if (zahl == 0) return -1;
    cout << "Berechne : " << zahl << endl;
    PrimEratosthenes  toto (zahl);
}

