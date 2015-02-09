#include "struktury.h"

#ifndef wykres_h
#define wykres_h
class Wykres
{
private:

public:
	zmienna punkt_x, punkt_y;
	//friend void  Reshape(int width, int height,Wykres &wyk);
	//friend void wykres_rodzaj(Wykres &wyk);
	void Tworzenie_okna(int argc, char **argv);
	void pobierz_punkty();
};
#endif