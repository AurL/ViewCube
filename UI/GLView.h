#ifndef GLVIEW_H
#define GLVIEW_H

#include "UI/MyGLWidget.h"
#include <QVector2D>
#include "Entities/Camera.h"
#include "UI/GLShader.h"
#include "Application/Scene.h"
#include <GL/glu.h>
#include <QKeyEvent>
#include <QOpenGLShaderProgram>
#include<QStack>

using namespace Entities;
using namespace UI;
using namespace Application;



class GLView : public myGLWidget
{
    Q_OBJECT
public:

    GLView(QWidget *parent=0, Application::Scene* scene = 0, Entities::Camera * camera = 0);
    void initializeGL();
    void paintGL();
    void keyPressEvent(QKeyEvent *keyEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void wheelEvent(QWheelEvent *wheelEvent);
    void redisplay();
    void setCamera(Camera* cam);
    void setVertexShader(const char *shader);
    void setFragmentShader(const char *shader);
    void displayScene(Scene *scene);

    //Sub
    void display3DEntities(Scene *scene);
    void display2DEntities(Scene scene);
    void displayLights(Scene scene);
    void displayCameras(Scene scene);
    void displayGizmos();

    //OpenGL functions
    void draw3DEntity(Entity3D entity);
    void draw2DEntity (Entity2D entity);
    void setLight(Light light);

    void setName(QString nname);

private:

    GLuint loadShader(GLenum type, const char *source);
    GLuint m_normAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;
    GLuint m_matrixModelViewUniform;

    const char* vertexShader;
    const char* fragmentShader;

    QMatrix4x4 matrix;
    QMatrix4x4 matModel;
    QMatrix4x4 matView;
    QMatrix4x4 matModelView;
    QMatrix4x4 matProjection;

    QVector2D _size;
    int _shaders;
    int _activeShaderIndex;
    Camera* _mainCamera;
    QStack<QMatrix4x4> modelView;
    Application::Scene* currentScene;

    QOpenGLShaderProgram *m_program;

    //To be replaced by Camera
    float transX, transY, transZ;
    float rotX, rotY, rotZ, speedX, speedY, speedZ;
    float twist, elevation=0, azimuth=0, distance=-10;

    bool wireframe, vertices, model;

    bool isDragging;
    QVector<DrawableEntity> drawEntities;

    void computeCameraMatrix();
    QString name;


};


#endif
