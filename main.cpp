//COMPILE FUNCTION: g++ -o main -Wall main.cpp -mwindows glut32.lib -lopengl32 -lglu32

#include <stdio.h>
//#include <iostream>
#include <windows.h>
#include "GL/glut.h"
#include <math.h>
#include <stdlib.h>
#define xpix 500
#include <cstring>
using namespace std;
#define pi 3.142857

// Function that exits from program
void keyboard(unsigned char key,
              int x, int y)
{
    switch (key) {
    case 27:
        glutHideWindow();
    }
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((x + y) % 2 == 1) {
                glColor3f(1.0, 1.0, 1.0);
            } else {
                glColor3f(0, 0, 0);
            }

            glBegin(GL_POLYGON);
            glVertex2f(-(x/10), -(y/10));
            glVertex2f(-(x/10), (y/10));
            glVertex2f((x/10), (y/10));
            glVertex2f((x/10), -(y/10));
            glEnd();
        }
    }
    
    glFlush();
}

void init() 
{
    glClearColor(0.000, 0.110, 0.392, 0.0); // JMU Gold

    glColor3f(0.314, 0.314, 0.000); // JMU Purple

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Chess");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}