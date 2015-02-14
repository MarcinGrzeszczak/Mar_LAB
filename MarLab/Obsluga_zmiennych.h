#ifndef Obsluga_zmiennych_h
#define Obsluga_zmiennych_h
#include <vector>

#include "struktury.h"
using namespace std;


class Obsluga_zmiennych
{
	private:
		
		zmienna tymczasowa;
		vector<zmienna> Baza_zmiennych;
	public:
		
		int wielkosc_bazy();
		void Dodawanie_zmiennych(string zmienna, string komenda,int kolumny,int wiersze,zespolone *dane);
		zmienna Odczytywanie_zmiennych(string nazwa);
		bool czy_liczba(string komenda);
		bool czy_zespolona(string komenda);
};

#endif