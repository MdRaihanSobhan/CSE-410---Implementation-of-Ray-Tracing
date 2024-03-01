#include "1905095_object.h"

class general : public object {
public:
    double a, b, c, d, e, f, g, h, i, j;
    general(); 
    virtual void draw();
    virtual ray getNormalAt(vectorPoint3D intersection_point, ray incident);
    virtual double findIntersection(ray r, color &col, int depth);
    bool checkInside(vectorPoint3D point);

    //input stream
    friend istream &operator>>(istream &is, general &g);

    // destructor
    ~general();
};

general::general()
{
}

void general::draw()
{
    return; // do nothing
}

ray general::getNormalAt(vectorPoint3D intersection_point, ray incident)
{
    double x = 2*a*intersection_point.getX() + d*intersection_point.getY() + e*intersection_point.getZ() + g;
    double y = 2*b*intersection_point.getY() + d*intersection_point.getX() + f*intersection_point.getZ() + h;
    double z = 2*c*intersection_point.getZ() + e*intersection_point.getX() + f*intersection_point.getY() + i;

    return ray(intersection_point, vectorPoint3D(x, y, z));

}

double general::findIntersection(ray r, color &col, int depth)
{
    double x0 = r.getOrigin().getX();
    double y0 = r.getOrigin().getY();
    double z0 = r.getOrigin().getZ();

    double xd = r.getDirection().getX();
    double yd = r.getDirection().getY();
    double zd = r.getDirection().getZ();

    double A = a*xd*xd + b*yd*yd + c*zd*zd + d*xd*yd + e*xd*zd + f*yd*zd;
    double B = 2*a*x0*xd + 2*b*y0*yd + 2*c*z0*zd + d*(x0*yd + y0*xd) + e*(x0*zd + z0*xd) + f*(y0*zd + z0*yd) + g*xd + h*yd + i*zd;
    double C = a*x0*x0 + b*y0*y0 + c*z0*z0 + d*x0*y0 + e*x0*z0 + f*y0*z0 + g*x0 + h*y0 + i*z0 + j;

    double discriminant = B*B - 4*A*C;
    if(discriminant<0) return -1;
    if(fabs(A) < 0.00001){
        return -C/B;
    }
    double t1 = (-B - sqrt(discriminant))/(2*A);
    double t2 = (-B + sqrt(discriminant))/(2*A);

    if(t1<0 && t2<0) return -1;
    if(t1 > t2) swap(t1, t2);
    if(t1>0){
        vectorPoint3D intersection = r.getOrigin() + r.getDirection() * t1;
        if(checkInside(intersection)) return t1;
    }
    if(t2>0){
        vectorPoint3D intersection = r.getOrigin() + r.getDirection() * t2;
        if(checkInside(intersection)) return t2;
    }
    return -1;
}

bool general::checkInside(vectorPoint3D point)
{
    if(fabs(length)>0.00001){
        if(point.getX() < ref_point.getX() || point.getX() > ref_point.getX() + length) return false;
    }
    if(fabs(width)>0.00001){
        if(point.getY() < ref_point.getY() || point.getY() > ref_point.getY() + width) return false;
    }
    if(fabs(height)>0.00001){
        if(point.getZ() < ref_point.getZ() || point.getZ() > ref_point.getZ() + height) return false;
    }
    return true;
}

istream &operator>>(istream &is, general &g)
{
    is >> g.a >> g.b >> g.c >> g.d >> g.e >> g.f >> g.g >> g.h >> g.i >> g.j;
    is>> g.ref_point >> g.length >> g.width >> g.height >> g.clr >> g.ambient >> g.diffuse >> g.specular >> g.reflection >> g.shininess;
    return is;
}

general::~general()
{
}