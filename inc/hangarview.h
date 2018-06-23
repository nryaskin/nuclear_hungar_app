#ifndef HANGARVIEW_H
#define HANGARVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "transformation3d.h"
#include <vector>

class QOpenGLShaderProgram;

struct s_pos{
  int i;
  int j;
};

class HangarView : public QOpenGLWidget,
                   protected QOpenGLFunctions
{
    Q_OBJECT

public:
    HangarView();
    ~HangarView();

    void initializeGL();
    void resizeGl(int width, int height);
    void paintGL();
    void tearDown();
public slots:
    void renderSceneCB();
    void addContainerClicked();
protected:
    void keyPressEvent(QKeyEvent *k);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
private:
    void setGWorld();
private:
    int r_i = 0;
    int c_j = 0;
    std::vector <s_pos> i_containers;
    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;
    Transformation3D m_transformation;

};

#endif // HANGARVIEW_H
