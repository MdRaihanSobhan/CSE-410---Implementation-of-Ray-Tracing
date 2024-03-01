#include "1905095_spotLight.h"

class object; 

extern vector <pointLight*> point_lights;
extern vector <spotLight*> spot_lights;
extern vector <object*> objects;
extern int recursion_depth;

class object
{
public: 
    pointLight ref_point; 
    double height, width, length;
    color clr;
    double ambient, diffuse, specular, reflection, refraction; 
    int shininess;
};
