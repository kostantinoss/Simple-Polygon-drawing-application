#include <cstdlib>
#include <iostream> 
#include <GL/glut.h>
#include <list> 
#include <iterator> 

using namespace std; 

typedef struct point {
	int x;
	int y;
}Point;


int trigger = 0;
int x,y;
int mouse = 0;
list <Point> points;

void display();
void polygon();

void init() {
	glClearColor(1.0,1.0, 1.0, 0.0);
	gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}

void processMainMenu(int option) {}

void processActionMenu(int option) {
	switch(option) {
		case 0:			//polygon mode
			polygon();
			break;
		case 1:			//exit
			list <Point> :: iterator it; 
			for(it = points.begin(); it != points.end(); ++it) {
	    		cout << "x, y :" << it->x << ", " << it->y << "\n" ;
	    	}
			exit(-1);
	}
}

void createGLUTMenus() {

	int actionMenu;
	actionMenu = glutCreateMenu(processActionMenu);
	glutAddMenuEntry("Polygon", 0);
	glutAddMenuEntry("Exit", 1);

	int mainMenu;
	mainMenu = glutCreateMenu(processMainMenu);
	glutAddSubMenu("ACTION", actionMenu);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// this will allow us to know if the menu is active
	//glutMenuStatusFunc(processMenuStatus);
}

void mouse_button(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		x = x;
		y = 500 - y;
		mouse = 1;
	}

	//trigger = 0;
}

void polygon() {

	if( mouse == 1)
	{

		cout << "in\n";
		Point p;
		p.x = x;
		p.y = y;

		points.push_back(p);
		
		//list <Point> :: iterator it; 
	    //for(it = points.begin(); it != points.end(); ++it) {
	   	glBegin(GL_LINES);
			glVertex2i(p.x, p.y);
			glVertex2i(0,0);
		glEnd();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(100.0);
	
	glFlush();
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 500);
	glutCreateWindow("project 1");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse_button);
	createGLUTMenus();
	glutMainLoop();
}