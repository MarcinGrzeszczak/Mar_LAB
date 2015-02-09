#ifndef Obliczenia_h
#define Obliczenia_h

#include <iostream>
#include <string>
#include "Obsluga_zmiennych.h"
using namespace std;

class Obliczenia
{
	private:
		vector<string> Dzialanie;
		vector<string> tymczas;
		vector<zmienna> tymczasowe_zmienne;
		void podstawowe_operacje(int pocz, int kon);
		float trygonometria(string dz,float liczba);
		Obsluga_zmiennych baza_zmienne;

	public:
		Obliczenia(Obsluga_zmiennych zmienne);
		zmienna Oblicz(string komenda);
};

#endif