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
    int stacks = 30; 
    int slices = 30;

    vectorPoint3D points[100][100];
    double h, r;
    for(int i=0; i<=stacks; i++)
    {
        h = length * sin( (double)i/stacks * pi/2);
        r = length * cos( (double)i/stacks * pi/2);
        for(int j=0; j<=slices; j++)
        {
            points[i][j].x = r * cos( (double)j/slices * 2*pi);
            points[i][j].y = r * sin( (double)j/slices * 2*pi);
            points[i][j].z = h;
        }
    }

    for(int i=0; i<stacks; i++)
    {
        glPushMatrix();
        glTranslatef(ref_point.x, ref_point.y, ref_point.z);
        glColor3f(clr.r, clr.g, clr.b);
        for(int j=0; j<slices; j++)
        {
            glBegin(GL_QUADS);
            //upper hemisphere
            glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
            glVertex3f(points[i][j+1].x, points[i][j+1].y, points[i][j+1].z);
            glVertex3f(points[i+1][j+1].x, points[i+1][j+1].y, points[i+1][j+1].z);
            glVertex3f(points[i+1][j].x, points[i+1][j].y, points[i+1][j].z);
            
            //lower hemisphere
            glVertex3f(points[i][j].x, points[i][j].y, -points[i][j].z);
            glVertex3f(points[i][j+1].x, points[i][j+1].y, -points[i][j+1].z);
            glVertex3f(points[i+1][j+1].x, points[i+1][j+1].y, -points[i+1][j+1].z);
            glVertex3f(points[i+1][j].x, points[i+1][j].y, -points[i+1][j].z);
            glEnd();
        }
        glPopMatrix();

    }
}

double sphere::findIntersection(ray r, color &col, int depth)
{
    r.origin = r.origin - ref_point;
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

    if(t1>t2) swap(t1, t2);
    if(t1>0) return t1;
    else if (t2>0) return t2;
    else return -1;
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