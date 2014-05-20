#ifndef ENTITIES_ENTITY_H
#define ENTITIES_ENTITY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <QString>
#include <QVector3D>
#include <QQuaternion>

namespace Entities
{
class Entity
{
private:
	int _id;

	QString _name;

	QVector3D _preRotation;

	QVector3D _localTranslation;

    QVector3D _rotation;

	QVector3D _localScale;

    QVector3D _position;

    bool _isVisible;

    bool _isSelected;

    //Entity* parent;

public:
	void setName(QString name);

	QString getName();

	void setPosition(QVector3D newposition);
    void setPosition(float x, float y, float z);

	QVector3D getPosition();

	void setRotation(QVector3D newrotation);

	QVector3D getRotation();

    QQuaternion getRotationQ();

	void setScale(QVector3D newScale);

	QVector3D getScale();

	void setParent(Entity parent);

	Entity getParent();

	void translate(float x, float y, float z);

	void rotate(float x, float y, float z);

	void rotateQ(QQuaternion qrot);

	void scale(float x, float y, float z);

    void setSelected(bool select);

    bool isSelected();

    void setVisible(bool visible);

    bool isVisible(bool visible);

};

}  // namespace Entities

#endif
