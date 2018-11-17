#include <GL/glut.h>
#include <iostream> 
#include <list> 
#include <iterator> 
using namespace std; 
//ntinaras

void draw();
void MenuEvents(int options);
void mouse_button(int button, int state, int x, int y)
int trig = 0;

void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

}

void createGLUTMenus() {

	int menu;

	menu = glutCreateMenu(MenuEvents);

	glutAddMenuEntry("fullscreen",0);
	glutAddMenuEntry("exit fullscreen",2);
	glutAddMenuEntry("Exit",1);
	glutAddMenuEntry("draw shapes",3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
   	glLoadIdentity(); 
	glColor3f(1.0, 0.0, 0.0);

	if(trig == 1)
	{
		glBegin(GL_LINES);            // These vertices form a closed polygon
	      	glColor3f(1.0f, 0.0f, 0.0f); // Yellow
	      	glVertex2f(1.0f, 0.0f);
	      	glVertex2f(-0.4f, 0.0f);
	   	glEnd();

	   	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
	      glColor3f(1.0f, 0.0f, 0.0f); // Red
	      glVertex2f(-0.8f, 0.1f);     // Define vertices in counter-clockwise (CCW) order
	      glVertex2f(-0.2f, 0.1f);     //  so that the normal (front-face) is facing you
	      glVertex2f(-0.2f, 0.7f);
	      glVertex2f(-0.8f, 0.7f);
	 
	      glColor3f(0.0f, 1.0f, 0.0f); // Green
	      glVertex2f(-0.7f, -0.6f);
	      glVertex2f(-0.1f, -0.6f);
	      glVertex2f(-0.1f,  0.0f);
	      glVertex2f(-0.7f,  0.0f);
	 
	      glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
	      glVertex2f(-0.9f, -0.7f);
	      glColor3f(1.0f, 1.0f, 1.0f); // White
	      glVertex2f(-0.5f, -0.7f);
	      glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
	      glVertex2f(-0.5f, -0.3f);
	      glColor3f(1.0f, 1.0f, 1.0f); // White
	      glVertex2f(-0.9f, -0.3f);
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
	}
}

void MenuEvents(int options)
{
	switch(options)
	{
		case 0:
			glutFullScreen();
			break;
		case 1:
			exit(0);
		case 2:
			glutReshapeWindow(400, 300);
		case 3:
			trig = 1;

	}
}

int main(int argc, char *argv[])
{
	list <int> points;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("project 1");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse); 
	createGLUTMenus();
	glutMainLoop();

	return 0;
}
