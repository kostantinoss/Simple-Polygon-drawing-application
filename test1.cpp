#include <iostream>

#include <GL/glut.h>
#include <cstdlib>
using namespace std;

int trigger = 0;
GLint pointx,pointy;

void init()
{
	glClearColor(1.0,1.0, 1.0, 0.0);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(100.0);

	if(trigger == 1)
	{
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2i(pointx,300-pointy);
			glVertex2i(300,200);
		glEnd();
	}

	glFlush();


}
void mouse_button(int button, int state, int x, int y) {
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		trigger = 1; 
		pointx = x;
		pointy = y;
		display();
	}
	
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("test");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse_button);
	glutMainLoop();

	return 0;
}