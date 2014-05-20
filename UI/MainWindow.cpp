#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Ui\GLView.h"
#include <QPushButton>
#include <QDebug>
#include <Parser/FbxParser.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();

}

void MainWindow::initialize()
{
    QSurfaceFormat format;
    format.setSamples(4);

    setWindowFlags(Qt::Widget);

    this->fileUrl = "C:/superteapot.FBX";
    this->currentScene =  new Application::Scene();

    Parser::FbxParser parser;
    parser.parseFileScene(fileUrl, this->currentScene);
    qDebug() << " [MainWindow] : Parsed !" ;

    this->currentScene->setDrawableScene();


    left = new Camera();
    left->setPosition(0, 0, -50);
    left->setFOV(78.0);

    this->leftViewGL = new GLView(this, this->currentScene, this->left);
    this->leftViewGL->setName("Left");
    ui->topView->addWidget(this->leftViewGL, 0, 1);


   /* up = new Camera();
    up->setPosition(0, 0, -30);
    up->setFOV(78.0);

    this->topViewGL = new GLView(this, this->currentScene, this->up);
    this->topViewGL->setName("Top");
    ui->topView->addWidget(this->topViewGL, 0, 0);*/

  /*right = new Camera();
    right->setPosition(0,0, -50);
    right->setFOV(20.0);
    this->rightViewGL = new GLView(this, this->currentScene, this->right);
    this->rightViewGL->setName("Right");
    ui->topView->addWidget(this->rightViewGL, 1, 0);


    down = new Camera();
    down->setPosition(0, 0, -50);
    down->setFOV(5.0);

    this->perspViewGL = new GLView(this, this->currentScene, this->down);
    this->perspViewGL->setName("Persp");
    ui->topView->addWidget(this->perspViewGL, 1, 1);*/



    shaderEditor = NULL;

    /*  ui->shader_rightView = new QLabel();
    ui->shader_rightView-> move(5,1);
    ui->shader_rightView->setText("<font color='white'>  Right </font>");

    ui->shader_topView = new QLabel(this->topViewGL);
    ui->shader_topView-> move(5,1);
    ui->shader_topView->setText("<font color='white'>  Top </font>");

    ui->shader_leftView = new QLabel();
    ui->shader_leftView-> move(5,1);
    ui->shader_leftView->setText("<font color='white'>  Left </font>");

    ui->shader_perspView = new QLabel();
    ui->shader_perspView-> move(5,1);
    ui->shader_perspView->setText("<font color='white'>  Perspective </font>");*/
    connect(ui->openShaderEditor_button, SIGNAL(clicked()), this, SLOT(openShaderEditor()));

    //Prepare Scene
    }

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::getUi(){
     return ui;
 }

void MainWindow::openShaderEditor()
{
    this->shaderEditor = new ShaderEditor(this);
    this->shaderEditor->show();
}

GLView* MainWindow::getView(int index)
{
    if(index==0)
        return topViewGL;
    if(index==1)
        return leftViewGL;
    if(index==2)
        return rightViewGL;
    if(index==3)
        return perspViewGL;
    }


QLabel* MainWindow::getFileLabel()
{
    return ui->fileUrl_label;
}

// Scene Informations Getters
QLabel* MainWindow::getAllEntitiesSI()
{
    return ui->entitiesSi_all;
}

QLabel* MainWindow::getAllPointsSI()
{
    return ui->pointsSi_all;
}

QLabel* MainWindow::getAllPolygonsSI()
{
    return ui->polygonsSi_all;
}

QLabel* MainWindow::getEntitiesSI()
{
    return ui->entitiesSi;
}

QLabel* MainWindow::getPolygonsSI()
{
    return ui->polygonsSi;
}

QLabel* MainWindow::getPointsSI()
{
   return ui->pointsSi;
}

// Transform Getters
QLineEdit* MainWindow::getPositionX()
{
    return ui->xPos;
}

QLineEdit* MainWindow::getPositionY()
{
    return ui->yPos;
}
QLineEdit* MainWindow::getPositionZ()
{
    return ui->zPos;
}

QLineEdit* MainWindow::getRotationX()
{
    return ui->xRot;
}
QLineEdit* MainWindow::getRotationY()
{
    return ui->yRot;
}
QLineEdit* MainWindow::getRotationZ()
{
    return ui->zRot;
}

QLineEdit* MainWindow::getScaleX()
{
    return ui->xSca;
}

QLineEdit* MainWindow::getScaleY()
{
    return ui->ySca;
}
QLineEdit* MainWindow::getScaleZ()
{
    return ui->zSca;
}

QLineEdit* MainWindow::getNameWidget()
{
    return ui->objectName;
}
QString MainWindow::getFileUrl(){
    return fileUrl;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
     QCoreApplication::sendEvent( this->topViewGL,new QKeyEvent(QKeyEvent::KeyPress, 48,Qt::NoModifier));
}
