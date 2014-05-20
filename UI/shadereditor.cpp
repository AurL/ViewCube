#include "shadereditor.h"
#include "ui_shadereditor.h"
#include <QDebug>

ShaderEditor::ShaderEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShaderEditor)
{
    ui->setupUi(this);
    connect(ui->shaderType_Combo, SIGNAL(currentIndexChanged(int)), this, SLOT(setShaderTypeSlot(int)));
    connect(ui->saveShader_button, SIGNAL(clicked()), this, SLOT(saveShaderSlot()));
    connect(ui->loadFile_button, SIGNAL(clicked()), this, SLOT(loadShaderFromFileSlot()));
    connect(ui->setCurrentScene_button, SIGNAL(clicked()), this, SLOT(setToCurrentSceneSlot()));
    connect(ui->viewTarget_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(setViewTargets(int)));
    connect(ui->ok_button, SIGNAL(clicked()), this, SLOT(saveAndClose()));
    connect(ui->quit_button, SIGNAL(clicked()), this, SLOT(close()));
}

ShaderEditor::~ShaderEditor()
{
    delete ui;
}

void ShaderEditor::setCurrentVertexShader(const char *vshader)
{
    this->currentVertexShader = vshader;
}

void ShaderEditor::setCurrentFragmentShader(const char *fshader)
{
    this->currentFragmentShader = fshader;
}

void ShaderEditor::setShaderTypeSlot(int shaderType)
{
    qDebug()<< "Shader Type changed " << shaderType ;
}

void ShaderEditor::setViewTargets(int viewTarget)
{
    qDebug()<< "Target changed " << viewTarget;
}

void ShaderEditor::saveShaderSlot()
{
    qDebug()<< "Shader saved";
}

void ShaderEditor::loadShaderFromFileSlot()
{
    qDebug()<< "Shader loaded";
}

void ShaderEditor::setToCurrentSceneSlot()
{
    qDebug()<< "Set to current scene";
}

void ShaderEditor::saveAndClose()
{
    qDebug() << "Save and close !";
   this->close();
}
