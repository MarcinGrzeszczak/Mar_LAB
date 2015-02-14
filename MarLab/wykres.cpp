#include "Lib\glew\glew.h"
#include "Lib\glut\freeglut.h"
#include "wykres.h"

zmienna punkt1_x, punkt1_y;
void Wykres::pobierz_punkty()
{
	punkt1_x = this->punkt_x;
	punkt1_y = this->punkt_y;
}

int gora = 0;
int dol = 0;
int lewo = 0;
int prawo = 0;

void Napisz(int x, int y, string tekst)
{
	int dlugosc = tekst.length();
	glRasterPos2f(x, y);
	for (int i = 0; i < dlugosc; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, tekst[i]);
}

void wykres_rodzaj()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINES);

	glVertex2i(0, 0);
	glVertex2i(0, gora);

	glVertex2i(0, 0);
	glVertex2i(0, dol);

	glVertex2i(0, 0);
	glVertex2i(prawo, 0);

	glVertex2i(0, 0);
	glVertex2i(lewo, 0);


	glEnd();

	int przedzialka = 1;
	
	if (przedzialka > 50)
		przedzialka *= 2;

	if (przedzialka > 300)
		przedzialka *= 32;

	if (przedzialka > 1000)
		przedzialka *= 32;

	if (przedzialka < 2000)
	{
		for (int i = 0; i < punkt1_x.kolumny; i += 2)
		{

			if ((punkt1_x.dane[i].Re - (int)punkt1_x.dane[i].Re) == 0)
				Napisz(punkt1_x.dane[i].Re, -2, to_string((int)punkt1_x.dane[i].Re));
			else
				Napisz(punkt1_x.dane[i].Re, -2, to_string(punkt1_x.dane[i].Re));
		}

		for (int i = dol; i < gora; i += 2)
		{
			if ((punkt1_y.dane[i].Re - (int)punkt1_y.dane[i].Re) == 0)
				Napisz(0, punkt1_y.dane[i].Re, to_string((int)punkt1_y.dane[i].Re));
			else
				Napisz(0, punkt1_y.dane[i].Re, to_string(punkt1_y.dane[i].Re));
		}
	}
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	
	for (int i = 0; i < punkt1_x.kolumny; i++)		
		glVertex2i(punkt1_x.dane[i].Re, punkt1_y.dane[i].Re);
	
	glEnd();

	glLineWidth(1.0);
	glBegin(GL_LINES);
	for (int i = 0; i < punkt1_x.kolumny; i++)
		if (i+1 < punkt1_x.kolumny)
		{
			glVertex2i(punkt1_x.dane[i].Re, punkt1_y.dane[i].Re);
			glVertex2i(punkt1_x.dane[i + 1].Re, punkt1_y.dane[i + 1].Re);
		}
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	for (int i = 0; i < punkt1_x.kolumny; i++)
	{
		if (gora < punkt1_y.dane[i].Re)
			gora = punkt1_y.dane[i].Re;
		
		if (dol > punkt1_y.dane[i].Re)
			dol = punkt1_y.dane[i].Re;

		if (prawo < punkt1_x.dane[i].Re)
			prawo = punkt1_x.dane[i].Re;
		
		if (lewo > punkt1_x.dane[i].Re)
			lewo = punkt1_x.dane[i].Re;
	}
	gluOrtho2D(lewo-2,prawo+5, dol-10, gora+10);
	//gluOrtho2D(0, punkt1_y.wielkosc + 1, 0, 80);
	wykres_rodzaj();
}

void Wykres::Tworzenie_okna(int argc, char **argv)
{
	pobierz_punkty();
	
	gora = punkt1_y.dane[0].Re;
	dol = punkt1_y.dane[0].Re;
	lewo = punkt1_x.dane[0].Re;
	prawo = punkt1_x.dane[0].Re;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Wykres 1");
	glutDisplayFunc(wykres_rodzaj);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	
}