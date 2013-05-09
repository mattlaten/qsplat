#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <GL/freeglut.h>
#include <iostream>
#include "ply_reader.h"

#define WINDOW_TITLE_PREFIX "OpenGL"


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
vertex cam_dir(0.0f, 0.0f, -1.0f);
vertex cam_pos(0.0f, 0.2f, 0.5f);


//-----------------------------------//
// Function Declarations 
// ----------------------------------//
void init(int, char*[]);
void keyboard(unsigned char, int, int);
void resize(int, int);
void display(void);

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
    //GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_direction[] = { 0.0, -1.0, 0.0, 0.0 };
    GLfloat light_ambient[] = { 0.0, 1.0, 0.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    //glEnable(GL_POINT_SMOOTH);

    //glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
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
        case 'a':
            cam_angle -= 0.01f;
            cam_dir.x = sin(cam_angle);
            cam_dir.z = -cos(cam_angle);
        break;
        case 'd':
            cam_angle += 0.01f;
            cam_dir.x = sin(cam_angle);
            cam_dir.z = -cos(cam_angle);
        break;
        case 'w':
            cam_pos.x += cam_dir.x*0.01;
            cam_pos.z += cam_dir.z*0.01;
        break;
        case 's':
            cam_pos.x -= cam_dir.x*0.01;
            cam_pos.z -= cam_dir.z*0.01;
        break;
        case 'r':
            cam_pos.y += 0.01;
        break;
        case 'f':
            cam_pos.y -= 0.01;
        break;
        default:
        break;
    }

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    glLoadIdentity();
    /*gluLookAt   (
                    cam_pos.x, cam_pos.y, cam_pos.z,
                    cam_dir.x, cam_dir.y, cam_dir.z,
                    0.0f, 1.0f, 0.0f
                );
    */
    gluLookAt   (
                    cam_pos.x, cam_pos.y, cam_pos.z,
                    0, 0, 0,
                    0.0f, 1.0f, 0.0f
                );

    glColor3f(1.0, 1.0, 1.0);
    //glPointSize(10.0f);
    
    for (vector<splat>::iterator s = model.splats.begin(); s != model.splats.end(); ++s) {
        glPointSize(s->size*2*window_width/(s->center-cam_pos).mag());
        //glPointSize(10.0f);
        glBegin(GL_POINTS);
            //cout << s->size << endl;
            glNormal3f(s->normal.x, s->normal.y, s->normal.z);
            glVertex3f(s->center.x, s->center.y, s->center.z);
            //cout << s->normal.x << endl;
            //cout << s->normal.mag() << endl;
        glEnd();
    }

    glutSwapBuffers();
}

int main(int argc, char* argv[]) {
    ply.read("bunny/reconstruction/bun_zipper.ply", model);        
    init(argc, argv);
    glutMainLoop();
    cout << "Herp derp" << endl;
    exit(EXIT_SUCCESS);
    return 0;
}
