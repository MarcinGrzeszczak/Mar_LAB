#include "Lib\glew\glew.h"
#include "Lib\glut\freeglut.h"
#include "wykres.h"

zmienna punkt1_x, punkt1_y;
void Wykres::pobierz_punkty()
{
	punkt1_x = this->punkt_x;
	punkt1_y = this->punkt_y;
}

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
	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int wysokosc = height;
	for (int i = 0; i < punkt1_x.wielkosc; i++)
	for (int j = 0; j < punkt1_y.wielkosc; j++)
	if (punkt1_y.dane[i].Re > punkt1_y.dane[j].Re)
		wysokosc = i;
	gluOrtho2D(-1, 365, -200, 200);
	//gluOrtho2D(0, punkt1_y.wielkosc + 1, 0, 80);
	wykres_rodzaj();
}

void Wykres::Tworzenie_okna(int argc, char **argv)
{
	pobierz_punkty();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Wykres 1");
	glutDisplayFunc(wykres_rodzaj);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	
}