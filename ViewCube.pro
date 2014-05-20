FORMS += \
    mainwindow.ui \
    shadereditor.ui

HEADERS += \
    UI/GLView.h \
    UI/MainWindow.h \
    Entities/Camera.h \
    Entities/Entity.h \
    Entities/Entity2D.h \
    Entities/Entity3D.h \
    Entities/Light.h \
    UI/GLShader.h \
    Application/GlobalSettings.h \
    Application/LightType.h \
    Application/Scene.h \
    Parser/FbxParser.h \
    Parser/Tools.h \
    Parser/FileParser.h \
    UI/MyGLWidget.h \
    shadereditor.h \
    UI/shadereditor.h \
    Entities/DrawableEntity.h

SOURCES += \
    Main.cpp \
    UI/GLView.cpp \
    UI/MainWindow.cpp \
    Entities/Camera.cpp \
    Entities/Entity.cpp \
    Entities/Entity2D.cpp \
    Entities/Entity3D.cpp \
    Entities/Light.cpp \
    UI/GLShader.cpp \
    Application/GlobalSettings.cpp \
    Application/LightType.cpp \
    Application/Scene.cpp \
    Parser/FbxParser.cpp \
    Parser/Tools.cpp \
    UI/MyGLWidget.cpp \
    UI/shadereditor.cpp \
    Entities/DrawableEntity.cpp

QT += gui
CONFIG += qt

QT       += core gui

QT += widgets

QT += opengl
