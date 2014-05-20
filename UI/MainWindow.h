#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include "Ui/GLView.h"
#include "UI/shadereditor.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initialize();

    QString getFileUrl();

    QLabel* getFileLabel();
    void keyPressEvent(QKeyEvent *event);

    void setStats();

    Ui::MainWindow* getUi();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GLView *topViewGL;
    GLView *leftViewGL;
    GLView *rightViewGL;
    GLView *perspViewGL;
    QString fileUrl;
    ShaderEditor* shaderEditor;
    Application::Scene *currentScene;

    Entities::Camera* up;
    Entities::Camera* left;
    Entities::Camera* right;
    Entities::Camera* down;

public slots:
   void openShaderEditor();
};


#endif // MAINWINDOW_H
