#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Scene.h"


namespace Application
{

QVector<Entity3D> Scene::getObjects3D()
{
    return _entity3DLst;
}



void Scene::addCamera(Camera cam)
{
    this->_cameraLst.append(cam);
}

void Scene::addEntity2D(Entity2D entity){
    this->_entity2DLst.append(entity);
}

void Scene::addEntity3D(Entity3D entity){

    // Setting stats
   setNbVertices(getNbVertices() + entity.getVertices().count());
   setNbPolygons(getNbPolygons() + entity.getPolygons().count());
   setNbEdges(getNbEdges() + entity.getEdges().count());
   setNbObjects(getNbObjects() + 1);

   this->_entity3DLst.append(entity);
}

void Scene::addLight(Light light){
    this->_lightLst.append(light);
}

QVector<DrawableEntity> Scene::getDEntities3D(){
    return _dEntitiy3DLst;
}

void Scene::setDrawableScene()
{
    DrawableEntity current;

    foreach(Entity3D entity, _entity3DLst){
        current.initialize(entity);
        this->_dEntitiy3DLst.append(current);
    }
}

void Scene::setNbVertices(int nbVertices){
    _nbVertices = nbVertices;
}

void Scene::setNbPolygons(int nbPolygons){
    _nbPolygons = nbPolygons;
}

void Scene::setNbEdges(int nbEdges){
    _nbEdges = nbEdges;
}

void Scene::setNbObjects(int nbObjects){
    _nbObjects = nbObjects;
}

int Scene::getNbVertices(){
    return _nbVertices;
}

int Scene::getNbEdges(){
    return _nbEdges;
}

int Scene::getNbPolygons(){
    qDebug()<<"Getting nb poly : " << _nbPolygons;
    return _nbPolygons/3;
}

int Scene::getNbObjects(){
    return _nbObjects;
}

} // namespace Application
