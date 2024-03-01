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

class vectorPoint3D{
public:
    double x,y,z; // coordinates of the vector
    double scaleDownFactor; // scale down factor for the vector

    vectorPoint3D();
    vectorPoint3D(double x, double y, double z);
    vectorPoint3D(double x, double y, double z, double scaleDownFactor);
    //copy constructor
    vectorPoint3D(const vectorPoint3D &v); 
    // operator overloading
    vectorPoint3D operator+(const vectorPoint3D &v);
    vectorPoint3D operator-(const vectorPoint3D &v);
    vectorPoint3D operator*(double constant);
    vectorPoint3D operator/(double constant);
    vectorPoint3D operator=(const vectorPoint3D &v);
    double operator*(const vectorPoint3D &v); // dot product
    vectorPoint3D operator^(const vectorPoint3D &v); // cross product

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
    friend ostream& operator<<(ostream& os, vectorPoint3D& v);
    // inputstream
    friend istream& operator>>(istream& is, vectorPoint3D& v);

    // apply Rodrigues' rotation formula
    friend vectorPoint3D applyRodrigues(vectorPoint3D& v, vectorPoint3D& k, double theta); 

    ~vectorPoint3D();
};

vectorPoint3D::vectorPoint3D()
{
    x=0;
    y=0;
    z=0;
    scaleDownFactor=1;
}

vectorPoint3D::vectorPoint3D(double x, double y, double z)
{
    this->x=x;
    this->y=y;
    this->z=z;
    scaleDownFactor=0.1;
}

vectorPoint3D::vectorPoint3D(double x, double y, double z, double scaleDownFactor)
{
    this->x=x;
    this->y=y;
    this->z=z;
    this->scaleDownFactor=scaleDownFactor;
}

//copy constructor
vectorPoint3D::vectorPoint3D(const vectorPoint3D &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    scaleDownFactor = v.scaleDownFactor;
}

// operator overloading
vectorPoint3D vectorPoint3D::operator+(const vectorPoint3D &v) {
    vectorPoint3D temp = vectorPoint3D(x+v.x, y+v.y, z+v.z);
    return temp;
}
vectorPoint3D vectorPoint3D::operator-(const vectorPoint3D &v) {
    vectorPoint3D temp = vectorPoint3D(x-v.x, y-v.y, z-v.z);
    return temp;
}
vectorPoint3D vectorPoint3D::operator*(double constant) {
    vectorPoint3D temp = vectorPoint3D(x*constant, y*constant, z*constant);
    return temp;
}
vectorPoint3D vectorPoint3D::operator/(double constant) {
    if(constant == 0) {
        return vectorPoint3D(0,0,0);
    }
    vectorPoint3D temp = vectorPoint3D(x/constant, y/constant, z/constant);
    return temp;
}
vectorPoint3D vectorPoint3D::operator=(const vectorPoint3D &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    scaleDownFactor = v.scaleDownFactor;
    return *this;
}
double vectorPoint3D::operator*(const vectorPoint3D &v) {
    return x*v.x + y*v.y + z*v.z;
}
vectorPoint3D vectorPoint3D::operator^(const vectorPoint3D &v) {
    vectorPoint3D temp = vectorPoint3D(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    return temp;
}

void vectorPoint3D::scaleDown(){
    x/=scaleDownFactor;
    y/=scaleDownFactor;
    z/=scaleDownFactor;
    scaleDownFactor=1;
}

double vectorPoint3D::length(){
    return sqrt(x*x+y*y+z*z);
}

void vectorPoint3D::normalize(){
    double len=length();
    x/=len;
    y/=len;
    z/=len;
}

// getter and setter
void vectorPoint3D::setVector(double x, double y, double z) {
    this->x=x;
    this->y=y;
    this->z=z;
}
void vectorPoint3D::setScaleDownFactor(double scaleDownFactor) {
    this->scaleDownFactor = scaleDownFactor;
}
double vectorPoint3D::getX() {
    return x;
}
double vectorPoint3D::getY() {
    return y;
}
double vectorPoint3D::getZ() {
    return z;
}
double vectorPoint3D::getScaleDownFactor() {
    return scaleDownFactor;
}

// outputstream
ostream& operator<<(ostream& os, vectorPoint3D& v) {
    os << fixed << setprecision(7) << v.x << " " << v.y << " " << v.z << endl; 
    return os;
}
// inputstream
istream& operator>>(istream& is, vectorPoint3D& v) {
    is >> v.x >> v.y >> v.z;
    v.scaleDownFactor = 1; // default scale down factor
    return is;
}

// apply Rodrigues' rotation formula
vectorPoint3D applyRodrigues(vectorPoint3D &v, vectorPoint3D &k, double theta) { 
    k.normalize();
    vectorPoint3D v1 = v*cos(theta*pi/180);
    vectorPoint3D v2 = k*(k*v)*(1-cos(theta*pi/180));
    vectorPoint3D v3 = (k^v)*sin(theta*pi/180);
    return v1+v2+v3;
}
vectorPoint3D::~vectorPoint3D()
{
}
