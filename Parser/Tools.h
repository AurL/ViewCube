#ifndef PARSER_TOOLS_H
#define PARSER_TOOLS_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include<QVector>
#include<Entities/Entity.h>
#include <QMatrix4x4>


namespace Parser
{
class Tools
{
public:

    static QVector<int> buildFBXEdges(QVector<int> polygons, QVector<int>Edges, bool isTriangleFashioned);
    static void setParamsFromEntity(Entities::Entity fromEntity, Entities::Entity toEntity);
    static QMatrix4x4 rotateAround(QVector3D eulerAngles, QVector3D rotationCenter);
    static void parseShaderFile(QString url, const char *shader);

};

}  // namespace Parser

#endif
