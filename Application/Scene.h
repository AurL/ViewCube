#ifndef APPLICATION_SCENE_H
#define APPLICATION_SCENE_H

#include <QList>

#include "Entities/Entity3D.h"
#include "Entities/Entity2D.h"
#include "Entities/Light.h"
#include "Entities/Camera.h"
#include "Entities/DrawableEntity.h"

using namespace Entities;

namespace Application
{
class Scene
{
private:
    int _fileUrl;
    int _nbVertices;
    int _nbPolygons;
    int _nbObjects;
    int _nbEdges;
    bool _isolationMode;
    QVector<Entity3D> _entity3DLst;
    QVector<Entity2D> _entity2DLst;
    QVector<Light> _lightLst;
    QVector<Camera> _cameraLst;

    QVector<DrawableEntity> _dEntitiy3DLst;


public:
    QVector<Entity3D> getObjects3D();
    QVector<Entity2D> getObjects2D();
    QVector<Light> getLights();
	int getCameras();

    QVector<DrawableEntity> getDEntities3D();

    void addEntity3D(Entity3D entity);
    void addEntity2D(Entity2D entity);
    void addLight(Light light);
    void addCamera(Camera cam);

    void setNbPolygons(int nbPolygons);
    void setNbVertices(int nbVertices);
    void setNbEdges(int nbEdges);
    void setNbObjects(int nbObjectd);

    int getNbPolygons();
    int getNbVertices();
    int getNbEdges();
    int getNbObjects();

    void setDrawableScene();

};

}  // namespace Application

#endif
