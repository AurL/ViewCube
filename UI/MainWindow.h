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

    // Widget getters
    GLView* getView(int index); // index : 0 = Up Left, 1 = Up Right, 2 = Down Left,  3 = Down Right
    QLabel* getViewText(int index);
    QWidget* getViewImage(int index);
    QLabel* getFileLabel();
    void keyPressEvent(QKeyEvent *event);

    // Scene Informations Getters
    QLabel* getAllEntitiesSI();
    QLabel* getAllPointsSI();
    QLabel* getAllPolygonsSI();

    QLabel* getEntitiesSI();
    QLabel* getPolygonsSI();
    QLabel* getPointsSI();

    // Transform Getters
    QLineEdit* getPositionX();
    QLineEdit* getPositionY();
    QLineEdit* getPositionZ();

    QLineEdit* getRotationX();
    QLineEdit* getRotationY();
    QLineEdit* getRotationZ();

    QLineEdit* getScaleX();
    QLineEdit* getScaleY();
    QLineEdit* getScaleZ();

    QLineEdit* getNameWidget();

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
