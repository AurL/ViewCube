
#include <QTextStream>
#include <QFile>
#include "FbxParser.h"
#include <QDebug>
#include <QMap>
#include "Tools.h"


namespace Parser
{


QTextStream in;
QString currentLine;
QStringList ssplit;

QMap<int, Entity3D> Geometries;
QMap <int, Entity3D> Models;

bool debug = false;

FbxParser::FbxParser()
{

}

bool FbxParser::parseFileScene(QString fileUrl, Application::Scene *scene)
{
    QFile f(fileUrl);
    f.open(QIODevice::ReadOnly);
    in.setDevice(&f);
    while(!in.atEnd()) {
        currentLine = in.readLine();
        if(currentLine.contains("Object properties")){
            parseObjectProperties();
        }
        if(currentLine.contains("; Object connections")){
            parseConnections();
        }
    }
    for(int i=0;i<Geometries.count();i++){
        scene->addEntity3D(Geometries.values().at(i));
    }

    return true;
    f.close();

}

bool FbxParser::parseObjectProperties(){


    QVector<float> vert;
    QVector<int> poly;
    QVector<int> tempPoly;
    QVector<int> edges;
    QVector<float> normals;
    QVector<float> uvs;
    QVector<int> uvIndices;
    Entity3D currentEntity;

    bool ok;
    int currentKey=-1;
    int nbElements;

    currentLine=  in.readLine();
    currentLine=  in.readLine();

    while(!currentLine.contains(";"))
    {
        if(currentLine.contains("Geometry::")){
            if(currentKey!=-1)
                Geometries.insert(currentKey,currentEntity);
            ssplit = currentLine.trimmed().split(":");
            ssplit = ssplit[1].split(",");
            currentKey = ssplit[0].toInt();
        }

        //------------- VERTICES
        if(currentLine.contains("Vertices:")){
            ssplit = currentLine.split("*");
            ssplit = ssplit[1].split(" ");

            nbElements = ssplit[0].toInt();

            currentLine = in.readLine();
            ssplit = currentLine.split(":");
            ssplit = ssplit[1].split(",");

            do{
                float f;
                for(int i=0;i<ssplit.count();i++){
                    f = ssplit[i].toFloat(&ok) ;
                    if(ok){
                        vert.append(f);
                    }
                }
                currentLine = in.readLine();
                ssplit = currentLine.split(",");
            }while(!currentLine.contains("}"));

            currentEntity.setVertices(vert);

            if(debug)
                qDebug() << " Vertices parsed";
        }
        //----------END VERTICES

        //-------------BEGIN POLYGONVERTEXINDEX
        if(currentLine.contains("PolygonVertexIndex:")){
            ssplit = currentLine.split("*");
            ssplit = ssplit[1].split(" ");

            nbElements = ssplit[0].toInt();

            currentLine = in.readLine();
            ssplit = currentLine.split(":");
            ssplit = ssplit[1].split(",");

            currentEntity.setTriangleFashion((ssplit[2].toInt(&ok)<0));
            do{
                float f;
                for(int i=0;i<ssplit.count();i++){
                    f = ssplit[i].toInt(&ok);
                    if(ok){
                        if(f<0){
                            poly.append(f*-1 -1);
                            tempPoly.append(f+1);
                        }
                        else
                        {
                            poly.append(f);
                            tempPoly.append(f);
                        }

                    }
                }
                currentLine = in.readLine();
                ssplit = currentLine.split(",");
            }while(!currentLine.contains("}"));

            currentEntity.setPolygons(poly);
            if(debug)
                qDebug() << " Polygons parsed";
        }
        //----------END POLYGONS

        //-------------BEGIN EDGES
        if(currentLine.contains("Edges:")){
            ssplit = currentLine.split("*");
            ssplit = ssplit[1].split(" ");

            nbElements = ssplit[0].toInt();

            currentLine = in.readLine();
            ssplit = currentLine.split(":");
            ssplit = ssplit[1].split(",");

            do{
                int f;
                for(int i=0;i<ssplit.count();i++){
                    f = ssplit[i].toInt(&ok);
                    if(ok){
                        edges.append(f);
                    }
                }
                currentLine = in.readLine();
                ssplit = currentLine.split(",");
            }while(!currentLine.contains("}"));

            currentEntity.setEdges(Tools::buildFBXEdges(tempPoly, edges, currentEntity.isTriangleFashioned()));
            if(debug)
                qDebug() << " Edges parsed";
        }

        //----------END EDGES

        //--------------BEGIN NORMALS
        if(currentLine.contains("Normals:")){
            ssplit = currentLine.split("*");
            ssplit = ssplit[1].split(" ");

            nbElements = ssplit[0].toInt();

            currentLine = in.readLine();
            ssplit = currentLine.split(":");
            ssplit = ssplit[1].split(",");

            do{
                for(int i=0;i<ssplit.count();i++){
                float f = ssplit[i].toInt(&ok);
                    if(ok){
                        normals.append(f);
                    }
                }
                currentLine = in.readLine();
                ssplit = currentLine.split(",");
            }while(!currentLine.contains("}"));
           if(debug)
               qDebug() << normals;
            currentEntity.setNormals(normals);
            if(debug)
                qDebug() << " Normals parsed";
        }
        //----------END NORMALS

        //--------------UV
        if(currentLine.contains("UV: *")){
            ssplit = currentLine.split("*");
            ssplit = ssplit[1].split(" ");

            nbElements = ssplit[0].toInt();

            currentLine = in.readLine();
            ssplit = currentLine.split(":");
            ssplit = ssplit[1].split(",");

            do{
                for(int i=0;i<ssplit.count();i++){
                    if(float f = ssplit[i].toFloat(&ok) && ok){
                        uvs.append(f);
                    }
                }
                currentLine = in.readLine();
                ssplit = currentLine.split(",");
            }while(!currentLine.contains("}"));

            currentEntity.setUVs(uvs);
            if(debug)
                qDebug() << " UVS parsed";
        }
        //--------------END UVS

        //----------------UVINDICES
        if(currentLine.contains("UVIndex:")){
            ssplit = currentLine.split("*");
            ssplit = ssplit[1].split(" ");

            nbElements = ssplit[0].toInt();

            currentLine = in.readLine();
            ssplit = currentLine.split(":");
            ssplit = ssplit[1].split(",");

            do{
                for(int i=0;i<ssplit.count();i++){
                    if(float f = ssplit[i].toInt(&ok) && ok){
                        uvIndices.append(f*-1 -1);
                    }
                }
                currentLine = in.readLine();
                ssplit = currentLine.split(",");
            }while(!currentLine.contains("}"));

            currentEntity.setUVIndices(uvIndices);
            if(debug)
                qDebug() << " Uv indices parsed";
        }
        //--------------END UVINDICES

        currentLine = in.readLine();

    }
    if(currentKey!=-1)
        Geometries.insert(currentKey,currentEntity);
    return true;

}

bool FbxParser::parseCameraProperties(){

}

bool FbxParser::parseLightProperties(){

}



bool FbxParser::parseConnections(){

    QString name;
    while(!currentLine.contains("}")){
        currentLine = in.readLine();
        if(currentLine.contains("Geometry::, Model::")){
            ssplit = currentLine.trimmed().split("Model::");
            name=ssplit[1];

            currentLine=in.readLine();
            ssplit = currentLine.trimmed().split(",");
            Geometries.find(ssplit[1].toInt()).value().setName(name);
        }

    }
}



}  // namespace Parser


