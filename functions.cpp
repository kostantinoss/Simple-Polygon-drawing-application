#include <iostream>
#include <cmath>
#include <vector>
#include <assert.h>
#include "functions.h"
using namespace std;

/** Calculate determinant of matrix:
	[a b]
	[c d]
*/
inline double Det(double a, double b, double c, double d)
{
	return a*d - b*c;
}

///Calculate intersection of two lines.
///\return true if found, false if not found or error
bool LineLineIntersect(double x1, double y1, //Line 1 start
	double x2, double y2, //Line 1 end
	double x3, double y3, //Line 2 start
	double x4, double y4, //Line 2 end
	double &ixOut, double &iyOut) //Output
{
	//http://mathworld.wolfram.com/Line-LineIntersection.html

	double detL1 = Det(x1, y1, x2, y2);
	double detL2 = Det(x3, y3, x4, y4);
	double x1mx2 = x1 - x2;
	double x3mx4 = x3 - x4;
	double y1my2 = y1 - y2;
	double y3my4 = y3 - y4;

	double xnom = Det(detL1, x1mx2, detL2, x3mx4);
	double ynom = Det(detL1, y1my2, detL2, y3my4);
	double denom = Det(x1mx2, y1my2, x3mx4, y3my4);
	if(denom == 0.0)//Lines don't seem to cross
	{
		ixOut = NAN;
		iyOut = NAN;
		return false;
	}

	ixOut = xnom / denom;
	iyOut = ynom / denom;
	if(!isfinite(ixOut) || !isfinite(iyOut)) //Probably a numerical issue
		return false;

	return true; //All OK
}

//=============================================================================//
// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    return TRUE;

    return FALSE;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.y - p.y) * (r.x - q.x) -
            (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns TRUE if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return TRUE;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return TRUE;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return TRUE;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return TRUE;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return TRUE;

    return FALSE; // Doesn't fall in any of the above cases
}

int isInside(Point lineStart, Point lineEnd, Point p)
{
    //The line is defined by (x1,y1) and (x2, y2).
    //The point we want to check is defined by (x, y)
    int x1 = lineStart.x; int y1 = lineStart.y;
    int x2 = lineEnd.x;   int y2 = lineEnd.y;
    int x = p.x; int y = p.y;

    int d = (x - x1)*(y2 - y1) - (y - y1)*(x2 - x1);

    if(d < 0)           //returns d < 0 if point (x,y) is outside of line
    {
        return -1;
    }
    else if(d > 0)      //returns d > 0 if point (x,y) is inside of line
    {
        return 1;
    }
    else                //returns d = 0 if point (x,y) is on the line
    {
        return 0;
    }

    return -2;          //returns -2 on error or any other case.
}

void normalization(int *x1, int *y2, int *x2, int *y1)              // travaei kata :
{
    int temp ;
    if ( (*x2 > *x1) && (*y2 > *y1) )                           //katw deksia (swsto)
    {
        return ;
    }
    else if ( (*x1 > *x2) && (*y2 > *y1) )                           //katw aristera (x1<->x2)
    {
        temp = *x1 ;
        *x1 = *x2 ;
        *x2 = temp ;
    }
    else if ( (*x1 > *x2) && (*y1 > *y2) )                             //panw aristera (x1<->x2,y1<->y2)
    {
        temp = *x1 ;
        *x1 = *x2 ;
        *x2 = temp ;
        temp = *y1 ;
        *y1 = *y2 ;
        *y2 = temp;
    }
    else if ( (*x2 > *x1) && (*y1 > *y2) )                          //panw deksia (y1<->y2)
    {
        temp = *y1 ;
        *y1 = *y2 ;
        *y2 = temp;
    }
}
void clip(vector < Point >& polygon, vector < Point > clippingWindow) 
{
    vector < Point > inputList;
    vector <Point > outputList;

    outputList = polygon;

    for(int i = 0; i < 4; i++)
    {
        inputList = outputList;
        outputList.clear();
        Point s = inputList.back();
        for(int j = 0; j < inputList.size(); j++)
        {
            int temp1 = isInside(clippingWindow[i], clippingWindow[(i + 1)%4], inputList[j]);  //vlepei an to trexwn stoixeio e
            int temp2 = isInside(clippingWindow[i], clippingWindow[(i + 1)%4], s);			// mesa ,etsi ?
            if(temp1 == 1)
            {
                //int x = isInside(clippingWindow[i], clippingWindow[(i + 1)%4], s);
                if(temp2 < 1)
                {
                    Point intersectionPoint;
                    double xout;
                    double yout;

                    int temp2 = LineLineIntersect((double) clippingWindow[i].x, (double) clippingWindow[i].y, //Line 1 start
                        (double) clippingWindow[(i + 1)%4].x, (double) clippingWindow[(i + 1)%4].y, //Line 1 end
                        (double) inputList[j].x, (double) inputList[j].y, //Line 2 end
                        (double) s.x, (double) s.y,
                        xout, yout);

                    intersectionPoint.x  = (int) xout;
                    intersectionPoint.y = (int) yout;

                    glBegin(GL_POINTS);
                    glPointSize(5.0);
                        glColor3f(1.0,0.0,.0);
                        glVertex2i(intersectionPoint.x, intersectionPoint.y);
                    glEnd();
                    glFlush();

                    outputList.push_back(intersectionPoint);
                }

                outputList.push_back(inputList[j]);
            }
            else if(temp2 == 1)
            {
                Point intersectionPoint;
                double xout;
                double yout;

                int x = LineLineIntersect((double) clippingWindow[i].x, (double) clippingWindow[i].y, //Line 1 start
                    (double) clippingWindow[(i + 1)%4].x, (double) clippingWindow[(i + 1)%4].y, //Line 1 end
                    (double) s.x, (double) s.y,
                    (double) inputList[j].x, (double) inputList[j].y, //Line 2 end
                    xout, yout);

                intersectionPoint.x  = (int) xout;
                intersectionPoint.y = (int) yout;

                outputList.push_back(intersectionPoint);
            }

            s = inputList[j];

        }
		std::cout << "outputList.size(): " << outputList.size() << '\n';

    }
	
    int sum = 0 ;
	int i;
	if (outputList.size() == 4 )
	{
		for (i = 0 ; i < 4; i++)
		{
			if (( outputList[i].x == clippingWindow[i].x ) && ( outputList[i].x == clippingWindow[i].x ))
			{
				sum = sum + 1 ;
			}
		}
		if (sum == 4)
		{
			polygon.clear() ;
			return ;
		}
        else
        {
            polygon = outputList;
        }
	}																			//kanw allagh
	else  //(outputList.size() != 4)
	{
		polygon = outputList;
	}
    //polygon = outputList; //na mhn to xexasoyme
}
