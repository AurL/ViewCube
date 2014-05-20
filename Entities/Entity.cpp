#include "Entity.h"
#include <QDebug>

namespace Entities
{

void Entity::setName(QString name)
{
}

QString Entity::getName()
{
	return 0;
}

void Entity::setPosition(QVector3D newposition)
{
    _position = newposition;
}
void Entity::setPosition(float x, float y, float z)
{
    _position= QVector3D(x, y, z);
}


QVector3D Entity::getPosition()
{
    return _position;
}

void Entity::setRotation(QVector3D newrotation)
{
    _rotation = newrotation;
}

QVector3D Entity::getRotation()
{
    return _rotation;
}

QQuaternion Entity::getRotationQ()
{
    return QQuaternion();
}

void Entity::setScale(QVector3D newScale)
{
}

QVector3D Entity::getScale()
{
    return _localScale;
}

void Entity::setParent(Entity parent)
{
}

Entity Entity::getParent()
{
    return Entity();
}

void Entity::translate(float x, float y, float z)
{
   setPosition(this->getPosition().x()+x, this->getPosition().y()+y, this->getPosition().z()+z);
}

void Entity::rotate(float x, float y, float z)
{
}

void Entity::rotateQ(QQuaternion qrot)
{
}

void Entity::scale(float x, float y, float z)
{
}

void Entity::setSelected(bool select)
{

}

bool Entity::isSelected()
{

}

void Entity::setVisible(bool visible)
{

}


bool Entity::isVisible(bool visible)
{

}

}  // namespace Entities
