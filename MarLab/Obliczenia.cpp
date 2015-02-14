#include "Obliczenia.h"

Obliczenia::Obliczenia(Obsluga_zmiennych zmienne)
{
	baza_zmienne = zmienne;
}
zmienna Obliczenia::Oblicz(string komenda)
{
	string specjalne_znaki[] = { "sin", "cos", "tg", "ctg", "abs", "exp", "pierw", "(", ")", "^", "*", "/", "+", "-" };
	string tym = "";
	zmienna rob;
	int maximum = 1;
	////////////////////////////////////////////////////////

	for (int i = 0, zi = 0; i < komenda.length(); i++)
	{

		if (komenda[i] < 48 || komenda[i] > 57)
		{
			zi = i;
			for (int j = 0; j < sizeof(specjalne_znaki) / sizeof(string); j++)
			{
				for (int k = 0; k < specjalne_znaki[j].length(); k++)
				{
					if (komenda[zi] == specjalne_znaki[j][k])
					{
						tym += komenda[zi];
						zi++;
					}
				}
				if (zi == i + specjalne_znaki[j].length())
				{
					i = zi - 1;
					if (tym != "")
						Dzialanie.push_back(tym);
					break;
				}
				if (i == komenda.length() - 1)
				{
					//tym = "";
					while (zi == i)
					{
						tym += komenda[zi++];
					}
					Dzialanie.push_back(tym);
					break;
				}
			}
			tym = "";
		}
		else
		{
			for (int j = i; j <= komenda.length(); j++)
			{
				if ((komenda[j] < 48 || komenda[j] > 57) && komenda[j] != '.')
				{
					i = j - 1;
					break;
				}
				tym += komenda[j];
			}
			if (tym != "")
				Dzialanie.push_back(tym);
			tym = "";
		}

	}
	
	for (int i = 0; i < Dzialanie.size(); i++)
	{
		if (baza_zmienne.Odczytywanie_zmiennych(Dzialanie[i]).nazwa != "!@#$%^&*()")
		{
			tymczasowe_zmienne.push_back(baza_zmienne.Odczytywanie_zmiennych(Dzialanie[i]));
		}
	}

		for (int i = 0; i < tymczasowe_zmienne.size();i++)
			if (maximum < tymczasowe_zmienne[i].kolumny)
				maximum = tymczasowe_zmienne[i].kolumny;
	
	rob.kolumny = maximum;
	rob.dane = new zespolone[rob.kolumny];
	tymczas = Dzialanie;
	for (int m = 0; m < maximum; m++)
	{
		Dzialanie = tymczas;
	//Wpisanie zmiennych
		for (int i = 0; i < Dzialanie.size(); i++)
		{
			for (int t = 0; t<tymczasowe_zmienne.size(); t++)
			{

				if (tymczasowe_zmienne[t].nazwa == Dzialanie[i])
				{
					if (m > tymczasowe_zmienne[t].kolumny)
						Dzialanie[i] = to_string(tymczasowe_zmienne[t].dane[0].Re);
					else
						Dzialanie[i] = to_string(tymczasowe_zmienne[t].dane[m].Re);
				}
			}
		}


		/////////////////////////////////////////////////
		float tmp_liczba = 0;
		for (int i = 0; i < sizeof(specjalne_znaki) / sizeof(string); i++)
		{
			for (int j = Dzialanie.size() - 1; j >= 0; j--)
			{
				if (Dzialanie[j] == specjalne_znaki[i])
				{
					if (i >= 0 && i <= 8)
					{
						for (int k = j; k < Dzialanie.size(); k++)
						if (Dzialanie[k] == ")")
						{
							podstawowe_operacje(j + 2, k);

							if (Dzialanie[j] != "(")
							{
								tmp_liczba = stof(Dzialanie[j + 2]);
								Dzialanie[j] = to_string(trygonometria(specjalne_znaki[i], tmp_liczba));
								Dzialanie.erase(Dzialanie.begin() + j + 1);
								Dzialanie.erase(Dzialanie.begin() + j + 2);
								Dzialanie.erase(Dzialanie.begin() + j + 1);
							}
							else
							{
								Dzialanie.erase(Dzialanie.begin() + j);
								Dzialanie.erase(Dzialanie.begin() + j + 1);
							}

							j = Dzialanie.size() - 1;
						}
					}
					else
					{
						podstawowe_operacje(j - 1, Dzialanie.size() - 1);
						j = Dzialanie.size() - 1;
					}
				}
			}
		}

		///////////////////////////////////////////////////////
		rob.wiersze = 1;
		rob.dane[m].Re= stof(Dzialanie[0]);
		rob.dane[m].Im = 0;
	}

	return rob;
}

void Obliczenia::podstawowe_operacje(int pocz,int kon)
{
	char dzial[] = { '^', '*', '/', '+', '-' };

	float tym = 0;
	string a;
	for (int i = 0; i <sizeof(dzial) / sizeof(char); i++)
	{
		for (int j = pocz; j <kon; j++)
		{
			a = dzial[i];
			if (Dzialanie[j] == a)
			{
				if (i == 0)
				{
					tym = pow(stof(Dzialanie[j - 1]), stof(Dzialanie[j + 1]));
					Dzialanie.erase(Dzialanie.begin() + j + 1);
					Dzialanie.erase(Dzialanie.begin() + j - 1);
					Dzialanie[j - 1] = to_string(tym);
					j = j - 1;
					kon = kon - 2;
				}

				if (i == 1)
				{
					tym = stof(Dzialanie[j - 1])*stof(Dzialanie[j + 1]);
					Dzialanie.erase(Dzialanie.begin() + j + 1);
					Dzialanie.erase(Dzialanie.begin() + j - 1);
					Dzialanie[j - 1] = to_string(tym);
					j = j-1;
					kon = kon - 2;
				}

				if (i == 2)
				{
					tym = stof(Dzialanie[j - 1]) / stof(Dzialanie[j + 1]);
					Dzialanie.erase(Dzialanie.begin() + j + 1);
					Dzialanie.erase(Dzialanie.begin() + j - 1);
					Dzialanie[j - 1] = to_string(tym);
					j = j - 1;
					kon = kon - 2;
				}

				if (i == 3)
				{
					tym = stof(Dzialanie[j - 1]) + stof(Dzialanie[j + 1]);
					Dzialanie.erase(Dzialanie.begin() + j + 1);
					Dzialanie.erase(Dzialanie.begin() + j - 1);
					Dzialanie[j - 1] = to_string(tym);
					j = j - 1;
					kon = kon - 2;
					
				}

				if (i == 4)
				{
					tym = stof(Dzialanie[j - 1]) - stof(Dzialanie[j + 1]);
					Dzialanie.erase(Dzialanie.begin() + j + 1);
					Dzialanie.erase(Dzialanie.begin() + j - 1);
					Dzialanie[j - 1] = to_string(tym);
					j = j - 1;
					kon = kon - 2;
				}
			}
		}
	}
}

float Obliczenia::trygonometria(string d, float liczba)
{
	if (d == "sin")
		return sin(liczba);

	if (d == "cos")
		return cos(liczba);

	if (d == "tg")
		return tan(liczba);

	if (d == "ctg")
		return pow(tan(liczba), -1);

	if (d == "pierw")
		return sqrt(liczba);
	
	if (d == "abs")
		return abs(liczba);

	if (d == "exp")
		return exp(liczba);

}
