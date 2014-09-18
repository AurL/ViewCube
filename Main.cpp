#include <QApplication>
#include "Ui/GLView.h"
#include "Ui/MainWindow.h"
#include <Parser/FbxParser.h>
#include "Ui/shadereditor.h"

// I am a comment

int main(int argc, char **argv)
{
    //This is a change from Paris
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec();
}


