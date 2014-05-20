#include "UI/MyGLWidget.h"
#include <QCoreApplication>

myGLWidget::myGLWidget(int framesPerSecond, QWidget *parent, char *name)
    : QGLWidget(parent)
    , m_update_pending(false)
    , m_animating(false)
{
    setWindowTitle(QString ::fromUtf8(name));
    if(framesPerSecond ==0)
        t_Timer = NULL;
    else
    {
        int seconde = 1000;
        int timerInterval = seconde /framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start(timerInterval);
    }
}
myGLWidget::~myGLWidget()
{

}

void myGLWidget::initialize()
{

}

void myGLWidget::renderLater()
{
    if(!m_update_pending)
    {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool myGLWidget::event(QEvent *event)
{
    switch(event->type()){
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
        return QWidget::event(event);
    }
}

void myGLWidget::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event)

    if(isVisible())
        renderNow();
}

void myGLWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    if(isVisible())
        renderNow();
}

void myGLWidget::renderNow()
{
    if(!isVisible())
        return;

    m_update_pending = false;

    bool needsInitialize = false;

    if(needsInitialize)
    {
       initializeOpenGLFunctions();
       this->initialize();
    }

    render();

    if(m_animating)
        renderLater();
}


void myGLWidget::timeOutSlot()
{

}

void myGLWidget::setAnimating(bool animating)
{
    m_animating = animating;

    if(animating)
        renderLater();
}

void myGLWidget::render()
{

}

