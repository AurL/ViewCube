#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "QString.h"
#include "Application/Scene.h"

class FileParser
{

public:
    virtual bool parseFileScene(QString fileUrl, Application::Scene scene)=0;


private:

    virtual bool parseModelPropterties();
    virtual bool parseGeometryProperties();
    virtual bool parseLightProperties();
    virtual bool parseCameraProperties();
    virtual bool parseConnections();


};
#endif
