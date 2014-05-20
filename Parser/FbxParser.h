#ifndef PARSER_FBX_PARSER_H
#define PARSER_FBX_PARSER_H

#include "Application/Scene.h"
#include "FileParser.h"


namespace Parser
{
class FbxParser
{
public:
    explicit FbxParser();
    bool parseFileScene(QString fileUrl, Application::Scene *scene);

private:
    bool parseCameraProperties();
    bool parseLightProperties();
    bool parseObjectProperties();
    bool parseConnections();


    QString fileUrl;

};

}  // namespace Parser

#endif
