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
void initWindow(int, char*[]);
void resize(int, int);
void display(void);

using namespace std;

ply_reader ply;
splat_model model;

int main(int argc, char* argv[]) {
    ply.read("bunny/reconstruction/bun_zipper.ply", model);        
    init(argc, argv);
    glutMainLoop();
    exit(EXIT_SUCCESS);
    return 0;
}

void init(int argc, char* argv[]) {
    initWindow(argc, argv);
    //log.info("OpenGL version:");
    cout << glGetString(GL_VERSION) << endl;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void initWindow(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitContextVersion(3, 3);
    //glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    //glutInitContextProfile(GLUT_CORE_PROFILE);    
    //glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    glutInitWindowSize(CurrentWidth, CurrentHeight);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);

    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

    if (WindowHandle < 1) {
        //log.err("Couldn't create window");
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(display);
} 

void resize(int Width, int Height) {
    CurrentWidth = Width;
    CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, 1, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0,0,10,0,0,0,0,1,0);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POINTS);
    for (vector<splat>::iterator s = model.splats.begin(); s != model.splats.end(); ++s) {
        glVertex3f(s->center.x, s->center.y, s->center.z);
        glColor3d(1,0,0);
        glVertex3f(0,0,0);
    }
    glEnd();
    glFlush();
}



