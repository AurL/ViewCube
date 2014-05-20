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

} // namespace Application
