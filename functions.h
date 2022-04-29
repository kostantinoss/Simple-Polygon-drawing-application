#include <vector>
#include <GL/glut.h>

using namespace std;

#define WIDTH 600.0
#define HEIGHT 500.0
#define TRUE 1
#define FALSE 0
#define MAXNUMPOLYGONS 100
#define MINDEPTH -100
#define MINNUMBEROFVERTICES 3 

class Point {
    public: int x ,y;
};

class Color {
    public:
    float redl = 0.0;
    float redf = 1.0;
    float greenl = 0.0;
    float greenf = 1.0;
    float bluel = 0.0;
    float bluef = 1.0;
};


void normalization(int *x1, int *y2, int *x2, int *y1) ;
inline double Det(double a, double b, double c, double d);

bool LineLineIntersect(double x1, double y1, //Line 1 start
	double x2, double y2, //Line 1 end
	double x3, double y3, //Line 2 start
	double x4, double y4, //Line 2 end
	double &ixOut, double &iyOut); //Output

int isInside(Point lineStart, Point lineEnd, Point p);

bool onSegment(Point p, Point q, Point r);

int orientation(Point p, Point q, Point r);

bool doIntersect(Point p1, Point q1, Point p2, Point q2);

void clip(vector < Point >& polygon, vector < Point > clippingWindow);
