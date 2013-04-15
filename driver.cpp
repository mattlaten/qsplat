#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include <iostream>
#define WINDOW_TITLE_PREFIX "OpenGL"

int CurrentWidth = 800,
    CurrentHeight = 600,
    WindowHandle = 0;

void init(int, char*[]);
void initWindow(int, char*[]);
void resizeFunction(int, int);
void renderFunction(void);


using namespace std;

int main(int argc, char* argv[]) {
    init(argc, argv);
    glutMainLoop();
    exit(EXIT_SUCCESS);
    return 0;
}

void init(int argc, char* argv[]) {
    initWindow(argc, argv);
    cout << "INFO: OpenGL version: " << glGetString(GL_VERSION) << endl;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void initWindow(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);    

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, 
            GLUT_ACTION_GLUTMAINLOOP_RETURNS);


    glutInitWindowSize(CurrentWidth, CurrentHeight);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

    if (WindowHandle < 1) {
        cout << "ERROR: Something went wrong" << endl;
        exit(EXIT_FAILURE);
    }

    glutReshapeFunc(resizeFunction);
    glutDisplayFunc(renderFunction);
} 

void resizeFunction(int Width, int Height) {
    CurrentWidth = Width;
    CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void renderFunction(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
    glutPostRedisplay();
}



