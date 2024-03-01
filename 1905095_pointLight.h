#include "1905095_ray.h"
class pointLight
{
private:
    vectorPoint3D position;
    color clr;

public:
    pointLight();
    pointLight(vectorPoint3D position, color clr);
    pointLight(const pointLight &pl); // copy constructor

    // getter and setter
    void setPosition(vectorPoint3D position);
    void setColor(color clr);
    vectorPoint3D getPosition();
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
    
}

pointLight::pointLight(vectorPoint3D position, color clr)
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

void pointLight::setPosition(vectorPoint3D position)
{
    this->position = position;
}
void pointLight::setColor(color clr)
{
    this->clr = clr;
}
vectorPoint3D pointLight::getPosition()
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

pointLight::~pointLight()
{
}