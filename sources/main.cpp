#include <GL/glut.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cmath>
#include <cstdlib>

#include "../headers/pso.hpp"
#include "../headers/textures.hpp"
#include "../headers/write.hpp"

#define ESC 27
#define unused(x) ((void)x)
#define window_width (1000)
#define window_height (1000)
#define window_position (500)

static void register_callbacks(void);
static void on_keyboard(unsigned char, int, int);
static void on_display(void);
static void init(void);
static void window_init(int, char **);
static void on_reshape(int, int);
static void init_lights(void);

static int pso_param_1 = 3;
static double pso_param_2 = .5;

int main(int argc, char **argv)
{
    window_init(argc, argv);
    init();
    register_callbacks();
    load_textures();
    glutMainLoop();

    return 0;
}

static void window_init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(window_position, window_position);
    glutCreateWindow("Art scene");
}

static void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 1);
    // Needed for the fog
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_FOG);
    GLfloat fogColor[] = {0.3, 0.2, 0.5, 0};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, 0.03);
    glHint(GL_FOG_HINT, GL_NICEST);
}

static void register_callbacks(void)
{
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
}

static void on_keyboard(unsigned char key, int x, int y)
{
    unused(x);
    unused(y);

    switch (key)
    {
    case ESC:
        exit(0);
        break;
    case 'T':
    case 't':
        pso_param_1 += 1;
        break;
    case 'J':
    case 'j':
        pso_param_2 += 0.3;
        break;
    }
}

static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (float)width / height, 1, 50);
}

static void init_lights(void)
{
    // Setup colors
    const float ambient[] = {0.1, 0.1, 0.1, 1};
    const float diffuse[] = {0.7, 0.7, 0.7, 1};
    const float position[] = {1, 1, 1, 0};
    const float specular[] = {0.9, 0.9, 0.9, 1};
    // Setup 1st light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    // Setup 2nd light
    // This light makes colors warmer
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    // Camera setup
    glLoadIdentity();
    gluLookAt(0, 5, 5,
              0, 0, 0,
              1, 0, 0);
    init_lights();
    // Make the signature in right bottom corner
    draw_name("BY TIJANA JEVTIC", 200, 95);
    // Start the animation instance
    auto instance = new PSO();
    instance->start(pso_param_1, pso_param_2);

    glutPostRedisplay();
    glutSwapBuffers();
}
