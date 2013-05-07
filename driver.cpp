#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <GL/freeglut.h>
#include <iostream>
#include "ply_reader.h"

#define WINDOW_TITLE_PREFIX "OpenGL"

int CurrentWidth = 800,
    CurrentHeight = 600,
    WindowHandle = 0;

void init(int, char*[]);
void resize(int, int);
void display(void);

using namespace std;

ply_reader ply;
splat_model model;


void init(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(CurrentWidth, CurrentHeight);
    glutInitWindowPosition(100,100);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);
    if (WindowHandle < 1) {
        //log.err("Couldn't create window");
        exit(EXIT_FAILURE);
    }

    glClearColor (0.0, 0.0, 0.0, 0.0);

    //glMatrixMode(GL_PROJECTION);
    //gluPerspective(45, 1, 1, 100);
    //glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0,0,10,0,0,0,0,1,0);
    
    /*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(resize);
    glutReshapeWindow(800,600);
    
    cout << "OpenGL Version:" << endl;
    cout << glGetString(GL_VERSION) << endl;
    
} 

void resize(int Width, int Height) {
    CurrentWidth = Width;
    CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    
    for (vector<splat>::iterator s = model.splats.begin(); s != model.splats.end(); ++s) {
        glVertex3f(s->center.x, s->center.y, s->center.z);
    }
    glEnd();
    glFlush();
}

int main(int argc, char* argv[]) {
    ply.read("bunny/reconstruction/bun_zipper.ply", model);        
    init(argc, argv);
    glutMainLoop();
    cout << "Herp derp" << endl;
    exit(EXIT_SUCCESS);
    return 0;
}
