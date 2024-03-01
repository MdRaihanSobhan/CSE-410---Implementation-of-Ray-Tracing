#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<cmath>
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

class vector3D{
public:
    double x,y,z; // coordinates of the vector
    double scaleDownFactor; // scale down factor for the vector

    vector3D();
    vector3D(double x, double y, double z);
    vector3D(double x, double y, double z, double scaleDownFactor);
    //copy constructor
    vector3D(const vector3D &v); 
    // operator overloading
    vector3D operator+(const vector3D &v);
    vector3D operator-(const vector3D &v);
    vector3D operator*(double constant);
    vector3D operator/(double constant);
    vector3D operator=(const vector3D &v);
    double operator*(const vector3D &v); // dot product
    vector3D operator^(const vector3D &v); // cross product

    void scaleDown();
    double length();
    void normalize();


    // getter and setter
    void setVector(double x, double y, double z);
    void setScaleDownFactor(double scaleDownFactor);
    double getX();
    double getY();
    double getZ();
    double getScaleDownFactor();
    
    // outputstream 
    friend ostream& operator<<(ostream& os, vector3D& v);
    // inputstream
    friend istream& operator>>(istream& is, vector3D& v);

    // apply Rodrigues' rotation formula
    friend vector3D applyRodrigues(vector3D& v, vector3D& k, double theta); 

    ~vector3D();
};

vector3D::vector3D()
{
    x=0;
    y=0;
    z=0;
    scaleDownFactor=1;
}

vector3D::vector3D(double x, double y, double z)
{
    this->x=x;
    this->y=y;
    this->z=z;
    scaleDownFactor=0.1;
}

vector3D::vector3D(double x, double y, double z, double scaleDownFactor)
{
    this->x=x;
    this->y=y;
    this->z=z;
    this->scaleDownFactor=scaleDownFactor;
}

//copy constructor
vector3D::vector3D(const vector3D &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    scaleDownFactor = v.scaleDownFactor;
}

// operator overloading
vector3D vector3D::operator+(const vector3D &v) {
    vector3D temp = vector3D(x+v.x, y+v.y, z+v.z);
    return temp;
}
vector3D vector3D::operator-(const vector3D &v) {
    vector3D temp = vector3D(x-v.x, y-v.y, z-v.z);
    return temp;
}
vector3D vector3D::operator*(double constant) {
    vector3D temp = vector3D(x*constant, y*constant, z*constant);
    return temp;
}
vector3D vector3D::operator/(double constant) {
    if(constant == 0) {
        return vector3D(0,0,0);
    }
    vector3D temp = vector3D(x/constant, y/constant, z/constant);
    return temp;
}
vector3D vector3D::operator=(const vector3D &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    scaleDownFactor = v.scaleDownFactor;
    return *this;
}
double vector3D::operator*(const vector3D &v) {
    return x*v.x + y*v.y + z*v.z;
}
vector3D vector3D::operator^(const vector3D &v) {
    vector3D temp = vector3D(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    return temp;
}

void vector3D::scaleDown(){
    x/=scaleDownFactor;
    y/=scaleDownFactor;
    z/=scaleDownFactor;
    scaleDownFactor=1;
}

double vector3D::length(){
    return sqrt(x*x+y*y+z*z);
}

void vector3D::normalize(){
    double len=length();
    x/=len;
    y/=len;
    z/=len;
}

// getter and setter
void vector3D::setVector(double x, double y, double z) {
    this->x=x;
    this->y=y;
    this->z=z;
}
void vector3D::setScaleDownFactor(double scaleDownFactor) {
    this->scaleDownFactor = scaleDownFactor;
}
double vector3D::getX() {
    return x;
}
double vector3D::getY() {
    return y;
}
double vector3D::getZ() {
    return z;
}
double vector3D::getScaleDownFactor() {
    return scaleDownFactor;
}

// outputstream
ostream& operator<<(ostream& os, vector3D& v) {
    os << fixed << setprecision(7) << v.x << " " << v.y << " " << v.z << endl; 
    return os;
}
// inputstream
istream& operator>>(istream& is, vector3D& v) {
    is >> v.x >> v.y >> v.z;
    v.scaleDownFactor = 1; // default scale down factor
    return is;
}

// apply Rodrigues' rotation formula
vector3D applyRodrigues(vector3D &v, vector3D &k, double theta) { 
    k.normalize();
    vector3D v1 = v*cos(theta*pi/180);
    vector3D v2 = k*(k*v)*(1-cos(theta*pi/180));
    vector3D v3 = (k^v)*sin(theta*pi/180);
    return v1+v2+v3;
}
vector3D::~vector3D()
{
}
