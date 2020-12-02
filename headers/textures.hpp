#ifndef _TEXTURES_HPP_
#define _TEXTURES_HPP_

#include <GL/glut.h>
#include "image.h"

#define NUMBER_OF_TEXTURES 3
#define FILENAME0 "textures/blue.bmp"
#define FILENAME1 "textures/rose.bmp"
#define FILENAME2 "textures/green.bmp"

extern GLuint texture_names[NUMBER_OF_TEXTURES];

void load_textures();
void free_textures();

#endif
