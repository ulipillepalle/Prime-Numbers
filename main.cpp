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

#include "PrimEratosthenes.h"

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

