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
    void setColor(); 
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

void color::setColor() {
    r = getRandomNumber();
    g = getRandomNumber();
    b = getRandomNumber();
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


