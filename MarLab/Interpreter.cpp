#include "Interpreter.h"

Interpreter::Interpreter()
{

}

void Interpreter::parser(string wiersz, int argc, char **argv)
{
	Obl = new Obliczenia(Baza_zmienne);
	string nazwa="";
	string komenda="";
	string tym = "";
	zmienna robocza;
	string dzialania[] = { "^", "*", "/", "+", "-", "sin", "cos","tg","abs","pierw","(" ,")"};
	bool odczyt = true;
	bool obsluga = false;
	
	if (wiersz == "koniec")
		exit(0);

	if (wiersz == "ekran")
	{
		system("cls");
		cout << "MarLab v. alpha 1.1\n\n";
		obsluga = true;
	}

	if (!obsluga)
	{
		int sprawdz_czy_wykres = 0;
		string wykres = "wykres";
		
			for (int d=0,s=0; d < wiersz.length() && s<wykres.length(); d++)
			{
				if (wiersz[d] == wykres[s])
				{
					sprawdz_czy_wykres++;
					s++;
				}
				else
				{	
					sprawdz_czy_wykres = -1;
					break;
				}
			
			if (sprawdz_czy_wykres == -1)
				break;
		}
		if (sprawdz_czy_wykres == 6)
		{
			tym = "";
			tym += wiersz[7];
			rysowanie_wykres.punkt_x = Baza_zmienne.Odczytywanie_zmiennych(tym);
			tym = "";
			tym += wiersz[wiersz.length() - 2];
			rysowanie_wykres.punkt_y = Baza_zmienne.Odczytywanie_zmiennych(tym);
			rysowanie_wykres.Tworzenie_okna(argc, argv);
		}
		else
		{

			for (int i = 0; i < wiersz.length(); i++)
			{
				if (wiersz[i] == '=')
				{
					for (int j = 0; j < i; j++)
						nazwa += wiersz[j];

					for (int j = i + 1; j < wiersz.length(); j++)
					{
						komenda += wiersz[j];
						i = j;
					}
					odczyt = false;
				}
			}
		}

		if (odczyt)
		{			
			Wyswietl(Baza_zmienne.Odczytywanie_zmiennych(wiersz));
		}
		else
		{
			if (Baza_zmienne.czy_liczba(komenda) || Baza_zmienne.czy_zespolona(komenda))
			{

				robocza.wielkosc = 1;
				robocza.dane = new zespolone[robocza.wielkosc];

				if (Baza_zmienne.czy_liczba(komenda))
				{
					robocza.dane[0].Re = stof(komenda);
					robocza.dane[0].Im = 0;
				}

				if (Baza_zmienne.czy_zespolona(komenda))
				{
					string t = "";
					for (int i = 0; i < komenda.length(); i++)
					{
						if (komenda[i] == '+' || komenda[i] == '-')
						{
							for (int j = 0; j < i; j++)
								t += komenda[j];
							robocza.dane[0].Re = stof(t);
							t = "";
							for (int j = i + 1; j < komenda.length(); j++)
							{
								if (komenda[j] != 'i' && komenda[j] != 'j')
									t += komenda[j];
							}
							if (komenda[i] == '-')
								robocza.dane[0].Im = stof(t)*-1;
							else
								robocza.dane[0].Im = stof(t);
							break;
						}
					}
				}

				Baza_zmienne.Dodawanie_zmiennych(nazwa, komenda, robocza.wielkosc, robocza.dane);
			}
			else
			{
			
					for (int i = 0; i < komenda.length(); i++)
					{
						if (komenda[0] == '[')
						{
							robocza = macierz.Oblicz(komenda);
							break;
						}

						///Obliczenia

						for (int j = 0, czy_dzialanie = 0; j < sizeof(dzialania) / sizeof(string); j++)
						{
							for (int k = 0; k < dzialania[j].length(); k++)
							{
								if (komenda[i] == dzialania[j][k])
									czy_dzialanie++;
							}
							if (czy_dzialanie == dzialania[j].length())
							{

								robocza = Obl->Oblicz(komenda);
								i = komenda.length();
								Obl = new Obliczenia(Baza_zmienne);
								break;
							}
						}

					}

					Baza_zmienne.Dodawanie_zmiennych(nazwa, komenda, robocza.wielkosc, robocza.dane);
				}
		}
	}
}

void Interpreter::Wyswietl(zmienna odczyt)
{
	if (odczyt.nazwa != "!@#$%^&*()")
	for (int i = 0; i < odczyt.wielkosc; i++)
	{
		cout <<"\t"<<to_string(odczyt.dane[i].Re);
		if (odczyt.dane[i].Im != 0)
		{
			if (odczyt.dane[i].Im > 0)
				cout << " + " << to_string(odczyt.dane[i].Im)<<"i";
			if (odczyt.dane[i].Im < 0)
				cout << " - " << to_string(odczyt.dane[i].Im*-1) << "i";
		}
		cout << endl;
	}
	else
		cout << "\tBLAD"<<endl;
}

