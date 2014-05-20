#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <QMatrix4x4>

#include "Camera.h"


namespace Entities
{

Camera::Camera()
{
  _position = QVector3D(0,0,0);
  _upVector = QVector3D(0,1,0);
  _interestPosition = QVector3D(0,0,-10);
  _backgroundColor = Qt::black;
  _aspect = QVector2D(1,0.5);
  //_aperture =
  _fieldOfView = 45.0;
  //_focalLength;
  _near = 0.1;
  _far = 1000.0;

}



void Camera::setFOV(float fov)
{
    _fieldOfView = fov;
}

void Camera::setPerspective()
{
}

void Camera::setOrthographic()
{
}

float Camera::getFOV()
{
    return _fieldOfView;
}

QVector2D Camera::getAspect()
{
     return _aspect;
}

float Camera::getFar()
{
    return _far;
}

float Camera::getNear()
{
    return _near;
}

QColor Camera::getBackgroundColor()
{
    return _backgroundColor;
}

QVector3D Camera::getInterestPosition()
{
    return _interestPosition;
}

QMatrix4x4 Camera::lookAt(QVector3D eye, QVector3D center, QVector3D up){

    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();


    QVector3D zaxis = (center - eye).normalized();
    QVector3D xaxis = QVector3D::crossProduct(up, zaxis).normalized();
    QVector3D yaxis = QVector3D::crossProduct(zaxis, xaxis);

    viewMatrix.setRow(0, QVector4D(xaxis.x(), yaxis.x(), zaxis.x(), 0));
    viewMatrix.setRow(1, QVector4D(xaxis.y(), yaxis.y(), zaxis.y(), 0));
    viewMatrix.setRow(2, QVector4D(xaxis.z(), yaxis.z(), zaxis.z(), 0));
    viewMatrix.setRow(3, QVector4D(-QVector3D::dotProduct(xaxis, eye), -QVector3D::dotProduct(yaxis, eye), -QVector3D::dotProduct(zaxis,eye),1));

    qDebug() << viewMatrix;
    return viewMatrix;
}

}  // namespace Entities

