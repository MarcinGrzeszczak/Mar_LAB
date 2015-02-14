#include "Macierz.h"

zmienna Macierz::Oblicz(string komenda)
{
	zmienna wynik;
	float *tab=new float[3];
	bool wek =false;
	string tmp= "";
	wynik.wiersze = 1;
	wynik.komenda = komenda;
	for (int i = 1, j = 1; i < komenda.length()-1; i++)
	{
		if (komenda[i] == ' ')
		{
			wek = true;
			break;
		}
		if (komenda[i] == ',' || komenda[i] == ';')
			break;
	}

	if (wek)
	{
			for (int i = 1, j = 1,k=0; i < komenda.length(); i++)
			{
				if (komenda[i] == ' ' || i == komenda.length()-2)
				{
					for (; j < i+1; j++)
						tmp += komenda[j];
					j = i+1;
					tab[k++] = stof(tmp);
					tmp = "";
					
				}
			}
		
		wynik.kolumny = 0;
		for (float i = tab[0]; i <= tab[2]; i += tab[1])
			wynik.kolumny += 1;
		wynik.dane = new zespolone[wynik.kolumny];
		
		int y = 0;
		for (float i = tab[0]; i <= tab[2]; i += tab[1],y++)
		{
			wynik.dane[y].Re = i;
			wynik.dane[y].Im = 0;
		}
		return wynik;
	}

	else
	{
		wynik.kolumny = 0;
		wynik.wiersze = 0;
		
		for (int i = 1; i < komenda.length() - 1; i++)
		{
			if (komenda[i] == ',')
				wynik.kolumny++;
			if (komenda[i] == ';')
				break;
		}
		for (int i = 1; i < komenda.length() - 1; i++)
		{
			if (komenda[i] == ';')
				wynik.wiersze++;
		}
		wynik.dane = new zespolone[(++wynik.kolumny)*(++wynik.wiersze)];

		for (int i = 1,j=1,k=0; i < komenda.length();i++)
			if (komenda[i] == ',' || komenda[i] == ';' || komenda[i] == ']')
			{
				for (; j < i; j++)
					tmp += komenda[j];
				j = i+1;
				wynik.dane[k].Im = 0;
				wynik.dane[k++].Re = stof(tmp);
				
				tmp = "";
			}
			return wynik;
	}
}