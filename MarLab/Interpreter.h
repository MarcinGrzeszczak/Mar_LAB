#ifndef Interpreter_h
#define Interpreter_h

#include <iostream>
#include <string>

#include "struktury.h"
#include "Obsluga_zmiennych.h"
#include "Obliczenia.h"
#include "Macierz.h"
#include "wykres.h"
#include <thread>
using namespace std;



class Interpreter
{
	private:
		void Wyswietl(zmienna odczyt);
		Obsluga_zmiennych Baza_zmienne;
		Obliczenia *Obl;
		Macierz macierz;
		Wykres rysowanie_wykres;

	public:
		Interpreter();
		void parser(string wiersz, int argc, char **argv);
		
};

#endif