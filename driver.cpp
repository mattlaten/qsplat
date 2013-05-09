#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
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
// Function Declarations 
// ----------------------------------//
void init(int, char*[]);
void keyboard(unsigned char, int, int);
void resize(int, int);
void display(void);


//-----------------------------------//
// Helper Functions 
// ----------------------------------//

double max(double a, double b) {
    if (a > b) return a;
    return b;
}

double min(double a, double b) {
    return (a+b) - max(a,b);
}

float toRadians(float deg) {
    return float(2*PI*deg/360.0);
}

float toDegrees(float rad) {
    return float(360.0*rad/(2*PI));
}

using namespace std;

ply_reader ply;
splat_model model;


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
    
    //glEnable(GL_POINT_SMOOTH);

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
            phi = max(phi-diff,0.1);
        break;
        case 's':
            phi = min(phi+diff,PI); 
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
        default:
        break;
    }
    cam_pos.x = r*cos(theta)*sin(phi);
    cam_pos.y = r*cos(phi);
    cam_pos.z = r*sin(phi)*sin(theta);

}

void resize(int w, int h) {
    cout << "resizing" << endl;
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
    
    for (vector<splat>::iterator s = model.splats.begin(); s != model.splats.end(); ++s) {
        glPointSize(s->size*3.5*window_width/(s->center-cam_pos).mag());
        if (s->normal.dot(cam_pos) < 0)
            continue;
        glBegin(GL_POINTS);
            glNormal3f(s->normal.x, s->normal.y, s->normal.z);
            glVertex3f(s->center.x, s->center.y, s->center.z);
        glEnd();
    }

    glutSwapBuffers();
    t = clock()-t;
    char buff[100];
    sprintf(buff, "%s: %.2ffps", WINDOW_TITLE_PREFIX, fps);
    glutSetWindowTitle(buff);
    fps = 1000/(float)t;
    //cout << fps << endl;
}

int main(int argc, char* argv[]) {
    ply.read("bunny/reconstruction/bun_zipper.ply", model);        
    cout << model.min_val.x << " " << model.min_val.y << " " << model.min_val.z << endl;
    cout << model.max_val.x << " " << model.max_val.y << " " << model.max_val.z << endl;
    init(argc, argv);
    glutMainLoop();
    exit(EXIT_SUCCESS);
    return 0;
}
