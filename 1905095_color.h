#include<bits/stdc++.h>

#include <GL/glut.h>
#ifdef _linux_
    #include <GL/glut.h>
#elif WIN32
    #include <windows.h>
    #include <glut.h>
#elif _APPLE_
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#endif

#define pi acos(-1.0)
using namespace std;


#define pi acos(-1.0)
class color
{
public:
    double r,g,b;
    color(/* args */);
    color(double r, double g, double b);

    void setColor(double r, double g, double b); 
    // overload the * operator
    color operator*(double k); 
    // overload the + operator
    color operator+(color clr); 
    // outputstream
    friend ostream &operator<<(ostream &os, color &clr);
    // inputstream
    friend istream &operator>>(istream &is, color &clr);
    ~color();
};

color::color(/* args */)
{
    r=0; 
    g=0;
    b=0;
}

color::color(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}


void color::setColor(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

color color::operator*(double k)
{
    return color(r*k, g*k, b*k);
}

color color::operator+(color clr)
{
    return color(r+clr.r, g+clr.g, b+clr.b);
}

ostream &operator<<(ostream &os, color &clr)
{
    os << "Color: " << clr.r << " " << clr.g << " " << clr.b << endl;
    return os;

}

istream &operator>>(istream &is, color &clr)
{
    is >> clr.r >> clr.g >> clr.b;
    return is;
}

color::~color()
{
}

