#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <iterator>
#include "triangulate.h"
#include "functions.h"

using namespace std;

vector < vector <Point> > points(MAXNUMPOLYGONS);
vector < vector <Point> > triangles(MAXNUMPOLYGONS);
vector < Color > color(MAXNUMPOLYGONS);

Point p;        //dhmiourgei to shmeio poya tha mpei ston pinaka.Me kathe neo shmeio
                //enhmervnontai to x kai y kai to kanoyme push_back sth lista

int mode3D = FALSE;
int maxDepth ;
int currentPolygon = 0 ;
int polygonComplete = FALSE;
int polygonErased = FALSE;
int polygonMode = FALSE ;
int sum = 0 ;
int down = FALSE;
int rightMouse = FALSE;
int show = TRUE;
int clippingMode = FALSE ;
int x1, y2; 
int y1, x2;

float rotate_y = 300.0;
float rotate_x = 250.0;


void draw3D();
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);          //na dokimasoyme na ta baloume sti Display
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
}

void processMainMenu(int option) {}

void processActionMenu(int option)          //Anagnwrizei an exw exit h polygon
{
    switch(option)
    {
        case 0:                             //polygon mode
            polygonMode = TRUE;
            break;
        case 1:                             //clipping Polygons
            clippingMode = TRUE;
            break;
        case 2:
            do
            {
                std::cout << "Give maximum depth value(110-600) :" << '\n';
                std::cout << "::" ;
                std::cin >> maxDepth ;
            }while(maxDepth < 110 || maxDepth > 600);
            mode3D = TRUE;
            //draw3D();
            break;
        case 3:                             //exit
            exit(0);
    }
}

void processFillMenu(int option)
{
    switch (option) {
        case 0:
            color[currentPolygon].redf = 1.0; color[currentPolygon].greenf = 0.0; color[currentPolygon].bluef = 0.0;
            break ;
        case 1:
            color[currentPolygon].redf = 0.0; color[currentPolygon].greenf = 1.0; color[currentPolygon].bluef = 0.0;
            break ;
        case 2:
            color[currentPolygon].redf = 0.0; color[currentPolygon].greenf = 0.0; color[currentPolygon].bluef = 1.0;
            break ;
        case 3:
            color[currentPolygon].redf = 0.9; color[currentPolygon].greenf = 1.0; color[currentPolygon].bluef = 0.0;
            break ;
        case 4:
            color[currentPolygon].redf = 0.3; color[currentPolygon].greenf = 0.1; color[currentPolygon].bluef = 0.0;
            break ;
        case 5:
            color[currentPolygon].redf = 1.0; color[currentPolygon].greenf = 0.5; color[currentPolygon].bluef = 0.0;
            break ;
        case 6:
            color[currentPolygon].redf = 1.0; color[currentPolygon].greenf = 0.5; color[currentPolygon].bluef = 0.7;
            break ;
        case 7:
            color[currentPolygon].redf = 1.0; color[currentPolygon].greenf = 0.0; color[currentPolygon].bluef = 0.9;
            break ;
        case 8:
            color[currentPolygon].redf = 0.0; color[currentPolygon].greenf = 0.7; color[currentPolygon].bluef = 1.0;
            break ;
        case 9:
            color[currentPolygon].redf = 0.3; color[currentPolygon].greenf = 0.9; color[currentPolygon].bluef = 0.0;
            break ;
        case 10:
            color[currentPolygon].redf = 0.3; color[currentPolygon].greenf = 1.0; color[currentPolygon].bluef = 1.0;
            break ;
        case 11:
            color[currentPolygon].redf = 0.0; color[currentPolygon].greenf = 0.0; color[currentPolygon].bluef = 0.0;
            break ;
        case 12:
            color[currentPolygon].redf = 0.5; color[currentPolygon].greenf = 0.5; color[currentPolygon].bluef = 0.5;
            break ;
        case 13:
            color[currentPolygon].redf = 1.0; color[currentPolygon].greenf = 1.0; color[currentPolygon].bluef = 1.0;
            break ;
        case 14:
            color[currentPolygon].redf = 0.2; color[currentPolygon].greenf = 0.0; color[currentPolygon].bluef = 0.4;
            break ;
        case 15:
            color[currentPolygon].redf = 1.0; color[currentPolygon].greenf = 0.8; color[currentPolygon].bluef = 1.0;
            break ;
    }
}

void processLineMenu(int option)
{
    switch (option) {
        case 0:
            color[currentPolygon].redl = 1.0; color[currentPolygon].greenl = 0.0; color[currentPolygon].bluel = 0.0;
            break ;
        case 1:
            color[currentPolygon].redl = 0.0; color[currentPolygon].greenl = 1.0; color[currentPolygon].bluel = 0.0;
            break ;
        case 2:
            color[currentPolygon].redl = 0.0; color[currentPolygon].greenl = 0.0; color[currentPolygon].bluel = 1.0;
            break ;
        case 3:
            color[currentPolygon].redl = 0.9; color[currentPolygon].greenl = 1.0; color[currentPolygon].bluel = 0.0;
            break ;
        case 4:
            color[currentPolygon].redl = 0.3; color[currentPolygon].greenl = 0.1; color[currentPolygon].bluel = 0.0;
            break ;
        case 5:
            color[currentPolygon].redl = 1.0; color[currentPolygon].greenl = 0.5; color[currentPolygon].bluel = 0.0;
            break ;
        case 6:
            color[currentPolygon].redl = 1.0; color[currentPolygon].greenl = 0.5; color[currentPolygon].bluel = 0.7;
            break ;
        case 7:
            color[currentPolygon].redl = 1.0; color[currentPolygon].greenl = 0.0; color[currentPolygon].bluel = 0.9;
            break ;
        case 8:
            color[currentPolygon].redl = 0.0; color[currentPolygon].greenl = 0.7; color[currentPolygon].bluel = 1.0;
            break ;
        case 9:
            color[currentPolygon].redl = 0.3; color[currentPolygon].greenl = 0.9; color[currentPolygon].bluel = 0.0;
            break ;
        case 10:
            color[currentPolygon].redl = 0.3; color[currentPolygon].greenl = 1.0; color[currentPolygon].bluel = 1.0;
            break ;
        case 11:
            color[currentPolygon].redl = 0.0; color[currentPolygon].greenl = 0.0; color[currentPolygon].bluel = 0.0;
            break ;
        case 12:
            color[currentPolygon].redl = 0.5; color[currentPolygon].greenl = 0.5; color[currentPolygon].bluel = 0.5;
            break ;
        case 13:
            color[currentPolygon].redl = 1.0; color[currentPolygon].greenl = 1.0; color[currentPolygon].bluel = 1.0;
            break ;
        case 14:
            color[currentPolygon].redl = 0.2; color[currentPolygon].greenl = 0.0; color[currentPolygon].bluel = 0.4;
            break ;
        case 15:
            color[currentPolygon].redl = 1.0; color[currentPolygon].greenl = 0.8; color[currentPolygon].bluel = 1.0;
            break ;
    }
}

void createGLUTMenus()
{
    int actionMenu, mainMenu, lineColorMenu, fillColorMenu;

    actionMenu = glutCreateMenu(processActionMenu);
    glutAddMenuEntry("Polygon", 0);
    glutAddMenuEntry("Clip Polygons", 1);
    glutAddMenuEntry("Extrude", 2);
    glutAddMenuEntry("Exit", 3);

    lineColorMenu = glutCreateMenu(processLineMenu);
    glutAddMenuEntry("red", 0);
    glutAddMenuEntry("green", 1);
    glutAddMenuEntry("blue", 2);
    glutAddMenuEntry("yellow", 3);
    glutAddMenuEntry("brown", 4);
    glutAddMenuEntry("orange", 5);
    glutAddMenuEntry("pink" ,6);
    glutAddMenuEntry("purlpe" ,7);
    glutAddMenuEntry("cyan", 8);
    glutAddMenuEntry("lime", 9);
    glutAddMenuEntry("turquoise", 10);
    glutAddMenuEntry("black", 11);
    glutAddMenuEntry("grey", 12);
    glutAddMenuEntry("white", 13);
    glutAddMenuEntry("navy", 14);
    glutAddMenuEntry("light pink", 15);

    fillColorMenu = glutCreateMenu(processFillMenu);
    glutAddMenuEntry("red", 0);
    glutAddMenuEntry("green", 1);
    glutAddMenuEntry("blue", 2);
    glutAddMenuEntry("yellow", 3);
    glutAddMenuEntry("brown", 4);
    glutAddMenuEntry("orange", 5);
    glutAddMenuEntry("pink" ,6);
    glutAddMenuEntry("purlpe" ,7);
    glutAddMenuEntry("cyan", 8);
    glutAddMenuEntry("lime", 9);
    glutAddMenuEntry("turquoise", 10);
    glutAddMenuEntry("black", 11);
    glutAddMenuEntry("grey", 12);
    glutAddMenuEntry("white", 13);
    glutAddMenuEntry("navy", 14);
    glutAddMenuEntry("light pink", 15);

    mainMenu = glutCreateMenu(processMainMenu);
    glutAddSubMenu("ACTION", actionMenu);
    glutAddSubMenu("LINE_COLOR", lineColorMenu);
    glutAddSubMenu("FILL_COLOR", fillColorMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void convertAndTriangulate(int index)
{
    std::vector< Vector2d > input;
    std::vector< Vector2d> result;

    int j;
    for(j = 0; j < points[index].size(); j++)
    {
        input.push_back( Vector2d(points[index][j].x, points[index][j].y));
    }

    Triangulate::Process(input, result);

    for(j = 0; j < result.size(); j++)
    {
        Point p;
        Vector2d v = result[j];
        p.x = (int)v.GetX();
        p.y = (int)v.GetY();
        triangles[index].push_back(p);
    }
}
int IfIntersect()
{
    int out = FALSE;

    if(points[currentPolygon].size() >= 3)
    {
        int last = points[currentPolygon].size() - 1;
        int j;
        for(j = last; j >= 2; j--)
        {
            out = doIntersect(points[currentPolygon][last], p, points[currentPolygon][j - 1], points[currentPolygon][j - 2]);

            if(out == TRUE)
            {
                points[currentPolygon].erase(points[currentPolygon].begin(), points[currentPolygon].end());

                glClear(GL_COLOR_BUFFER_BIT);
                polygonErased = TRUE;
                polygonMode = FALSE;
                polygonComplete = FALSE;
                rightMouse = FALSE;

                return TRUE;
            }
        }
    }

    return FALSE;
}

int IfIntersectInRightClick()
{
    int out = FALSE;
    int j;
    for(j = 1; j <= points[currentPolygon].size() - 3; j++)
    {
        out = doIntersect(points[currentPolygon][0] ,points[currentPolygon][points[currentPolygon].size() - 1], points[currentPolygon][j], points[currentPolygon][j + 1]);
        if(out == TRUE)
        {
            points[currentPolygon].erase(points[currentPolygon].begin(), points[currentPolygon].end());
            glClear(GL_COLOR_BUFFER_BIT);
            polygonErased = TRUE;
            polygonMode = FALSE;
            polygonComplete = FALSE;
            rightMouse = FALSE;
            return TRUE;
        }
    }

    return FALSE;
}

void drawPolygons()
{
    glLineWidth(2.0);
    int i ,j, tcount;
    for(i = 0; i < currentPolygon; i++)
    {
        glColor3f(color[i].redl, color[i].greenl, color[i].bluel);
        glBegin(GL_LINE_LOOP);
            for (j = 0; j < points[i].size(); j++)
            {
                glVertex2i(points[i][j].x, points[i][j].y);
            }
        glEnd();

        //fill polygons using the triangles.
        tcount = triangles[i].size()/3;
        for (j = 0; j < tcount; j++)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glColor3f(color[i].redf, color[i].greenf, color[i].bluef);
            glBegin(GL_TRIANGLES);
                glVertex2i(triangles[i][j*3+0].x, triangles[i][j*3+0].y);
                glVertex2i(triangles[i][j*3+1].x, triangles[i][j*3+1].y);
                glVertex2i(triangles[i][j*3+2].x, triangles[i][j*3+2].y);
            glEnd();
        }
    }
}
void drawCurrentPolygon()
{
    glColor3f(color[currentPolygon].redl, color[currentPolygon].greenl, color[currentPolygon].bluel);
    glLineWidth(2.0);
    glPointSize(3.0);
    int i,j;

    if(polygonMode == TRUE && polygonComplete == FALSE)                              //Ayto thn Prwth fora den isxuei
    {
        glutDetachMenu(GLUT_RIGHT_BUTTON);
        for(j = 0 ;j < points[currentPolygon].size();j++)
        {
            glBegin(GL_POINTS);
                glVertex2i(points[currentPolygon][j].x, points[currentPolygon][j].y);
            glEnd();
        }

        glBegin(GL_LINE_STRIP);
            for(j=0 ;j<points[currentPolygon].size();j++)
            {
                glVertex2i(points[currentPolygon][j].x, points[currentPolygon][j].y);
            }
        glEnd();

        glFlush();
    }

    if((rightMouse == TRUE) && (polygonComplete == FALSE) && ( sum >= MINNUMBEROFVERTICES ))             // An paththei to deksi klik enwse thn prwth me thn teleytaia
    {
        if(IfIntersectInRightClick() == FALSE)
        {
            glBegin(GL_LINE);
                glVertex2i(points[currentPolygon].front().x, points[currentPolygon].front().y);
                glVertex2i(points[currentPolygon].back().x, points[currentPolygon].back().y);
            glEnd();

            convertAndTriangulate(currentPolygon);

            polygonComplete = TRUE;
            polygonMode = FALSE;
            currentPolygon ++;
            sum = 0 ;
        }
    }

    if (polygonComplete == TRUE || polygonErased == TRUE)
    {
        createGLUTMenus();
        polygonErased = FALSE;
    }

    if((rightMouse == TRUE) &&  ( sum <= 5 ))
    {
          rightMouse = FALSE ;
    }

    polygonComplete = FALSE;
    rightMouse = FALSE;

    glFlush();
}

void drawTriangles()
{
    int i,j;
    int tcount ;

    glLineWidth(2.0);

    for(i = 0; i <= currentPolygon; i++)
    {
        tcount = triangles[i].size()/3;
        for (j = 0; j < tcount; j++)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_TRIANGLES);
                glVertex2i(triangles[i][j*3+0].x, triangles[i][j*3+0].y);
                glVertex2i(triangles[i][j*3+1].x, triangles[i][j*3+1].y);
                glVertex2i(triangles[i][j*3+2].x, triangles[i][j*3+2].y);
            glEnd();
        }
        glFlush();
    }
}

void clippingPolygons(vector < Point > clippingWindow)
{
    int i;

    for(i = 0; i < currentPolygon; i++)
    {
        if(points[i].size() == 0)
        {
            continue;
        }
        clip(points[i], clippingWindow);
        std::cout << "size,"<<points[i].size()<<"| i--> " <<i<< '\n';
        for(int j = 0; j < points[i].size(); j++)
        {
            cout << "x,y: " << points[i][j].x << "," << points[i][j].y <<'\n';
        }
    }
}

void initTriangles()
{
    for(int i = 0; i < triangles.size(); i++)
    {
        triangles[i].clear();
    }
    for(int i = 0; i < points.size(); i++)
    {
        convertAndTriangulate(i);
    }
}

void mouseHandler(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && polygonMode == TRUE)
    {
        p.x = x;
        p.y = HEIGHT - y;

        if(IfIntersect() == FALSE)
        {
            sum ++;
            points[currentPolygon].push_back(p);

        }
        drawCurrentPolygon();
        drawPolygons();
    }
    else if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
    {
        rightMouse = TRUE;
        drawCurrentPolygon();
        drawPolygons();
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clippingMode == TRUE)
    {
        x1 = x;     //pano aristera shmeio toy parathyroy apokopis
        y2 = HEIGHT - y;

        down = TRUE;
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && clippingMode == TRUE && down == TRUE)
    {
        x2 = x;     //katv dexia shmeio toy parathyroy apokopis
        y1 = HEIGHT - y;

        normalization(&x1,&y2,&x2,&y1);

        vector <Point> clippingWindow;
        Point p1,p2,p3,p4;

        p1.x = x1; p1.y = y1;
        p2.x = x1; p2.y = y2;
        p3.x = x2; p3.y = y2;
        p4.x = x2; p4.y = y1;

        clippingWindow.push_back(p1);
        clippingWindow.push_back(p2);
        clippingWindow.push_back(p3);
        clippingWindow.push_back(p4);

        clippingPolygons(clippingWindow);

        initTriangles();
        glClear(GL_COLOR_BUFFER_BIT);
        drawPolygons();
        glFlush();

        clippingMode = FALSE;
        down = FALSE;
    }
}

void mouseMove(int x, int y)
{
    if(clippingMode == TRUE)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        drawPolygons();

        glColor3f(0.0, 0.0, 0.0);
        glLineStipple(1, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
            glColor3f(0.0, 1.0, 0.0);
            glVertex2i(x1, HEIGHT - y);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2i(x1, y2);
            glColor3f(0.0, 0.0, 1.0);
            glVertex2i(x, y2);
            glColor3f(1.0, 0.5, 0.0);
            glVertex2i(x, HEIGHT-  y);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        glFlush();
    }
}

void keyboardHandler(unsigned char key, int x, int y) {
    switch (key)
    {
        case 84:
            if(show == TRUE)
            {
                drawTriangles();
                show = FALSE;
            }
            else
            {
                glClear(GL_COLOR_BUFFER_BIT);
                drawPolygons();
                glFlush();
                show = TRUE;
            }
            break;
    }
}

void display()
{
    if(mode3D == TRUE)
    {
        draw3D();
    }
   	glFlush ();
}

void draw3D()
{
	if(mode3D == TRUE)
    {
        glClearDepth(1.0f);                   // Set background depth to farthest
        glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
        glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
        glShadeModel(GL_SMOOTH);   // Enable smooth shading
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity ();
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
       	
       	//glOrtho(0.0, 600.0, 0.0, 500.0, -1000.0, 1000.0);
        gluPerspective(80.0, 1.0*(WIDTH/HEIGHT), 1.0, 1000);
        
        gluLookAt(rotate_x*cos(80.0),rotate_y*sin(80),0.0, 300.0, 250.0, 1.0, 0.0,1.0,0.0);
        //glRotatef( rotate_x, 1.0, 250.0, 0.0 );
        //glRotatef( rotate_y, 300.0, 1.0, 0.0);


        glLineWidth(2.0);
        int i ,j, tcount;
        for(i = 0; i < currentPolygon; i++)
        {
            tcount = triangles[i].size()/3;
            glColor3f(color[i].redf, color[i].greenf, color[i].bluef);
            for (j = 0; j < tcount; j++)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glBegin(GL_TRIANGLES);
                    glVertex3f((float)triangles[i][j*3+0].x, (float)triangles[i][j*3+0].y,-maxDepth);
                    glVertex3f((float)triangles[i][j*3+1].x, (float)triangles[i][j*3+1].y,-maxDepth);
                    glVertex3f((float)triangles[i][j*3+2].x, (float)triangles[i][j*3+2].y,-maxDepth);
                glEnd();
            }
            tcount = triangles[i].size()/3;
            for (j = 0; j < tcount; j++)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glBegin(GL_TRIANGLES);
                    glVertex3f((float)triangles[i][j*3+0].x, (float)triangles[i][j*3+0].y,MINDEPTH);
                    glVertex3f((float)triangles[i][j*3+1].x, (float)triangles[i][j*3+1].y,MINDEPTH);
                    glVertex3f((float)triangles[i][j*3+2].x, (float)triangles[i][j*3+2].y,MINDEPTH);
                glEnd();
            }


            for (j = 0; j < points[i].size(); j++)
            {
                glColor3f(color[i].redl, color[i].greenl, color[i].bluel);
                glBegin(GL_LINES);
                    glVertex3f((float)points[i][j].x, (float)points[i][j].y, MINDEPTH);
                    glVertex3f((float)points[i][j].x, (float)points[i][j].y, - maxDepth);
                glEnd();
            }
            for (j = 0; j < points[i].size(); j++)
            {
                glColor3f(color[i].redl, color[i].greenl, color[i].bluel);
                // enonei ta dyo polygona
                glBegin(GL_QUADS);
                glVertex3f((float)points[i][j].x, (float)points[i][j].y, MINDEPTH);
                glVertex3f((float)points[i][j].x, (float)points[i][j].y, - maxDepth);
                glVertex3f((float)points[i][(j+1)%(points[i].size())].x, (float)points[i][(j+1)%(points[i].size())].y, - maxDepth);
                glVertex3f((float)points[i][(j+1)%(points[i].size())].x, (float)points[i][(j+1)%(points[i].size())].y, MINDEPTH);
                glEnd();
            }

            glColor3f(color[i].redl, color[i].greenl, color[i].bluel);
            glBegin(GL_LINE_LOOP);
                for (j = 0; j < points[i].size(); j++)
                {
                    glVertex3f((float)points[i][j].x, (float)points[i][j].y ,MINDEPTH);
                }
            glEnd();

            glColor3f(color[i].redl, color[i].greenl, color[i].bluel);
            glBegin(GL_LINE_LOOP);
                for (j = 0; j < points[i].size(); j++)
                {
                    glVertex3f((float)points[i][j].x, (float)points[i][j].y, - maxDepth);
                }
            glEnd();
        }
    }
}

void specialKeys( int key, int x, int y ) {

  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotate_x -= 2.5;

  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_x += 2.5;

  else if (key == GLUT_KEY_UP)
    rotate_y += 2.5;

  else if (key == GLUT_KEY_DOWN)
    rotate_y -= 2.5;

  //  Request display update
  glutPostRedisplay();

}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(40, 100);
    glutInitWindowSize(600, 500);
    glutCreateWindow("project 1");
    init();
    glClear(GL_COLOR_BUFFER_BIT);
    //glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(specialKeys);
    createGLUTMenus();

    glutMainLoop();

    return 0;
}
