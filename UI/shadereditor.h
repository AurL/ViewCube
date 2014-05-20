#ifndef SHADEREDITOR_H
#define SHADEREDITOR_H

#include <QMainWindow>

namespace Ui {
class ShaderEditor;
}

class ShaderEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShaderEditor(QWidget *parent = 0);
    void setCurrentVertexShader(const char* vshader);
    void setCurrentFragmentShader(const char* fshader);

    ~ShaderEditor();

private:
    Ui::ShaderEditor *ui;
    const char* currentVertexShader;
    const char* currentFragmentShader;

public slots:
    void setShaderTypeSlot(int shaderType);
    void saveShaderSlot();
    void loadShaderFromFileSlot();
    void setToCurrentSceneSlot();
    void setViewTargets(int viewTarget);
    void saveAndClose();
};

#endif // SHADEREDITOR_H
