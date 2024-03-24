#pragma once

#include "SDL.h"
#include "SDL_opengl.h"

#include "VertexGL.h"

class QuadGL
{
public:
    QuadGL(VertexGL v[4])
    {
        for (int i = 0; i < 4; ++i) 
        {
            x[i] = v[i].x;
            y[i] = v[i].y;
            z[i] = v[i].z;
            
            r[i] = v[i].r;
            g[i] = v[i].g;
            b[i] = v[i].b;
            a[i] = v[i].a;
            
            tx[i] = v[i].tx;
            ty[i] = v[i].ty;
        }
    }

    GLfloat x[4];
    GLfloat y[4];
    GLfloat z[4];
    GLfloat r[4];
    GLfloat g[4];
    GLfloat b[4];
    GLfloat a[4];
    GLfloat tx[4];
    GLfloat ty[4];
};