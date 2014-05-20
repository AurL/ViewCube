#ifndef ENTITIES_ENTITY3_D_H
#define ENTITIES_ENTITY3_D_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <QList>
#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include "Entities/Entity.h"


namespace Entities
{
class Entity3D : public Entity
{
private:
    QVector<float> _vertices;
    QVector<int> _edges;
    QVector<float> _normals;
    QVector<float> _uvs;
    QVector<int> _uvIndices;
    QVector<int> _polygons;

    bool _triangleFashion;


public:
	void setParamsFromEntity(int id);
    void setVertices(QVector<float> vertices);
    void setNormals(QVector<float> normals);
    void setPolygons(QVector<int> polygons);
    void setUVs(QVector<float> uvs);
    void setUVIndices(QVector<int> uvIndices);
    void setEdges(QVector<int> edges);
    void setTriangleFashion(bool isTriangle);

    QVector<float> getVertices( );
    QVector<float> getNormals();
    QVector<float> getUVs();
    QVector<int> getPolygons();
    QVector<int> getUVIndices();
    QVector<int> getEdges();
    bool isTriangleFashioned();

};

}  // namespace Entities

#endif
