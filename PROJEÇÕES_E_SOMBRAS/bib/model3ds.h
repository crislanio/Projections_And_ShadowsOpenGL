#ifndef MODEL3DS_H
#define MODEL3DS_H

#include <GL/glut.h>
#include <lib3ds/file.h>
#include <lib3ds/camera.h>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>
#include <lib3ds/material.h>
#include <lib3ds/matrix.h>
#include <lib3ds/vector.h>
#include <lib3ds/light.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <SDL/SDL_image.h>

#define	TEX_XSIZE	1024
#define	TEX_YSIZE	1024

//#define USE_SDL

class Model3DS
{

public:
    Model3DS(const char *name);
    ~Model3DS();
    void draw();
};

#endif // MODEL3DS_H
