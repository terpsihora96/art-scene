#include <GL/glut.h>
#include <iostream>

// Function for drawing string name on the screen
// The position is controlled by double x, double y parameters
void draw_name(std::string name, double x, double y)
{
    int current_width = glutGet(GLUT_WINDOW_WIDTH);
    int current_height = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    gluOrtho2D(0.0, current_width, current_height, 0.0);

    glRasterPos2i(current_width - x, current_height - y);
    for (char letter : name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
