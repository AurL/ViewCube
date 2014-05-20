#ifndef ENTITIES_LIGHT_H
#define ENTITIES_LIGHT_H

#include "Entities/Entity.h"
#include <QGLFunctions>
#include <QColor>



namespace Entities
{
class Light : public Entity
{
private:
    QColor _ambient;
    QColor _diffuse;
    QColor _specular;
    QVector4D _position;
    QVector4D _halfVector;
    QVector3D _spotDirection;
    float _spotExponent;
    float _spotCutoff;
    float _spotCosCutoff;
    float _constantAttn;
    float _linearAttn;
    float _quadraticAttn;


public:


    void setAmbientColor(QColor ambient);
    void setDiffuseColor(QColor diffuse);
    void setSpecularColor(QColor specular);
    void setHalfVector(QVector4D halfvector);
    void setSpotDirection(QVector4D spotDirection);
    void setSpotExponent(float spotExponent);
    void setSpotCutoff(float spotCutoff);
    void setConstantAttn(float constantAttn);
    void setLinearAttn(float linearAttn);
    void setQuadraticAttn(float quadraticAttn);

    QColor getAmbientColor(QColor ambient);
    QColor getDiffuseColor(QColor diffuse);
    QColor getSpecularColor(QColor specular);
    QVector4D getHalfVector(QVector4D halfvector);
    QVector4D getSpotDirection(QVector4D spotDirection);
    float getSpotExponent();
    float getSpotCutoff();
    float getConstantAttn();
    float getLinearAttn();
    float getQuadraticAttn();



};

}  // namespace Entities

#endif
