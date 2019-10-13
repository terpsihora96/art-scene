#include <GL/glut.h>
#include <string>
#include <iostream>

#include "./headers/pso.hpp"

#define ESC 27
#define unused(x) ((void) x)
#define size 0.1

static void register_callbacks();
static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Art scene");
    
    register_callbacks();

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

	return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{   
    unused(x);
    unused(y);
    
    switch (key) {
    case ESC:
        exit(0);
        break;
    }
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PSO().start();
    glutPostRedisplay();
    glutSwapBuffers();
}

static void register_callbacks() {
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display); 
}
