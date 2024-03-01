#include "1905095_spotLight.h"
class object; 

extern vector <pointLight*> point_lights;
extern vector <spotLight*> spot_lights;
extern vector <object*> objects;
extern int recursion_depth;

class object
{
private:
    pointLight ref_point; 
    double height, width, length;
    color clr;
    double ambient, diffuse, specular, reflection, refraction; 
    int shininess;
public: 


    object();

    // getter and setter
    void setRefPoint(pointLight p);
    void setHeight(double h);
    void setWidth(double w);
    void setLength(double l);
    void setColor(color c);
    void setAmbient(double a);
    void setDiffuse(double d);
    void setSpecular(double s);
    void setShininess(int s);
    void setReflection(double r);
    void setRefraction(double r);

    pointLight getRefPoint();
    double getHeight();
    double getWidth();
    double getLength();
    virtual color getColor(vectorPoint3D p);
    double getAmbient();
    double getDiffuse();
    double getSpecular();
    int getShininess();
    double getReflection();
    double getRefraction();

    virtual void draw() = 0;
    virtual double findIntersection(ray r, color &col, int depth) = 0;
    virtual ray getNormalAt(vectorPoint3D point, ray incident) = 0;
    virtual double intersect(ray r, color &col, int depth); 

    // distructor
    virtual ~object();

};

object::object()
{
    ref_point = pointLight();
    height = 0;
    width = 0;
    length = 0;
    clr = color();
    ambient = 0;
    diffuse = 0;
    specular = 0;
    shininess = 0;
    reflection = 0;
    refraction = 0;
}

// getter and setter
void object::setRefPoint(pointLight p)
{
    ref_point = p;
}
void object::setHeight(double h)
{
    height = h;
}
void object::setWidth(double w)
{
    width = w;
}
void object::setLength(double l)
{
    length = l;
}
void object::setColor(color c)
{
    clr = c;
}
void object::setAmbient(double a)
{
    ambient = a;
}
void object::setDiffuse(double d)
{
    diffuse = d;
}
void object::setSpecular(double s)
{
    specular = s;
}
void object::setShininess(int s)
{
    shininess = s;
}
void object::setReflection(double r)
{
    reflection = r;
}
void object::setRefraction(double r)
{
    refraction = r;
}

pointLight object::getRefPoint()
{
    return ref_point;
}
double object::getHeight()
{
    return height;
}
double object::getWidth()
{
    return width;
}
double object::getLength()
{
    return length;
}
color object::getColor(vectorPoint3D p)
{
    return color(this->clr.r , this->clr.g , this->clr.b);
}
double object::getAmbient()
{
    return ambient;
}
double object::getDiffuse()
{
    return diffuse;
}
double object::getSpecular()
{
    return specular;
}
int object::getShininess()
{
    return shininess;
}
double object::getReflection()
{
    return reflection;
}
double object::getRefraction()
{
    return refraction;
}

double object::intersect(ray r, color &col, int depth)
{
    double t = findIntersection(r, col, depth);

    if(t<0) return -1;
    if(depth <= 0) return t;

    // find intersection point 
    vectorPoint3D intersection = r.getOrigin() + r.getDirection() * t;
    // find the color at the intersection point
    color intersection_color = getColor(intersection);

    // update the color with ambient light
    col = intersection_color * ambient;

    for(int i=0; i<point_lights.size(); i++)
    {
        // find the direction of the light
        vectorPoint3D light_position = point_lights[i]->getPosition(); 

    }
}


// destructor
object::~object()
{
    // free the memories
}