#include "1905095_checkerBoard.h"
#include "bitmap_image.hpp" 
#include <GL/glut.h>

#include<bits/stdc++.h>
using namespace std;

bool drawCheckerBoard; 
bool drawAxes; 

double cameraHeight;
double cameraAngle;
double angle; 

int recursion_depth; 
int pictureWidth;
int pictureHeight;

bitmap_image picture; 

vector<object*> objects;
vector<pointLight*> point_lights;
vector<spotLight*> spot_lights;

vectorPoint3D cameraPos(100,0,5);
vectorPoint3D cameraUp(0,0,1);
vectorPoint3D cameraRight(-1/sqrt(2),1/sqrt(2),0);
vectorPoint3D cameraLookAt(-1/sqrt(2),-1/sqrt(2),0);

double viewWidth = 500;
double viewHeight = 500;
double viewAngle = 90;
double noOfSegments; 

int noOfObjects;
int pictureNo = 1; 
void drawAxesFunc()
{
    if(drawAxes){
        glBegin(GL_LINES);

        glColor3f(1, 0, 0);

        glVertex3f(100, 0, 0);
        glVertex3f(-100, 0, 0);

        glColor3f(0, 1, 0);

        glVertex3f(0, -100, 0);
        glVertex3f(0, 100, 0);

        glColor3f(0, 0, 1);

        glVertex3f(0, 0, 100);
        glVertex3f(0, 0, -100);

        glEnd();
    }
}

void drawCheckerBoardFunc()
{
    if(drawCheckerBoard){
        glColor3f(0.5,0.5,0.5); 
        glBegin(GL_LINES);
        for(int i=-8; i<=8; i++){
            if(i==0) continue;
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10, 90, 0);

            glVertex3f(-90, i*10, 0);
            glVertex3f(90, i*10, 0);
        }
        glEnd();
    }
}

void rotateCamera(vectorPoint3D &v,vectorPoint3D &axis, double angle){
    v = v*cos(angle) + (axis^v)*sin(angle); 
}

void capture(){
    cout << "SS Taken" << endl;

    for(int i=0; i<pictureWidth; i++){
        for(int j=0; j<pictureHeight; j++){
            picture.set_pixel(i, j, 0, 0, 0);
        }
    }

    double tanX = tan((pi*viewAngle)/(2*180.0));
    double planeDistance = (viewHeight/2.0)/tanX;

    vectorPoint3D topLeft = cameraPos + cameraLookAt*planeDistance - cameraRight*(viewWidth/2.0) + cameraUp*(viewHeight/2.0);

    double du = viewWidth/(1.0*pictureWidth);
    double dv = viewHeight/(1.0*pictureHeight);

    // mid of the pixel
    topLeft = topLeft + cameraRight*(du/2.0) - cameraUp*(dv/2.0);

    int objIndex = -1; 
    double t_min;
    double t;

    for(int i=0; i<pictureWidth; i++){
        for(int j=0; j<pictureHeight; j++){
            vectorPoint3D P = topLeft + cameraRight*i*du - cameraUp*j*dv;
            ray r = ray(cameraPos, P - cameraPos);
            color col = color(0, 0, 0);
            t_min = -1;
            objIndex = -1;
            for(int k=0; k<(int)objects.size(); k++){
                t = objects[k]->intersect(r, col, 0);
                if(t>0 && (t<t_min || objIndex == -1)){
                    t_min = t;
                    objIndex = k;
                }
            }
            if(objIndex != -1){
                col = color(0, 0, 0);
                double t = objects[objIndex]->intersect(r, col, 1);
                if(col.r > 1) col.r = 1;
                if(col.g > 1) col.g = 1;
                if(col.b > 1) col.b = 1;

                if(col.r < 0) col.r = 0;
                if(col.g < 0) col.g = 0;
                if(col.b < 0) col.b = 0;

                picture.set_pixel(i, j, col.r*255, col.g*255, col.b*255);
            }
        }
    }

    picture.save_image("Output_1"+ to_string(pictureNo) + ".bmp");
    pictureNo++;
    cout << "SS Saved" << endl;
}

void keyboardListener(unsigned char key, int x,int y){
    switch(key){

        case '1':
            // rotate left 
            rotateCamera(cameraRight, cameraUp, angle);
            rotateCamera(cameraLookAt, cameraUp, angle);
            break;
        case '2':
            // rotate right
            rotateCamera(cameraRight, cameraUp, -angle);
            rotateCamera(cameraLookAt, cameraUp, -angle);
            break;
        case '3':
            // rotate up
            rotateCamera(cameraUp, cameraRight, angle);
            rotateCamera(cameraLookAt, cameraRight, angle);
            break;
        case '4':
            // rotate down
            rotateCamera(cameraUp, cameraRight, -angle);
            rotateCamera(cameraLookAt, cameraRight, -angle);
            break;
        case '5':
            // tilt clockwise
            rotateCamera(cameraRight, cameraLookAt, angle);
            rotateCamera(cameraUp, cameraLookAt, angle);
            break;
        case '6':
            // tilt anti-clockwise
            rotateCamera(cameraRight, cameraLookAt, -angle);
            rotateCamera(cameraUp, cameraLookAt, -angle);
            break;
        
        case '0':
            capture();
            break;
        default:
            break;
    }
}

void specialKeyListener(int key, int x,int y){
    switch(key){
        case GLUT_KEY_DOWN:		//down arrow key
            cameraPos = cameraPos - cameraLookAt*3;
            break;
        case GLUT_KEY_UP:		// up arrow key
            cameraPos = cameraPos + cameraLookAt*3;
            break;

        case GLUT_KEY_RIGHT:
            cameraPos = cameraPos + cameraRight*3;
            break;
        case GLUT_KEY_LEFT:
            cameraPos = cameraPos - cameraRight*3;
            break;

        case GLUT_KEY_PAGE_UP:
            cameraPos = cameraPos + cameraUp*3;
            break;
        case GLUT_KEY_PAGE_DOWN:
            cameraPos = cameraPos - cameraUp*3;
            break;

        case GLUT_KEY_INSERT:
            break;

        case GLUT_KEY_HOME:
            break;
        case GLUT_KEY_END:
            break;

        default:
            break;
    }
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
                drawAxes = !drawAxes;
            }
            break;

        case GLUT_RIGHT_BUTTON:
            //........
            break;
        case GLUT_MIDDLE_BUTTON:
            //........
            break;

        default:
            break;
    }
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(cameraPos.getX(), cameraPos.getY(), cameraPos.getZ(), cameraPos.getX() + cameraLookAt.getX(), cameraPos.getY() + cameraLookAt.getY(), cameraPos.getZ() + cameraLookAt.getZ(), cameraUp.getX(), cameraUp.getY(), cameraUp.getZ());

    glMatrixMode(GL_MODELVIEW);

    drawAxesFunc();
    drawCheckerBoardFunc();

    for(int i=0; i<(int)objects.size(); i++){
        object *obj = objects[i];
        obj->draw();
    }
    for(int i=0; i<(int)point_lights.size(); i++){
        point_lights[i]->drawPointLight();
    }
    for(int i=0; i<(int)spot_lights.size(); i++){
        spotLight* sl = spot_lights[i];
        sl->drawSpotLight();
    }

    glutSwapBuffers();
}

void animate(){
    glutPostRedisplay();
}

void loadData(){
    ifstream sceneFile;
    // output file
    ofstream outputFile;
    outputFile.open("Output_1.txt");
    sceneFile.open("scene.txt");
    sceneFile >> recursion_depth; 
    sceneFile >> pictureHeight; 
    pictureWidth = pictureHeight;

    outputFile<<recursion_depth<<" "<<pictureHeight<<endl;

    int noOfObjects;
    sceneFile >> noOfObjects;

    outputFile<<noOfObjects<<endl;

    for(int i=0; i<noOfObjects; i++){
        string objectType;
        sceneFile >> objectType;

        outputFile<<objectType<<endl; 

        object *obj; 
        if(objectType == "sphere"){
            obj = new sphere();
            sceneFile >> *((sphere*)obj); 
            outputFile<<*((sphere*)obj)<<endl;
        }
        else if(objectType == "triangle"){
            obj = new triangle();
            sceneFile >> *((triangle*)obj); 
            outputFile<<*((triangle*)obj)<<endl;
        }
        else if(objectType == "general"){
            obj = new general();
            sceneFile >> *((general*)obj); 
        }
        else {
            cout << "Invalid object type" << endl;
        }

        objects.push_back(obj);
    }

    int noOfpoint_lights;
    sceneFile >> noOfpoint_lights;
    outputFile<<noOfpoint_lights<<endl;
    for(int i=0; i<noOfpoint_lights; i++){
        pointLight *pl = new pointLight();
        sceneFile >> *pl;
        outputFile<<*pl<<endl;
        point_lights.push_back(pl);
    }

    int noOfspot_lights;
    sceneFile >> noOfspot_lights;
    outputFile<<noOfspot_lights<<endl;
    for(int i=0; i<noOfspot_lights; i++){
        spotLight *sl = new spotLight();
        sceneFile >> *sl;
        outputFile<<*sl<<endl;
        spot_lights.push_back(sl);
    }

    object *cb = new checkerBoard(400,10); 
    cb->setColor(color(0.6,0.6,0.6));
    
    double ambient = 0.4;
    double diffuse = 0.2;
    double specular = 0.2;
    double reflection = 0.2; 
    
    cb->setAmbient(ambient);
    cb->setDiffuse(diffuse);
    cb->setSpecular(specular);
    cb->setReflection(reflection);

    objects.push_back(cb);

    sceneFile.close();

}

void init(){
    drawCheckerBoard = true;
    drawAxes = true;
    cameraHeight = 160.0;
    cameraAngle = 1.0;
    angle = 0;
    noOfSegments = 36; 
    loadData();
    picture = bitmap_image(pictureWidth, pictureHeight);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(viewAngle,1,0.1,1000.0);
}

int main(int argc, char **argv){
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("RTX Offline");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);
    glutMainLoop();

    objects.clear();
    objects.shrink_to_fit();
    point_lights.clear();
    point_lights.shrink_to_fit();
    spot_lights.clear();
    spot_lights.shrink_to_fit();
    return 0;
}