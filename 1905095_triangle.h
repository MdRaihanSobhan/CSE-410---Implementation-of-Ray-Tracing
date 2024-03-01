#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<cmath>
#include<iomanip>
#include "1905095_color.h" // color class
#include "1905095_vector3D.h" // vector class
 // color class
#define pi acos(-1.0)
using namespace std;

class triangle 
{
private:
    vector3D a,b,c; // coordinates of the triangle
    color clr; // color of the triangle

public:
    triangle();
    triangle(vector3D a, vector3D b, vector3D c);
    triangle(vector3D a, vector3D b, vector3D c, color clr);
    triangle(const triangle &t); // copy constructor

    void sortTriangle(); // sort the triangle in ascending order of y coordinates
    
    void resetColor(); // reset the color of the triangle
    // getter and setter
    void setTriangle(vector3D a, vector3D b, vector3D c);
    void setColor(color clr);
    vector3D getA();
    vector3D getB();
    vector3D getC();
    color getColor();

    // outputstream
    friend ostream& operator<<(ostream& os, triangle& t);
    // inputstream
    friend istream& operator>>(istream& is, triangle& t);

    ~triangle();
}; 

triangle::triangle()
{
    a = vector3D();
    b = vector3D();
    c = vector3D();
    clr = color();
}

triangle::triangle(vector3D a, vector3D b, vector3D c)
{
    this->a = a;
    this->b = b;
    this->c = c;
    clr = color();
}

triangle::triangle(vector3D a, vector3D b, vector3D c, color clr)
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
        vector3D temp = a;
        a = b;
        b = temp;
    }
    if (a.getY() > c.getY()) {
        vector3D temp = a;
        a = c;
        c = temp;
    }
    if (b.getY() > c.getY()) {
        vector3D temp = b;
        b = c;
        c = temp;
    }
}

void triangle::resetColor() {
    clr.setColor();
}

// getter and setter
void triangle::setTriangle(vector3D a, vector3D b, vector3D c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

void triangle::setColor(color clr) {
    this->clr = clr;
}

vector3D triangle::getA() {
    return a;
}

vector3D triangle::getB() {
    return b;
}

vector3D triangle::getC() {
    return c;
}

color triangle::getColor() {
    return clr;
}

// outputstream
ostream& operator<<(ostream& os, triangle& t) {
    os << t.a << t.b << t.c;
    return os;
}
// inputstream
istream& operator>>(istream& is, triangle& t) {
    is >> t.a >> t.b >> t.c;
    return is;
}

triangle::~triangle()
{
}



