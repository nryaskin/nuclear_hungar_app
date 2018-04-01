#ifndef HANGARVIEW_H
#define HANGARVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "transformation3d.h"

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
    void setGWorld();
private:
    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;
    Transformation3D *m_transformation;

};

#endif // HANGARVIEW_H
