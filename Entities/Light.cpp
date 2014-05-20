#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Entities/Light.h"

namespace Entities
{


void Light::setAmbientColor(QColor ambient){
   _ambient = ambient;
}

void Light::setDiffuseColor(QColor diffuse){
    _diffuse = diffuse;
}

void Light::setSpecularColor(QColor specular){
    _specular = specular;
}
/*
void Light::setHalfVector(QVector4D halfvector);
void Light::setSpotDirection(QVector4D spotDirection);
void Light::setSpotExponent(float spotExponent);
void Light::setSpotCutoff(float spotCutoff);
void Light::setConstantAttn(float constantAttn);
void Light::setLinearAttn(float linearAttn);
void Light::setQuadraticAttn(float quadraticAttn);

QColor Light::getAmbientColor(QColor ambient);
QColor Light::getDiffuseColor(QColor diffuse);
QColor Light::getSpecularColor(QColor specular);
QVector4D Light::getHalfVector(QVector4D halfvector);
QVector4D Light::getSpotDirection(QVector4D spotDirection);
float Light::getSpotExponent();
float Light::getSpotCutoff();
float Light::getConstantAttn();
float Light::getLinearAttn();
float Light::getQuadraticAttn();*/


}  // namespace Entities

