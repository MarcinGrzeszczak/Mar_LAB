#include "Macierz.h"

zmienna Macierz::Oblicz(string komenda)
{
	zmienna wynik;
	float *tab=new float[3];
	bool wek =false;
	string tmp= "";
	
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
		
		wynik.wielkosc = 0;
		for (float i = tab[0]; i <= tab[2]; i += tab[1])
			wynik.wielkosc += 1;
		wynik.dane = new zespolone[wynik.wielkosc];
		
		int y = 0;
		for (float i = tab[0]; i <= tab[2]; i += tab[1],y++)
		{
			wynik.dane[y].Re = i;
			wynik.dane[y].Im = 0;
		}
		return wynik;
	}
}