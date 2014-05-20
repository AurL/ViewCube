#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

#include <GL/glu.h>
#include "Entities/Entity3D.h"

class DrawableEntity
{

public:
    GLfloat *vertices;
    GLuint *polygons;
    GLuint *edges;
    GLfloat *normals;
    GLuint drawCount;
    GLfloat *colors;
    GLuint vertCount;
    GLuint edgesCount;
    float centerX, centerY, centerZ;
    bool trianglesFashion;

    float xPos, yPos, zPos;
    float xRot, yRot, zRot;
    float xScale, yScale, zScale;

    void initialize(Entities::Entity3D);
    void setPosition(float, float, float);

public:
    DrawableEntity();
};

#endif // DRAWABLEENTITY_H
