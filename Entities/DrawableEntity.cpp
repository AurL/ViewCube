#include "DrawableEntity.h"

DrawableEntity::DrawableEntity()
{
}

void DrawableEntity::initialize(Entities::Entity3D entity){
//Utiliser des iterators
    QVector<float> vertLst;
    QVector<int> polyLst;
    QVector<int> edgesLst;
    QVector<float> normLst;

    float maxX =-9999, maxY=-9999, maxZ=-9999, minX=+9999, minY=+9999, minZ=+9999;
    vertLst = entity.getVertices();
    polyLst = entity.getPolygons();
    edgesLst = entity.getEdges();
    normLst = entity.getNormals();

    this->drawCount = polyLst.count();
    this->edgesCount = edgesLst.count();
    this->vertCount = vertLst.count();

    //Memory allocation
    this->vertices = (GLfloat*)malloc(sizeof(GLfloat)*vertLst.count());
    this->polygons = (GLuint*)malloc(sizeof(GLuint) * polyLst.count());
    this->colors = (GLfloat*)malloc(sizeof(GLfloat)*vertLst.count()*4);
    this->edges = (GLuint*)malloc(sizeof(GLuint) * edgesLst.count());
    this->normals = (GLfloat*)malloc(sizeof(GLfloat) *normLst.count());
    //From QVector to arrays
    for(int i=0;i<vertLst.count();i++){
        vertices[i] = vertLst.at(i);
        // case X
        if(i%3==0){
            if(vertices[i]> maxX)
                maxX = vertices[i];
            if(vertices[i]< minX)
                minX = vertices[i];
        }
        if(i%3==1){
            if(vertices[i]> maxY)
                maxY = vertices[i];
            if(vertices[i]< minY)
                minY = vertices[i];
        }
        if(i%3==2){
            if(vertices[i]> maxZ)
                maxZ = vertices[i];
            if(vertices[i]< minZ)
                minZ = vertices[i];
        }
    }
    centerX = (abs(maxX) - abs(minX))/2;
    centerY = (abs(maxY) - abs(minY))/2;
    centerZ = (abs(maxZ) - abs(minZ))/2;

    for(int i=0;i<polyLst.count();i++){
        polygons[i] = polyLst.at(i);
    }
    for(int i=0;i<edgesLst.count() ; i++) {
        edges[i] = edgesLst.at(i);
    }
    for(int i=0;i<normLst.count() ; i++) {
        normals[i] = normLst.at(i);
    }
    //Temporary color filler
    for(int i=0;i<vertLst.count();i+=4){
       if(i/3%3==1){
           colors[i]=0;
           colors[i+1]=1.0;
           colors[i+2]=0.0;
       }else if(i/3%3==2){
           colors[i]=0.0;
           colors[i+1]=0.0;
           colors[i+2]=1.0;}
       else{
           colors[i]=1.0;
           colors[i+1]=0.0;
           colors[i+2]=0.0;
       }
    }
    this->trianglesFashion = false;
    yRot = 90;
    zRot = 90;
}

void DrawableEntity::setPosition(float x, float y, float z)
{
         xPos=x;
         yPos=y;
         zPos=z;
 }
