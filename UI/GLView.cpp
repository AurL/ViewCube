
#include "Ui/GLView.h"
#include <QDebug>
#include <QGLFunctions>
#include <QScreen>
#include <QCoreApplication>
#include "Application/Scene.h"
#include <qiterator.h>
#include <qmath.h>
#include <Parser/FbxParser.h>
#include <QProcess>
#include "Parser/Tools.h"
#include "Entities/DrawableEntity.h"

using namespace Entities;

// GIT CHANGE
// View parameters
float mouseOriginX, mouseOriginY;

// Verbose mode
bool debug = true;

GLView::GLView (QWidget *parent, Application::Scene *scene, Camera *camera)
    : myGLWidget(60, parent)
    , m_program(0)
    , rotX(0)
    , rotY(0)
    , speedX(0)
    , speedY(0)
    , isDragging(false)
    , _shaders(0)
    , _activeShaderIndex(0)
    , elevation(0)
    , azimuth(0)
    , distance(0)
    , wireframe(false)
    , vertices(false)
    , model(true)
{
    qDebug() << "[GLView - " << name <<"] Creation";
    this->makeCurrent();
    drawEntities = QVector<DrawableEntity>();
    QOpenGLFunctions::initializeOpenGLFunctions();

    // Basic test shader
    vertexShader = "attribute highp vec4 posAttr;\n"
                       "attribute lowp vec4 colAttr;\n"
                       "varying lowp vec4 col;\n"
                       "uniform highp mat4 matrix;\n"
                       "void main() {\n"
                       "     col = colAttr;\n"
                       "     gl_Position = matrix * posAttr;\n"
                       "}\n";
   fragmentShader = "varying lowp vec4 col; \n"
                        "void main() { \n"
                        "   gl_FragColor = col; \n"
                        "} \n";

   this->_mainCamera = camera;
   this->currentScene = scene;
   drawEntities = scene->getDEntities3D();
}


void GLView::setName(QString nname)
{
    this->name = nname;
}

void GLView::initializeGL(){

    if(debug)
       qDebug() << "[GLView - " << name <<"] initialize";

    m_program = new QOpenGLShaderProgram(this);

    //TODO : specified by object
    setVertexShader(vertexShader);
    setFragmentShader(fragmentShader);

    m_normAttr = m_program->attributeLocation("normAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");

    //Matrices operations
    {
        matModel.setToIdentity();
        matView.setToIdentity();
        matProjection.setToIdentity();
        matProjection.perspective(_mainCamera->getFOV(), this->width()/this->height(), 0.1, 1000.0);
    }
    // GL modes
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0,0.0, 0.0, 1.0);
    }
    glViewport(0,0,this->width(), this->height());
    computeCameraMatrix();
}


//Améliorer la rotation : utiliser offset rotation + variables de currentRotation
void GLView::computeCameraMatrix()
{
    if(debug)
        qDebug() << "[GLView - " << name <<"] Compute matrices ";

    //Matrices computation
    matModel.setToIdentity();
    matView.setToIdentity();
    matProjection.setToIdentity();
    matrix.setToIdentity();

    elevation +=speedY;
    azimuth += speedX;
    speedY=0;
    speedX=0;
    // Compute view matrix
    matView.translate(0, 0, _mainCamera->getPosition().z());
    matView.rotate(-twist, 0, 0, 1);
    matView.rotate(-elevation, 1.0, 0.0, 0.0);
    matView.rotate(azimuth, 0.0, 1.0, 0);
    this->redisplay();
}

void GLView::setVertexShader(const char *vertexS)
{
    this->vertexShader = vertexS;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    m_program->link();

}

void GLView::setFragmentShader(const char *fragmentS)
{
    this->fragmentShader = fragmentS;
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    m_program->link();

}

void GLView::paintGL()
{
    if(debug)
        qDebug() << "[GLView - " << name <<"] Paint";
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    this->display3DEntities(this->currentScene);
    glBegin(GL_POINTS);
        glVertex3f(0, 0, 0);
    glEnd();


}

void GLView::display3DEntities(Scene *scene)
{
       /* enable z buffer */
        matModel.setToIdentity();
       for(int i=0; i<drawEntities.count();i++){
           DrawableEntity current = drawEntities.at(i);
           qDebug() << "xRot "<< current.xRot;
           current.xRot = 0 ;
           matModel.rotate(current.xRot, 1, 0, 0);
           matModel.rotate(current.yRot, 0, 1, 0);
           matModel.rotate(current.zRot, 0, 0, 1);
           matModel.translate(-current.centerX, -current.centerY, -current.centerZ);
          // Compute custom model matrix
          // building the final MVP matrix
           matModelView = matView * matModel;
           matProjection.setToIdentity();
           matProjection.perspective(_mainCamera->getFOV(), this->width()/this->height(), 0.1, 1000.0);
           qDebug() << matProjection;
           matrix = matProjection * matModelView;

           m_program->bind();
           m_program->setUniformValue(m_matrixUniform, matrix);
          // m_program->setUniformValue(m_matrixModelViewUniform, matModelView);
           displayGizmos();
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, current.vertices);

            glVertexAttribPointer(m_colAttr,3, GL_FLOAT, GL_FALSE, 0, current.colors );
            glEnableVertexAttribArray(1);

            if(model)
                if(current.trianglesFashion){
                  glDrawElements(GL_TRIANGLES,current.drawCount,GL_UNSIGNED_INT, current.polygons );
                }
            else
                {
                     glDrawElements(GL_QUADS,current.drawCount,GL_UNSIGNED_INT, current.polygons );
                }

            glDisableVertexAttribArray(1);
            // Vertices
            if(vertices){
                glColor3f(1.0, 1.0, 1.0);
                glPointSize(4);
                glDrawElements(GL_POINTS, current.drawCount, GL_UNSIGNED_INT, current.polygons);
            }

            // Wireframe
            if(wireframe) {
                glLineWidth(1);
                glDrawElements(GL_LINES, current.edgesCount,GL_UNSIGNED_INT, current.edges );
            }

        }
    m_program->release();
}


void GLView::displayGizmos(){
    glLineWidth(0.2);
    glBegin(GL_LINES);
    glVertex3f(-5.0, 0.0, 0.0);
    glVertex3f(5.0, 0.0, 0.0);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -5.0, 0.0);
    glVertex3f(0.0, 5.0, 0.0);
    glEnd();
   glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -0.0);
    glVertex3f(0.0, 0.0, 5.0);
    glEnd();
    glLineWidth(4.0);

    if(debug)
        qDebug() << "DisplayGizmos";
}

GLuint GLView::loadShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    return shader;
}



void GLView::keyPressEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->key() == Qt::Key_1)
       vertices= !vertices;
    if(keyEvent->key() == Qt::Key_2)
       wireframe= !wireframe;
    if(keyEvent->key() == Qt::Key_3)
        model=!model;
    if(keyEvent->key() == Qt::Key_7)
        transZ--;
    if(keyEvent->key() == Qt::Key_9)
        transZ++;

    if(keyEvent->key() == Qt::Key_4)
        _mainCamera->translate(-1, 0, 0);
    if(keyEvent->key() == Qt::Key_8)
        _mainCamera->translate(0, 1, 0);
    if(keyEvent->key() == Qt::Key_6)
        _mainCamera->translate(1, 0, 0);
    if(keyEvent->key() == Qt::Key_2)
        _mainCamera->translate(0, -1, 0);


    if(keyEvent->key()== Qt::Key_Up){
        elevation++;
    }
    if(keyEvent->key()== Qt::Key_Down){
        elevation--;
    }
    if(keyEvent->key()== Qt::Key_Left){
        azimuth--;
    }
    if(keyEvent->key()== Qt::Key_Right){
        azimuth++;

    }
    computeCameraMatrix();
}

void GLView::mousePressEvent(QMouseEvent *mouseEvent)
{
        this->setFocus();
        isDragging = true;
        mouseOriginX=mouseEvent->pos().x();
        mouseOriginY=mouseEvent->pos().y();

}

void GLView::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
         isDragging = false;
         mouseOriginX = 0;
         mouseOriginY =0;
}

void GLView::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if(isDragging){
    speedX = (mouseEvent->pos().x() - mouseOriginX)/50;
    speedY = -(mouseEvent->pos().y() - mouseOriginY)/50;
    computeCameraMatrix();
    }
}

void GLView::wheelEvent(QWheelEvent *wheelEvent)
{
    _mainCamera->translate(0, 0, wheelEvent->delta()/50);
    computeCameraMatrix();
}

void GLView::resizeEvent(QResizeEvent *event){

    glViewport(0,0,(float)this->width(), (float)this->height());
    matProjection.setToIdentity();
    matProjection.perspective(_mainCamera->getFOV(),(float) this->width()/this->height(), 0.1, 100000.0);

    this->computeCameraMatrix();
}


void GLView::setCamera(Camera* cam)
{
    _mainCamera = cam;
}

void GLView::redisplay(){
        QCoreApplication::postEvent(this, new QEvent(QEvent::Paint));
        }

void GLView::displayScene(Scene *scene)
{
    display3DEntities(scene);
}

void GLView::display2DEntities(Scene scene)
{
}
void GLView::displayLights(Scene scene)
{
}
void GLView::displayCameras(Scene scene)
{
}
