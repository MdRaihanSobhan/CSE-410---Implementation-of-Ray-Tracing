#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<cmath>
#include<iomanip>
#include "1905095_triangle.h" // triangle class
#define pi acos(-1.0)
using namespace std;

class matrix4D{
private:
    double Matrix [4][4];
public:
    matrix4D();
    matrix4D(double Matrix[4][4]);
    matrix4D(const matrix4D &m); // copy constructor

    // operator overloading
    matrix4D operator+(const matrix4D &m);
    matrix4D operator-(const matrix4D &m);
    matrix4D operator*(double constant);
    matrix4D operator/(double constant);
    matrix4D operator=(const matrix4D &m);
    matrix4D operator*(const matrix4D &m); // matrix multiplication
    vectorPoint3D operator*( vectorPoint3D &v); // matrix vector multiplication
    triangle operator*( triangle &t); // matrix triangle multiplication

    //matrix functions
    void identityMatrix();
    void translationMatrix(vectorPoint3D v);
    void scalingMatrix(vectorPoint3D v);
    void rotationMatrix(vectorPoint3D v, double theta);

    // getter and setter
    void setMatrix(double Matrix[4][4]);
    double getMatrix(int i, int j);

    // outputstream
    friend ostream& operator<<(ostream& os, matrix4D& m);
    // inputstream
    friend istream& operator>>(istream& is, matrix4D& m);

    ~matrix4D();
};

matrix4D::matrix4D()
{
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            Matrix[i][j] = 0;
        }
    }
}

matrix4D::matrix4D(double Matrix[4][4])
{
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            this->Matrix[i][j] = Matrix[i][j];
        }
    }
}

matrix4D::matrix4D(const matrix4D &m)
{
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            Matrix[i][j] = m.Matrix[i][j];
        }
    }
}

// operator overloading
matrix4D matrix4D::operator+(const matrix4D &m) {
    matrix4D temp = matrix4D();
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            temp.Matrix[i][j] = Matrix[i][j] + m.Matrix[i][j];
        }
    }
    return temp;
}

matrix4D matrix4D::operator-(const matrix4D &m) {
    matrix4D temp = matrix4D();
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            temp.Matrix[i][j] = Matrix[i][j] - m.Matrix[i][j];
        }
    }
    return temp;
}

matrix4D matrix4D::operator*(double constant) {
    matrix4D temp = matrix4D();
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            temp.Matrix[i][j] = Matrix[i][j] * constant;
        }
    }
    return temp;
}

matrix4D matrix4D::operator/(double constant) {
    if(constant == 0) {
        return matrix4D();
    }
    matrix4D temp = matrix4D();
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            temp.Matrix[i][j] = Matrix[i][j] / constant;
        }
    }
    return temp;
}

matrix4D matrix4D::operator=(const matrix4D &m) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            Matrix[i][j] = m.Matrix[i][j];
        }
    }
    return *this;
}

matrix4D matrix4D::operator*(const matrix4D &m) {
    matrix4D temp = matrix4D();
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            for(int k=0; k<4; k++) {
                temp.Matrix[i][j] += Matrix[i][k] * m.Matrix[k][j];
            }
        }
    }
    return temp;
}

vectorPoint3D matrix4D::operator*( vectorPoint3D &v) {
    double ara[4]={0,0,0,0};
    double ara2[4]={v.getX(), v.getY(), v.getZ(), v.getScaleDownFactor()};
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            ara[i] += Matrix[i][j] * ara2[j];
        }
    }
    vectorPoint3D temp = vectorPoint3D(ara[0], ara[1], ara[2], ara[3]);
    temp.scaleDown();
    return temp;
}

triangle matrix4D::operator*( triangle &t) {
    vectorPoint3D a = t.getA();
    vectorPoint3D b = t.getB();
    vectorPoint3D c = t.getC();

    triangle temp = triangle((*this)*a, (*this)*b, (*this)*c, t.getColor());
    return temp;
}

//matrix functions
void matrix4D::identityMatrix() {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if(i==j) {
                Matrix[i][j] = 1;
            }
            else {
                Matrix[i][j] = 0;
            }
        }
    }
}

void matrix4D::translationMatrix(vectorPoint3D v) {
    identityMatrix();
    Matrix[0][3] = v.getX();
    Matrix[1][3] = v.getY();
    Matrix[2][3] = v.getZ();
}

void matrix4D::scalingMatrix(vectorPoint3D v) {
    identityMatrix();
    Matrix[0][0] = v.getX();
    Matrix[1][1] = v.getY();
    Matrix[2][2] = v.getZ();
}

//rotation using Rodrigues' rotation function (friend function of vectorPoint3D class)
void matrix4D::rotationMatrix(vectorPoint3D v, double theta) {
    identityMatrix();
    v.normalize();
    vectorPoint3D a(1.0,0.0,0.0); 
    vectorPoint3D b(0.0,1.0,0.0);
    vectorPoint3D c(0.0,0.0,1.0);
    vectorPoint3D r1 = applyRodrigues(a, v, theta);
    vectorPoint3D r2 = applyRodrigues(b, v, theta);
    vectorPoint3D r3 = applyRodrigues(c, v, theta);
    Matrix[0][0] = r1.getX();
    Matrix[0][1] = r2.getX();
    Matrix[0][2] = r3.getX();
    Matrix[1][0] = r1.getY();
    Matrix[1][1] = r2.getY();
    Matrix[1][2] = r3.getY();
    Matrix[2][0] = r1.getZ();
    Matrix[2][1] = r2.getZ();
    Matrix[2][2] = r3.getZ();
}

// getter and setter
void matrix4D::setMatrix(double Matrix[4][4]) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            this->Matrix[i][j] = Matrix[i][j];
        }
    }
}

double matrix4D::getMatrix(int i, int j) {
    return Matrix[i][j];
}

// outputstream
ostream& operator<<(ostream& os, matrix4D& m) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            os << m.Matrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

// inputstream
istream& operator>>(istream& is, matrix4D& m) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            is >> m.Matrix[i][j];
        }
    }
    return is;
}

matrix4D::~matrix4D()
{
}

