#ifndef struktury_h
#define struktury_h

#include <string>
using namespace std;
struct zespolone
{
	float Re;
	float Im;
};

struct zmienna
{
	string nazwa;
	string komenda;
	int wiersze;
	int kolumny;
	zespolone *dane;
};


#endif