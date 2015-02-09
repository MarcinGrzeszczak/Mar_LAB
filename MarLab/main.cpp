#include "Interpreter.h"
#include <conio.h>
using namespace std;

int main(int argc, char **argv)
{
	string komenda;
	char znak;
	Interpreter inter;
	cout << "MarLab v. alpha 1.1\n\n";
	while (1)
	{
		cout << "> ";
		getline(cin, komenda);
		inter.parser(komenda,argc,argv);
		komenda = "";
	}
	return 0;
}