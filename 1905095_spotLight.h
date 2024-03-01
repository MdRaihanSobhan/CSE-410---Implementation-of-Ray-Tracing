#include "1905095_pointLight.h"

class spotLight{
private:
    pointLight point_light; // position and color of the point light
    vectorPoint3D direction;
    double angle; // cut off angle of the spot light

public:
    spotLight();
    spotLight(pointLight point_light, vectorPoint3D direction, double angle);
    spotLight(const spotLight &sl); // copy constructor

    // getter and setter
    void setPointLight(pointLight point_light);
    void setDirection(vectorPoint3D direction);
    void setAngle(double angle);
    pointLight getPointLight();
    vectorPoint3D getDirection();
    double getAngle();

    // draw the spot light
    void drawSpotLight();

    // outputstream
    friend ostream &operator<<(ostream &os, spotLight &sl);
    // inputstream
    friend istream &operator>>(istream &is, spotLight &sl);

    ~spotLight();
};

spotLight::spotLight()
{
    point_light = pointLight();
    direction = vectorPoint3D();
    angle = 0;
}

spotLight::spotLight(pointLight point_light, vectorPoint3D direction, double angle)
{
    this->point_light = point_light;
    this->direction = direction;
    this->angle = angle;
}

spotLight::spotLight(const spotLight &sl)
{
    point_light = sl.point_light;
    direction = sl.direction;
    angle = sl.angle;
}

// getter and setter

void spotLight::setPointLight(pointLight point_light)
{
    this->point_light = point_light;
}
void spotLight::setDirection(vectorPoint3D direction)
{
    this->direction = direction;
}
void spotLight::setAngle(double angle)
{
    this->angle = angle;
}
pointLight spotLight::getPointLight()
{
    return point_light;
}
vectorPoint3D spotLight::getDirection()
{
    return direction;
}
double spotLight::getAngle()
{
    return angle;
}

// draw the spot light
void spotLight::drawSpotLight()
{
    glPointSize(15);
    glBegin(GL_POINTS);
    glColor3f(point_light.getColor().r, point_light.getColor().g, point_light.getColor().b);
    glVertex3f(point_light.getPosition().getX(), point_light.getPosition().getY(), point_light.getPosition().getZ());
    glEnd();
}

// outputstream
ostream &operator<<(ostream &os, spotLight &sl)
{
    os << sl.point_light << " " << sl.direction << " " << sl.angle;
    return os;
}

// inputstream
istream &operator>>(istream &is, spotLight &sl)
{
    pointLight point_light;
    vectorPoint3D direction;
    double angle;
    is >> point_light >> direction >> angle;
    sl.setPointLight(point_light);
    sl.setDirection(direction);
    sl.setAngle(angle);
    return is;
}

spotLight::~spotLight()
{
}