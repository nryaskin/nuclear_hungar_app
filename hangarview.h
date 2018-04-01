#ifndef HANGARVIEW_H
#define HANGARVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QOpenGLShaderProgram;

class HangarView : public QOpenGLWidget,
                   protected QOpenGLFunctions
{
    Q_OBJECT

public:
    ~HangarView();

    void initializeGL();
    void resizeGl(int width, int height);
    void paintGL();
    void tearDown();
public slots:
    void renderSceneCB();

private:
    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;


};

#endif // HANGARVIEW_H
