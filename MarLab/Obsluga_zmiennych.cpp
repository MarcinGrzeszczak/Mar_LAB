#include "Obsluga_zmiennych.h"

void Obsluga_zmiennych::Dodawanie_zmiennych(string nazwa, string komenda, int kolumny,int wiersze, zespolone *dane)
{
	bool dodaj = true;
	tymczasowa.nazwa = nazwa;
	tymczasowa.komenda = komenda;
	tymczasowa.kolumny = kolumny;
	tymczasowa.wiersze = wiersze;
	tymczasowa.dane = new zespolone[kolumny*wiersze];
	for (int j = 0; j < (kolumny*wiersze); j++)
		tymczasowa.dane[j] = dane[j];

	for (int i = 0; i < Baza_zmiennych.size(); i++)
	{
		if (Baza_zmiennych[i].nazwa == nazwa)
		{
			Baza_zmiennych[i] = tymczasowa;
			dodaj = false;
			break;
		}
	}
	if (dodaj)
		Baza_zmiennych.push_back(tymczasowa);

}

zmienna Obsluga_zmiennych::Odczytywanie_zmiennych(string nazwa)
{
	//Baza_zmiennych[0] = tymczasowa;
	for (int i = 0; i < Baza_zmiennych.size(); i++)
	{
		if (Baza_zmiennych[i].nazwa == nazwa)
		{
			tymczasowa = Baza_zmiennych[i];
			break;
		}

		if (Baza_zmiennych[i].nazwa != nazwa && i == Baza_zmiennych.size() - 1)
		{
			tymczasowa.nazwa = "!@#$%^&*()";
		}
	}
	
	return tymczasowa;
}


bool Obsluga_zmiennych::czy_liczba(string komenda)
{
	for (int i = 0, liczba = 0; i < komenda.length(); i++)
	{
		if (komenda[i] >= 48 && komenda[i] <= 57)
			liczba++;

		if (liczba == komenda.length())
			return true;
	}
		return false;
}

bool Obsluga_zmiennych::czy_zespolona(string komenda)
{
	for (int i = 0; i < komenda[i]; i++)
	{
		if ((komenda[i] >= 97 && komenda[i]<105) || (komenda[i] > 106 && komenda[i] <= 122))
			return false;
		if (komenda[i] == 'i' || komenda[i] == 'j')
			return true;
	}
	return false;
}

int Obsluga_zmiennych::wielkosc_bazy()
{
	return Baza_zmiennych.size();
}