#ifndef ENTITIES_CAMERA_H
#define ENTITIES_CAMERA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <QColor>

#include "QVector3D.h"
#include "QVector2D.h"
#include "Entities/Entity.h"


namespace Entities
{
class Camera : public Entity
{
private:

	QVector3D _position;

	QVector3D _upVector;

    QVector3D _interestPosition;

    QColor _backgroundColor;

	QVector2D _aspect;

	QVector2D _aperture;

	float _fieldOfView;

	float _focalLength;

    float _far;

    float _near;


public:
    explicit Camera();
    void setFOV(float fov);
	void setPerspective();
	void setOrthographic();

    float getFOV();
    float getFar();
    float getNear();

    QColor getBackgroundColor();
    QVector3D getInterestPosition();

    QVector2D getAspect();
    void lookAt(float xEye, float yEye, float zEye, float xCenter, float yCenter, float zCenter, float xUp, float yUp, float zUp)

};

}  // namespace Entities

#endif
