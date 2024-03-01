#include "1905095_spotLight.h"
class object; 

extern vector <pointLight*> point_lights;
extern vector <spotLight*> spot_lights;
extern vector <object*> objects;
extern int recursion_depth;

class object
{
protected:
    vectorPoint3D ref_point; 
    double height, width, length;
    color clr;
    double ambient, diffuse, specular, reflection, refraction; 
    int shininess;
public: 


    object();

    // getter and setter
    void setRefPoint(vectorPoint3D p);
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

    vectorPoint3D getRefPoint();
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
    ~object();

};

object::object()
{
    ref_point = vectorPoint3D();
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
void object::setRefPoint(vectorPoint3D p)
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


vectorPoint3D object::getRefPoint()
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
        vectorPoint3D light_direction = intersection - light_position;
        light_direction.normalize();

        // cast a incident ray from the light to the intersection point
        ray incidentRay = ray(light_position, light_direction);
        ray normal = getNormalAt(intersection, incidentRay);


        // avoid self recursion
        double dist = (intersection - light_position).length();
        if(dist < 0.00001) continue;

        // check if the light is blocked by any object
        bool blocked = false;
        for(object *o : objects)
        {
            if(o == this) continue;
            double t = o->findIntersection(incidentRay, col, 0);
            if(t > 0 && t+0.00001 < dist)
            {
                blocked = true;
                break;
            }
        }
        
        if(!blocked)
        {
            double lambert = max(0.0,  incidentRay.getDirection()*normal.getDirection()*(-1));
            ray reflectionRay = ray(intersection, incidentRay.getDirection() - normal.getDirection() * 2 * (incidentRay.getDirection()*normal.getDirection()));
            double phong = max(0.0, reflectionRay.getDirection()*r.getDirection()*(-1));
            // update diffuse and specular 
            col.r += (intersection_color.r * diffuse * lambert + point_lights[i]->getColor().r);
            col.g += (intersection_color.g * diffuse * lambert + point_lights[i]->getColor().g);
            col.b += (intersection_color.b * diffuse * lambert + point_lights[i]->getColor().b);

            col.r += (point_lights[i]->getColor().r * specular * pow(phong, shininess)*intersection_color.r);
            col.g += (point_lights[i]->getColor().g * specular * pow(phong, shininess)*intersection_color.g);
            col.b += (point_lights[i]->getColor().b * specular * pow(phong, shininess)*intersection_color.b);

        }
    }

    // for spotlights, dot and angle needed to be calculated
    for(int i=0; i<spot_lights.size(); i++)
    {
        // find the direction of the light
        vectorPoint3D light_position = spot_lights[i]->getPointLight().getPosition(); 
        vectorPoint3D light_direction = intersection - light_position;
        light_direction.normalize();

        double dot = light_direction*spot_lights[i]->getDirection();
        double angle = acos(dot/(light_direction.length()*spot_lights[i]->getDirection().length()));
        angle = angle * 180.0 / pi;

        if(fabs(angle)<spot_lights[i]->getAngle()){
            // cast a incident ray from the light to the intersection point
            ray incidentRay = ray(light_position, light_direction);
            ray normal = getNormalAt(intersection, incidentRay);

            // avoid self recursion
            double dist = (intersection - light_position).length();
            if(dist < 0.00001) continue;

            // check if the light is blocked by any object
            bool blocked = false;
            for(object *o : objects)
            {
                if(o == this) continue;
                double t = o->findIntersection(incidentRay, col, 0);
                if(t > 0 && t+0.00001 < dist)
                {
                    blocked = true;
                    break;
                }
            }
            
            if(!blocked)
            {
                double lambert = max(0.0,  incidentRay.getDirection()*normal.getDirection()*(-1));
                ray reflectionRay = ray(intersection, incidentRay.getDirection() - normal.getDirection() * 2 * (incidentRay.getDirection()*normal.getDirection()));
                double phong = max(0.0, reflectionRay.getDirection()*r.getDirection()*(-1));
                // update diffuse and specular 
                col.r += (intersection_color.r * diffuse * lambert + spot_lights[i]->getPointLight().getColor().r);
                col.g += (intersection_color.g * diffuse * lambert + spot_lights[i]->getPointLight().getColor().g);
                col.b += (intersection_color.b * diffuse * lambert + spot_lights[i]->getPointLight().getColor().b);

                col.r += (spot_lights[i]->getPointLight().getColor().r * specular * pow(phong, shininess)*intersection_color.r);
                col.g += (spot_lights[i]->getPointLight().getColor().g * specular * pow(phong, shininess)*intersection_color.g);
                col.b += (spot_lights[i]->getPointLight().getColor().b * specular * pow(phong, shininess)*intersection_color.b);

            }
        }
      
    }
    if(depth< recursion_depth){
        ray normal = getNormalAt(intersection, r);
        ray reflectionRay = ray(intersection, r.getDirection() - normal.getDirection() * 2 * (r.getDirection()*normal.getDirection()));
        reflectionRay.setOrigin(reflectionRay.getOrigin() + reflectionRay.getDirection() * 0.00001);

        int index = -1;
        double min_t = 99999999;
        double t = -1; 
        for(int i=0; i<(int)objects.size(); i++)
        {
            t = objects[i]->intersect(reflectionRay, col, 0);
            if(t > 0 && t < min_t)
            {
                min_t = t;
                index = i;
            }
        }
        
        if(index != -1)
        {
            color reflection_color = color();
            t = objects[index]->intersect(reflectionRay, reflection_color, depth+1);
            col.r += reflection_color.r * reflection;
            col.g += reflection_color.g * reflection;
            col.b += reflection_color.b * reflection;
        }
    }
    return t;
}


// destructor
object::~object()
{
}