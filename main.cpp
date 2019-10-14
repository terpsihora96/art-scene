#include <GL/glut.h>
#include <string>
#include <iostream>

#include "./headers/pso.hpp"

#define ESC 27
#define unused(x) ((void) x)
#define size 0.1

static void init(void);
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
    
    //init();
    register_callbacks();

    glutMainLoop();

	return 0;
}

static void register_callbacks() {
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display); 
}

static void init(void) 
{
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 30.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
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

