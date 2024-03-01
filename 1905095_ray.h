#include "1905095_vector3D.h" 

class ray
{
private:
    vector3D origin;
    vector3D direction;

public:
    ray();
    ray(vector3D origin, vector3D direction);
    ray(const ray &r); // copy constructor

    // getter and setter
    void setRay(vector3D origin, vector3D direction);
    void setOrigin(vector3D origin);
    void setDirection(vector3D direction);
    vector3D getOrigin();
    vector3D getDirection();

    // outputstream
    friend ostream &operator<<(ostream &os, ray &r);
    // inputstream
    friend istream &operator>>(istream &is, ray &r);

    ~ray();
};

ray::ray()
{
    origin = vector3D();
    direction = vector3D();
}

ray::ray(vector3D origin, vector3D direction)
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
void ray::setRay(vector3D origin, vector3D direction)
{
    this->origin = origin;
    direction.normalize();
    this->direction = direction;
}
void ray::setOrigin(vector3D origin)
{
    this->origin = origin;
}
void ray::setDirection(vector3D direction)
{
    direction.normalize();
    this->direction = direction;
}
vector3D ray::getOrigin()
{
    return origin;
}
vector3D ray::getDirection()
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
    vector3D origin, direction;
    is >> origin >> direction;
    r.setRay(origin, direction);
    return is;
}