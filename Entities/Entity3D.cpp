#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Entity3D.h"


namespace Entities
{

void Entity3D::setParamsFromEntity(int id)
{
}

void Entity3D::setVertices(QVector<float> vertices){
    _vertices = vertices;
}

void Entity3D::setNormals(QVector<float> normals){
    _normals = normals;
}

void Entity3D::setUVs(QVector<float> uvs){
    _uvs = uvs;
}

void Entity3D::setPolygons(QVector<int> polygons){
    _polygons = polygons;
}
void Entity3D::setUVIndices(QVector<int> uvIndices) {
    _uvIndices = uvIndices;
}
void Entity3D::setEdges(QVector<int> edges){
    _edges = edges;
}
void Entity3D::setTriangleFashion(bool isTriangle){
    _triangleFashion = isTriangle;
}

QVector<float> Entity3D::getVertices(){
    return _vertices;
}

QVector<int> Entity3D::getPolygons(){
    return _polygons;
}

QVector<float> Entity3D::getNormals(){
    return _normals;
}

QVector<int> Entity3D::getUVIndices(){
    return _uvIndices;
}
QVector<float> Entity3D::getUVs(){
    return _uvs;
}
QVector<int> Entity3D::getEdges(){
    return _edges;
}
bool Entity3D::isTriangleFashioned(){
    return _triangleFashion;
}

}  // namespace Entities


