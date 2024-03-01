#include "1905095_vector3D.h"
#include "1905095_color.h"
class pointLight
{
private:
    vector3D position;
    color clr;

public:
    pointLight();
    pointLight(vector3D position, color clr);
    pointLight(const pointLight &pl); // copy constructor

    // getter and setter
    void setPosition(vector3D position);
    void setColor(color clr);
    vector3D getPosition();
    color getColor();

    // draw the point light
    void drawPointLight();

    // outputstream
    friend ostream &operator<<(ostream &os, pointLight &pl);
    // inputstream
    friend istream &operator>>(istream &is, pointLight &pl);

    ~pointLight();
};

pointLight::pointLight()
{
    position = vector3D();
    clr = color();
}

pointLight::pointLight(vector3D position, color clr)
{
    this->position = position;
    this->clr = clr;
}

pointLight::pointLight(const pointLight &pl)
{
    position = pl.position;
    clr = pl.clr;
}

// getter and setter

void pointLight::setPosition(vector3D position)
{
    this->position = position;
}
void pointLight::setColor(color clr)
{
    this->clr = clr;
}
vector3D pointLight::getPosition()
{
    return position;
}
color pointLight::getColor()
{
    return clr;
}

// draw the point light
#include <iostream> // Add missing include

void pointLight::drawPointLight()
{
    glPointSize(5);
    glBegin(GL_POINTS);
        glColor3f(clr.r, clr.g, clr.b);
        glVertex3f(position.getX(), position.getY(), position.getZ());
    glEnd();    
}

// outputstream
ostream &operator<<(ostream &os, pointLight &pl)
{
    os << "Position: " << pl.position << "Color: " << pl.clr; 
    return os;
}
// inputstream
istream &operator>>(istream &is, pointLight &pl)
{
    is >> pl.position >> pl.clr;
    return is;
}