#include "1905095_triangle.h" 

class sphere : public object{
public:
    sphere();
    sphere(vectorPoint3D center, double radius);
    virtual ray getNormalAt(vectorPoint3D point, ray incident);
    virtual void draw();
    virtual double findIntersection(ray r, color &col, int depth);

    // input stream
    friend istream& operator>>(istream& is, sphere& s);
    // output stream
    friend ostream& operator<<(ostream& os, sphere& s);
    // destructor
    ~sphere();
}; 

sphere::sphere()
{

}

sphere::sphere(vectorPoint3D center, double radius)
{
    ref_point = center;
    length = radius;
}

ray sphere::getNormalAt(vectorPoint3D point, ray incident)
{
    vectorPoint3D normal = point - ref_point;
    normal.normalize();
    return ray(point, normal);
}

void sphere::draw()
{
    glPushMatrix();
    glTranslatef(ref_point.getX(), ref_point.getY(), ref_point.getZ());
    glutWireSphere(length, 30, 20);
    glPopMatrix();
}

double sphere::findIntersection(ray r, color &col, int depth)
{
    r.setOrigin(r.getOrigin() - ref_point);
    double a = 1; 
    double b = 2* (r.getDirection() * r.getOrigin());
    double c = r.getOrigin() * r.getOrigin() - length*length;
    double discriminant = b*b - 4*a*c;
    if(discriminant < 0) return -1;

    if(fabs(a) < 0.00001){
        return -c/b;
    }

    double t1 = (-b - sqrt(discriminant))/(2*a);
    double t2 = (-b + sqrt(discriminant))/(2*a);

    if(t1 < 0 && t2 < 0) return -1;
    if(t1 > t2) swap(t1, t2);
    if(t1 > 0){
        return t1;
    }
    else{
        return t2;
    }
}

istream& operator>>(istream& is, sphere& s)
{
    is >> s.ref_point >> s.length;
    is>>s.clr; 
    is >> s.ambient >> s.diffuse >> s.specular>> s.reflection >> s.shininess;
    return is;
}

ostream& operator<<(ostream& os, sphere& s)
{
    os << "sphere" << endl;
    os << s.ref_point << " " << s.length << endl;
    os << s.clr.r<<" "<<s.clr.g<<" "<<s.clr.b<<endl;
    os << s.ambient << " " << s.diffuse << " " << s.specular << " " << s.reflection << " " << s.shininess << endl;
    return os;
}

sphere::~sphere()
{
    
}