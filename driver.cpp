#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include "pre_processor.h"
#include "ply_reader.h"

#define WINDOW_TITLE_PREFIX "QSplat"

const double PI = atan(1.0)*4;

//-----------------------------------//
// Window Variables
// ----------------------------------//
int window_width = 800,
    window_height = 600,
    WindowHandle = 0;

//-----------------------------------//
// Camera Variables 
// ----------------------------------//

float cam_angle = 0.0;
vertex cam_dir(0.0f, 0.0f, 0.0f);

float theta = 3*PI/4;
float phi = PI/4;
float r = 0.5;
float diff = PI/180;

vertex cam_pos(r*cos(theta)*sin(phi), r*cos(phi), r*sin(theta)*sin(phi));


//-----------------------------------//
// Clock Variables 
// ----------------------------------//

clock_t t;
float fps;

//-----------------------------------//
// Rendering Variables
//-----------------------------------//

double epsilon = 0.0;
double splat_diff = 0.001;
bool back_cull = true;
bool frust_cull = true;

//-----------------------------------//
// Function Declarations 
// ----------------------------------//
void init(int, char*[]);
void keyboard(unsigned char, int, int);
void resize(int, int);
void display(void);


//-----------------------------------//
// Helper Functions 
// ----------------------------------//

double fast_max(double a, double b) {
    if (a > b) return a;
    return b;
}

double fast_min(double a, double b) {
    return (a+b) - fast_max(a,b);
}

float toRadians(float deg) {
    return float(2*PI*deg/360.0);
}

float toDegrees(float rad) {
    return float(360.0*rad/(2*PI));
}

using namespace std;

ply_reader ply;
pre_processor pre;
splat_model model;
node * root;


void init(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100,100);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);
    if (WindowHandle < 1) {
        //log.err("Couldn't create window");
        exit(EXIT_FAILURE);
    }
    glClearColor (0.0, 0.0, 0.0, 0.0);


    //lighting
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_direction[] = { 0.0, -1.0, 0.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    cout << "OpenGL Version:" << endl;
    cout << glGetString(GL_VERSION) << endl;
    
} 

void keyboard(unsigned char key, int x, int y) {
    switch (key){
        case 27:
            exit(EXIT_SUCCESS);
        break;
        case 'w':
            phi = fast_max(phi-diff,0.1);
        break;
        case 's':
            phi = fast_min(phi+diff,PI); 
        break;
        case 'a':
            theta += diff;
        break;
        case 'd':
            theta -= diff;
        break;
        case 'r':
            r -= diff;
        break;
        case 'f':
            r += diff;
        break;
        case 'x':
            epsilon += splat_diff;
        break;
        case 'z':
            epsilon = fast_max(epsilon - splat_diff, 0);
        break;
        case 'c':
            back_cull = !back_cull;
        break;
        default:
        break;
    }
    cam_pos.x = r*cos(theta)*sin(phi);
    cam_pos.y = r*cos(phi);
    cam_pos.z = r*sin(phi)*sin(theta);

}

void resize(int w, int h) {
    if (h == 0) 
        h = 1;
    float ratio = w*1.0/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    window_width = w;
    window_height = h;
    glViewport(0, 0, window_width, window_height);
    gluPerspective(45,ratio,0.01,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int traverse(node * n)
{
    if (n->cone*back_cull + n->s.normal.dot(cam_pos) < 0 || n->s.size == 0) {
    //if (false) { 
        //cout << "DON'T DRAW" << endl;
        return 0;
    }
    else if (n->is_leaf()) {
        //cout << "RENDERING" << endl;
        if (!isnan(n->s.normal.mag())) {
            glPointSize(n->s.size*3.5*window_width/(n->s.center-cam_pos).mag());
            glBegin(GL_POINTS);
                glNormal3f(n->s.normal.x, n->s.normal.y, n->s.normal.z);
                glVertex3f(n->s.center.x, n->s.center.y, n->s.center.z);
            glEnd();
        }
        return 0;
    }
    else if (n->s.size < epsilon) {
        //cout << "RENDERING 2" << endl;
        if (!isnan(n->s.normal.mag())) {
            glPointSize(n->s.size*3.5*window_width/(n->s.center-cam_pos).mag());
            glBegin(GL_POINTS);
                glNormal3f(n->s.normal.x, n->s.normal.y, n->s.normal.z);
                glVertex3f(n->s.center.x, n->s.center.y, n->s.center.z);
            glEnd();
        }
        return 0;
    }
    else {
        //cout << "TRAVERSING" << endl;
        if (n->left != NULL) {
            //cout << "LEFT: " << n->left << endl;
            traverse(n->left);
        }
        if (n->right != NULL) {
            //cout << "RIGHT: " << n->right << endl;
            traverse(n->right);
        }
        return 0;
    }
}

void frustum(vertex pos, vertex dir, vertex up) {

}

void display(void) {
    t = clock();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    glLoadIdentity();
    gluLookAt   (
                    cam_pos.x, cam_pos.y, cam_pos.z,
                    0, 0, 0,
                    0.0f, 1.0f, 0.0f
                );

    glColor3f(1.0, 1.0, 1.0);
   
    //rendering
    traverse(root);


    glutSwapBuffers();
    t = clock()-t;
    char buff[100];
    sprintf(buff, "%s | %s | %.2ffps " , WINDOW_TITLE_PREFIX, back_cull? "Normal [C]one Based Culling" : "[C]onventional Backface Culling", fps);
    glutSetWindowTitle(buff);
    fps = 1000/(float)t;
    //cout << fps << endl;
}

int main(int argc, char* argv[]) {
    //ply.read("bunny/reconstruction/bun_zipper.ply", model);        
    string filename;
    cout << "Enter in filename:" <<  endl;
    cin >> filename; 
    //ply.read("dragon_recon/dragon_vrip.ply", model);        
    ply.read(filename, model);        
    root = pre.build_tree(model.splats.begin(), model.splats.end(), model.min_val, model.max_val);
    //cout << model.min_val.x << " " << model.min_val.y << " " << model.min_val.z << endl;
    //cout << model.max_val.x << " " << model.max_val.y << " " << model.max_val.z << endl;
    init(argc, argv);
    glutMainLoop();
    exit(EXIT_SUCCESS);
    return 0;
}
