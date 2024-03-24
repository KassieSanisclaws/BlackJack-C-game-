#include "SDLOpenGLCoordinate.h"
#include "QuadGL.h"

void SDLOpenGLCoordinate::drawSDL(int x, int y, int width, int height, int windowWidth, int windowHeight)
{
    float ndcX = 2.0f * x / windowWidth - 1.0f;
    float ndcY = 1.0f - 2.0f * y / windowHeight;
    float ndcWidth = 2.0f * width / windowWidth;
    float ndcHeight = 2.0f * height / windowHeight;

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(ndcX, ndcY - ndcHeight);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(ndcX + ndcWidth, ndcY - ndcHeight);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(ndcX + ndcWidth, ndcY);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(ndcX, ndcY);

    glEnd();
}

float* SDLOpenGLCoordinate::createVertices(int x, int y, int width, int height, int windowWidth, int windowHeight)
{
    float* vertices = new float[32];

    float ndcX = 2.0f * x / windowWidth - 1.0f;
    float ndcY = 1.0f - 2.0f * y / windowHeight;
    float ndcWidth = 2.0f * width / windowWidth;
    float ndcHeight = 2.0f * height / windowHeight;

    vertices[0] = ndcX;
    vertices[1] = ndcY - ndcHeight;
    vertices[2] = 0.0f;

    vertices[3] = 1.0f;
    vertices[4] = 0.0f;
    vertices[5] = 0.0f;

    vertices[6] = 0.0f;
    vertices[7] = 1.0f;

    vertices[8] = ndcX + ndcWidth;
    vertices[9] = ndcY - ndcHeight;
    vertices[10] = 0.0f;

    vertices[11] = 0.0f;
    vertices[12] = 1.0f;
    vertices[13] = 0.0f;

    vertices[14] = 1.0f;
    vertices[15] = 1.0f;

    vertices[16] = ndcX + ndcWidth;
    vertices[17] = ndcY;
    vertices[18] = 0.0f;

    vertices[19] = 0.0f;
    vertices[20] = 0.0f;
    vertices[21] = 1.0f;

    vertices[22] = 1.0f;
    vertices[23] = 0.0f;

    vertices[24] = ndcX;
    vertices[25] = ndcY;
    vertices[26] = 0.0f;

    vertices[27] = 1.0f;
    vertices[28] = 1.0f;
    vertices[29] = 1.0f;

    vertices[30] = 0.0f;
    vertices[31] = 0.0f;

    return vertices;
}

QuadGL* SDLOpenGLCoordinate::generateQuad(int x, int y, int width, int height, int windowWidth, int windowHeight)
{
    float ndcX = 2.0f * x / windowWidth - 1.0f;
    float ndcY = 1.0f - 2.0f * y / windowHeight;
    float ndcWidth = 2.0f * width / windowWidth;
    float ndcHeight = 2.0f * height / windowHeight;

    VertexGL vertex[4];

    vertex[0].x = ndcX;
    vertex[0].y = ndcY - ndcHeight;
    vertex[0].z = 0.0f;

    vertex[0].r = 1.0f;
    vertex[0].g = 0.0f;
    vertex[0].b = 0.0f;
    vertex[0].a = 1.0f;

    vertex[0].tx = 0.0f;
    vertex[0].ty = 1.0f;


    vertex[1].x = ndcX + ndcWidth;
    vertex[1].y = ndcY - ndcHeight;
    vertex[1].z = 0.0f;

    vertex[1].r = 0.0f;
    vertex[1].g = 1.0f;
    vertex[1].b = 0.0f;
    vertex[1].a = 1.0f;

    vertex[1].tx = 1.0f;
    vertex[1].ty = 1.0f;


    vertex[2].x = ndcX + ndcWidth;
    vertex[2].y = ndcY;
    vertex[2].z = 0.0f;

    vertex[2].r = 0.0f;
    vertex[2].g = 0.0f;
    vertex[2].b = 1.0f;
    vertex[2].a = 1.0f;

    vertex[2].tx = 1.0f;
    vertex[2].ty = 0.0f;


    vertex[3].x = ndcX;
    vertex[3].y = ndcY;
    vertex[3].z = 0.0f;

    vertex[3].r = 1.0f;
    vertex[3].g = 1.0f;
    vertex[3].b = 1.0f;
    vertex[3].a = 1.0f;

    vertex[3].tx = 0.0f;
    vertex[3].ty = 0.0f;

    return new QuadGL(vertex);
}