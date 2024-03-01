#include "1905095_sphere.h"

class checkerBoard : public object
{
public: 
    int noOfSquares;

    checkerBoard();
    checkerBoard(int boardWidth, int squareWidth);
    virtual color getColorAt(vectorPoint3D point);
    virtual ray getNormalAt(vectorPoint3D point, ray incident);
    virtual void draw();
    virtual double findIntersection(ray r, color &col, int depth);
};

checkerBoard::checkerBoard()
{
    noOfSquares = 1; 
}

checkerBoard::checkerBoard(int boardWidth, int squareWidth)
{
    noOfSquares = boardWidth/squareWidth;
    ref_point = vectorPoint3D(-boardWidth/2, -boardWidth/2, 0);
    length = squareWidth;
}

color checkerBoard::getColorAt(vectorPoint3D point)
{
    int x = (point.getX() - ref_point.getX())/length;
    int y = (point.getY() - ref_point.getY())/length;
    
    if(x<0 || y<0 || x>=noOfSquares || y>=noOfSquares) return color(0, 0, 0);

    if((x+y)%2 == 0) return color(1, 1, 1);
    else return color(0, 0, 0);
}

ray checkerBoard::getNormalAt(vectorPoint3D point, ray incident)
{
    if(incident.getDirection().getZ() > 0) {
        return ray(point, vectorPoint3D(0, 0, 1));
    }
    else {
        return ray(point, vectorPoint3D(0, 0, -1));
    }
}

void checkerBoard::draw()
{
    for(int i=0; i<noOfSquares; i++) {
        for(int j=0; j<noOfSquares; j++) {
            if((i+j)%2 == 0) glColor3f(1, 1, 1);
            else glColor3f(0, 0, 0);
            
            glBegin(GL_QUADS);
            glVertex3f(ref_point.getX() + i*length, ref_point.getY() + j*length, 0);
            glVertex3f(ref_point.getX() + (i+1)*length, ref_point.getY() + j*length, 0);
            glVertex3f(ref_point.getX() + (i+1)*length, ref_point.getY() + (j+1)*length, 0);
            glVertex3f(ref_point.getX() + i*length, ref_point.getY() + (j+1)*length, 0);
            glEnd();
        }
    }
}

double checkerBoard::findIntersection(ray r, color &col, int depth)
{
    vectorPoint3D normal = vectorPoint3D(0, 0, 1);
    double dot = r.getDirection()*normal;

    if(round(dot * 100) == 0) return -1;

    double t = -(normal*r.getOrigin())/dot;
    vectorPoint3D v = r.getOrigin() + r.getDirection()*t;

    if(v.getX() <= ref_point.getX() || v.getX() >= abs(ref_point.getX()) && v.getY()<=ref_point.getY() && v.getY()>=abs(ref_point.getY())) {
        return -1;
    }
    return t;
}