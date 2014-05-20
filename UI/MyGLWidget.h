#ifndef MY_G_L_WIDGET_H
#define MY_G_L_WIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QOpenGLFunctions>

class myGLWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    explicit myGLWidget(int framesPerSecond =0, QWidget *parent = 0, char *name = 0);
    ~myGLWidget();
    virtual void initializeGL()=0;
    virtual void paintGL()=0;
    virtual void keyPressEvent(QKeyEvent *keyEvent) = 0;
    virtual void mousePressEvent(QMouseEvent * mouseEvent) = 0;
    virtual void mouseMoveEvent(QMouseEvent * mouseEvent) = 0;
    virtual void mouseReleaseEvent(QMouseEvent * mouseEvent) = 0;
    virtual void wheelEvent(QWheelEvent *wheelEvent) = 0;

    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

protected:
    bool event(QEvent* event);

    void exposeEvent(QExposeEvent *event);
    void resizeEvent(QResizeEvent *event);


public slots :
    virtual void timeOutSlot();
    void renderLater();
    void renderNow();

private:
    QTimer *t_Timer;
    bool m_update_pending;
    bool m_animating;

};
#endif
