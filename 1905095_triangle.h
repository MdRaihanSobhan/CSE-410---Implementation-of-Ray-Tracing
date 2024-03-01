#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<cmath>
#include<iomanip>
#include "1905095_general.h"
 // color class
#define pi acos(-1.0)
using namespace std;

class triangle : public object
{

public:
    vectorPoint3D a,b,c; // coordinates of the triangle

    triangle();
    triangle(vectorPoint3D a, vectorPoint3D b, vectorPoint3D c);
    triangle(vectorPoint3D a, vectorPoint3D b, vectorPoint3D c, color clr);
    triangle(const triangle &t); // copy constructor

    void sortTriangle(); // sort the triangle in ascending order of y coordinates
    
    void resetColor(); // reset the color of the triangle
    // getter and setter
    void setTriangle(vectorPoint3D a, vectorPoint3D b, vectorPoint3D c);
    void setColor(color clr);
    vectorPoint3D getA();
    vectorPoint3D getB();
    vectorPoint3D getC();
    color getColor();

    virtual ray getNormalAt(vectorPoint3D point, ray incident); 
    virtual void draw();
    virtual double findIntersection(ray r, color &col, int depth);

    double determinant(double ara[3][3]);

    // outputstream
    friend ostream& operator<<(ostream& os, triangle& t);
    // inputstream
    friend istream& operator>>(istream& is, triangle& t);

    ~triangle();
}; 

triangle::triangle()
{
    a = vectorPoint3D();
    b = vectorPoint3D();
    c = vectorPoint3D();
    clr = color();
}

triangle::triangle(vectorPoint3D a, vectorPoint3D b, vectorPoint3D c)
{
    this->a = a;
    this->b = b;
    this->c = c;
    clr = color();
}

triangle::triangle(vectorPoint3D a, vectorPoint3D b, vectorPoint3D c, color clr)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->clr = clr;
}

triangle::triangle(const triangle &t)
{
    a = t.a;
    b = t.b;
    c = t.c;
    clr = t.clr;
}


void triangle::sortTriangle() {
    if (a.getY() > b.getY()) {
        vectorPoint3D temp = a;
        a = b;
        b = temp;
    }
    if (a.getY() > c.getY()) {
        vectorPoint3D temp = a;
        a = c;
        c = temp;
    }
    if (b.getY() > c.getY()) {
        vectorPoint3D temp = b;
        b = c;
        c = temp;
    }
}

void triangle::resetColor() {
    clr.setColor();
}

// getter and setter
void triangle::setTriangle(vectorPoint3D a, vectorPoint3D b, vectorPoint3D c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

void triangle::setColor(color clr) {
    this->clr = clr;
}

vectorPoint3D triangle::getA() {
    return a;
}

vectorPoint3D triangle::getB() {
    return b;
}

vectorPoint3D triangle::getC() {
    return c;
}

color triangle::getColor() {
    return clr;
}

double triangle::determinant(double ara[3][3]) {
    double det = 0;
    for (int i=0; i<3; i++) {
        det += ara[0][i]*(ara[1][(i+1)%3]*ara[2][(i+2)%3] - ara[1][(i+2)%3]*ara[2][(i+1)%3]);
    }
    return det;
}

ray triangle::getNormalAt(vectorPoint3D point, ray incident) {
    vectorPoint3D normal = (b-a)^(c-a);
    normal.normalize();
    ray r1 = ray(point, normal*(-1));
    ray r2 = ray(point, normal);
    if (incident.getDirection()*normal < 0) {
        return r1;
    }
    else{
        return r2;
    }
}

void triangle::draw() {
    glColor3f(clr.r, clr.g, clr.b);
    glBegin(GL_TRIANGLES);
    glVertex3f(a.getX(), a.getY(), a.getZ());
    glVertex3f(b.getX(), b.getY(), b.getZ());
    glVertex3f(c.getX(), c.getY(), c.getZ());
    glEnd();
}

double triangle::findIntersection(ray r, color &col, int depth) {
    double matrix_beta[3][3] = {
        {a.getX()-r.getOrigin().getX(), a.getX() - c.getX(), r.getDirection().getX()},
        {a.getY()-r.getOrigin().getY(), a.getY() - c.getY(), r.getDirection().getY()},
        {a.getZ()-r.getOrigin().getZ(), a.getZ() - c.getZ(), r.getDirection().getZ()}
    };

    double matrix_gamma[3][3] = {
        {a.getX()-b.getX(), a.getX() - r.getOrigin().getX(), r.getDirection().getX()},
        {a.getY()-b.getY(), a.getY() - r.getOrigin().getY(), r.getDirection().getY()},
        {a.getZ()-b.getZ(), a.getZ() - r.getOrigin().getZ(), r.getDirection().getZ()}
    };
    
    double matrix_t[3][3] = {
        {a.getX()-b.getX(), a.getX() - c.getX(), a.getX() - r.getOrigin().getX()},
        {a.getY()-b.getY(), a.getY() - c.getY(), a.getY() - r.getOrigin().getY()},
        {a.getZ()-b.getZ(), a.getZ() - c.getZ(), a.getZ() - r.getOrigin().getZ()}
    };

    double matrix_A[3][3] = {
        {a.getX()-b.getX(), a.getX() - c.getX(), r.getDirection().getX()},
        {a.getY()-b.getY(), a.getY() - c.getY(), r.getDirection().getY()},
        {a.getZ()-b.getZ(), a.getZ() - c.getZ(), r.getDirection().getZ()}
    };

    double det_A = determinant(matrix_A);
    double det_beta = determinant(matrix_beta);
    double det_gamma = determinant(matrix_gamma);
    double det_t = determinant(matrix_t);

    double beta = det_beta/det_A;
    double gamma = det_gamma/det_A;
    double t = det_t/det_A;

    if(beta+gamma<1 && beta>0 && gamma>0 && t>0){
        return t;
    }
    else{
        return -1;
    }
    
}


// outputstream
ostream& operator<<(ostream& os, triangle& t) {
    os << t.a << t.b << t.c;
    return os;
}
// inputstream
istream& operator>>(istream& is, triangle& t) {
    is >> t.a >> t.b >> t.c;
    is>> t.clr;
    is>>t.ambient>>t.diffuse>>t.specular>>t.reflection>>t.shininess;
    return is;
}

triangle::~triangle()
{
}



