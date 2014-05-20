#ifndef ENTITIES_ENTITY2_D_H
#define ENTITIES_ENTITY2_D_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "QVector3D.h"
#include "QList.h"
#include "Entities/Entity.h"


namespace Entities
{
class Entity2D : public Entity
{
private:
	QVector3D _color;

	QList<QVector3D> _points;

	QList<int> _pointsIndex;


public:
	void setParamsFromEntity(int id);

};

}  // namespace Entities

#endif
