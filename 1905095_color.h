#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include <cstdint>
#include <cstdlib>  // For rand() function
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <limits>
#include <vector>
#include<iomanip>

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



static unsigned long int g_seed = 1;
inline int getRandomNumber()
{
    g_seed = (214013 * g_seed + 2531011);

    return (g_seed >> 16) & 0x7FFF;
}




#define pi acos(-1.0)
class color
{
public:
    int r,g,b;
    color(/* args */);
    color(int r, int g, int b); 
    void setColor(); 
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

color::color(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void color::setColor() {
    r = getRandomNumber();
    g = getRandomNumber();
    b = getRandomNumber();
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


