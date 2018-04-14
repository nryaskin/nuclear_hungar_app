#include "hangarview.h"
#include <QOpenGLShaderProgram>
#include <QString>
#include <QDebug>
#include "vertex.h"
#include <math.h>
#include <QtWidgets>
#include "camera.h"

// Front Verticies
#define VERTEX_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.0f, 0.0f, 0.0f ) )
#define VERTEX_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define VERTEX_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 1.0f ) )
#define VERTEX_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) )

// Back Verticies
#define VERTEX_BTR Vertex( QVector3D( 0.5f,  0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 0.0f ) )
#define VERTEX_BTL Vertex( QVector3D(-0.5f,  0.5f, -0.5f), QVector3D( 0.0f, 1.0f, 1.0f ) )
#define VERTEX_BBL Vertex( QVector3D(-0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 0.0f, 1.0f ) )
#define VERTEX_BBR Vertex( QVector3D( 0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )

// Create a colored cube
static const Vertex sg_vertexes[] = {
  // Face 1 (Front)
    VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
    VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
  // Face 2 (Back)
    VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
    VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
  // Face 3 (Top)
    VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
    VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
  // Face 4 (Bottom)
    VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
    VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
  // Face 5 (Left)
    VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
    VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
  // Face 6 (Right)
    VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
    VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
};

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR

#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR

HangarView::HangarView()
{
    setFocusPolicy(Qt::StrongFocus);
    m_transformation.translate(0.0f, 0.0f, -3.0f);
    QVector3D CameraPos(1.0f, 1.0f, -3.0f);
    QVector3D CameraTarget(0.45f, 0.0f, 1.0f);
    QVector3D CameraUp(0.0f, 1.0f, 0.0f);
    Camera cam(800, 600);
    m_transformation.setCamera(cam);
    //m_transformation.scale(0.5f);
}
//User enteractions event handlers
void HangarView::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    m_transformation.camera().onMouseMove(mouseEvent->x(), mouseEvent->y());
}

void HangarView::keyPressEvent(QKeyEvent *k)
{
     m_transformation.camera().onKeyboard(k->key());
}

void HangarView::mousePressEvent(QMouseEvent *mouseEvent){
    m_transformation.camera().mousePos().setX(mouseEvent->x());
    m_transformation.camera().mousePos().setY(mouseEvent->y());
}

HangarView::~HangarView()
{
    makeCurrent();
    tearDown();
}

void HangarView::setGWorld()
{
    int gWorldLocation = m_program->uniformLocation("gWorld");
    static float Scale = 0.0f;
    Scale += 0.001f;
    m_transformation.rotate(Scale, QVector3D(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f));
    m_transformation.setPerspectiveProj(45.0f, this->width(), this->height(), 0.0f, 1000.0f);
    m_program->setUniformValue(gWorldLocation, m_transformation.toMatrix());
}

void HangarView::renderSceneCB()
{
    m_transformation.camera().onRender();
    makeCurrent();
    m_program->bind();
    {
         setGWorld();
    }
    m_program->release();
}

void HangarView::initializeGL()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderSceneCB()));
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    initializeOpenGLFunctions();
    // Set global information
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_CULL_FACE);
    {
        // Create Shader (Do not release until VAO is created)

        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
        m_program->link();
        m_program->bind();

        //setting world global matrix
        setGWorld();

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
    m_transformation.camera().setWindowHeight(height);
    m_transformation.camera().setWindowWidth(width);
    m_transformation.setPerspectiveProj(45.0f, width, height, 0.0f, 10.0f);
}

void HangarView::tearDown()
{
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
}
