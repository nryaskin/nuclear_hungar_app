#include "hangarview.h"
#include <QOpenGLShaderProgram>
#include <QString>
#include <QDebug>
#include "vertex.h"
#include <math.h>
#include <QtWidgets>

static const Vertex sg_vertexes[] = {
  Vertex( QVector3D( 0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f) ),
  Vertex( QVector3D( 0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f) ),
  Vertex( QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f) )
};

HangarView::~HangarView()
{
    makeCurrent();
    tearDown();
}

void HangarView::renderSceneCB()
{
    makeCurrent();
    m_program->bind();
    {
        int gScaleLocation = m_program->uniformLocation("gScale");
        static GLfloat Scale = 0.0f;
        Scale += 0.001f;
        m_program->setUniformValue(gScaleLocation, Scale);
    }
    m_program->release();
    update();
}

void HangarView::initializeGL()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderSceneCB()));
    initializeOpenGLFunctions();
    //
    QString glType;
      QString glVersion;
      QString glProfile;

      // Get Version Information
      glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
      glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

      // Get Profile Information
    #define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
      switch (format().profile())
      {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
      }
    #undef CASE

      // qPrintable() will print our QString w/o quotes around it.
      qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";

    // Set global information
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    {
          // Create Shader (Do not release until VAO is created)

        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
        m_program->link();
        m_program->bind();

        // Create Buffer (Do not release until VAO is created)
        m_vertex.create();
        m_vertex.bind();
        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

        // Create Vertex Array Object
        m_object.create();
        m_object.bind();
        m_program->enableAttributeArray(0);
        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

        // Release (unbind) all
        m_object.release();
        m_vertex.release();
        m_program->release();
    }
    timer->start(1);
}

void HangarView::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    m_program->bind();
    {
        m_object.bind();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
        m_object.release();
    }
    m_program->release();
}

void HangarView::resizeGl(int width, int height)
{
    (void) width;
    (void) height;
}

void HangarView::tearDown()
{
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
}
