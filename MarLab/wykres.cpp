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

void wykres_rodzaj()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < punkt1_x.wielkosc; i++)
	{
		glPointSize(4.0);
		glBegin(GL_POINTS);
		glVertex2i(punkt1_x.dane[i].Re, punkt1_y.dane[i].Re);
		glEnd();

	}

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(5.0);
	glBegin(GL_LINES);

	glVertex2i(0, 0);
	glVertex2i(0, gora);

	glVertex2i(0, 0);
	glVertex2i(0, dol);

	glVertex2i(0, 0);
	glVertex2i(prawo, 0);

	glEnd();

	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	for (int i = 0; i < punkt1_x.wielkosc; i++)
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