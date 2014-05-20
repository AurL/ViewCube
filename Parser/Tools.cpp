
#include<QDebug>
#include "Tools.h"
#include <QTextStream>
#include <QFile>

namespace Parser
{

QVector<int> Tools::buildFBXEdges(QVector<int> polygons, QVector<int> Edges, bool isTriangleFashioned){
    QVector<int> builtEdges;
    int polygonSize;
    if(isTriangleFashioned)
        polygonSize=2;
    else
        polygonSize=3;

    for(int i=0;i<Edges.count();i++){
        if(polygons.at(Edges.at(i))<0){
            if(i>=polygonSize){
                builtEdges.append(abs(polygons.at(Edges.at(i))));
                builtEdges.append(abs(polygons.at(Edges.at(i)-polygonSize)));

            }
        }else
        {
            builtEdges.append(abs(polygons.at(Edges.at(i))));
            builtEdges.append(abs(polygons.at(Edges.at(i)+1)));
        }
    }
    return builtEdges;
}


void Tools::parseShaderFile(QString url, const char *shader){

    QFile f(url);
    f.open(QIODevice::ReadOnly);
    QTextStream sr(&f);
    QString currentLine;
    qDebug() << "parsing shader " << sr.readAll();
    QString shaderCode = "";
    while(!sr.atEnd()){
        currentLine = sr.readLine();
        qDebug()<< currentLine;
        shaderCode += currentLine;
        shaderCode += "\n";
    }
    shader = shaderCode.toStdString().c_str();
}



}  // namespace Parser

