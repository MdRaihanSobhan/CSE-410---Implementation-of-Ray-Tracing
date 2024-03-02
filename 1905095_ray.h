#include "1905095_vector3D.h" 

class ray
{
private:


public:
    vectorPoint3D origin;
    vectorPoint3D direction;
    ray();
    ray(vectorPoint3D origin, vectorPoint3D direction);
    ray(const ray &r); // copy constructor

    // getter and setter
    void setRay(vectorPoint3D origin, vectorPoint3D direction);
    void setOrigin(vectorPoint3D origin);
    void setDirection(vectorPoint3D direction);
    vectorPoint3D getOrigin();
    vectorPoint3D getDirection();

    // outputstream
    friend ostream &operator<<(ostream &os, ray &r);
    // inputstream
    friend istream &operator>>(istream &is, ray &r);

    ~ray();
};

ray::ray()
{
    origin = vectorPoint3D();
    direction = vectorPoint3D();
}

ray::ray(vectorPoint3D origin, vectorPoint3D direction)
{
    this->origin = origin;
    direction.normalize();
    this->direction = direction;
}

ray::ray(const ray &r)
{
    origin = r.origin;
    direction = r.direction;
}

// getter and setter
void ray::setRay(vectorPoint3D origin, vectorPoint3D direction)
{
    this->origin = origin;
    direction.normalize();
    this->direction = direction;
}
void ray::setOrigin(vectorPoint3D origin)
{
    this->origin = origin;
}
void ray::setDirection(vectorPoint3D direction)
{
    direction.normalize();
    this->direction = direction;
}
vectorPoint3D ray::getOrigin()
{
    return origin;
}
vectorPoint3D ray::getDirection()
{
    return direction;
}

// outputstream
ostream &operator<<(ostream &os, ray &r)
{
    os << "Origin: " << r.origin << ", Direction: " << r.direction << endl;
    return os;
}

// inputstream
istream &operator>>(istream &is, ray &r)
{
    vectorPoint3D origin, direction;
    is >> origin >> direction;
    r.setRay(origin, direction);
    return is;
}

ray::~ray()
{
}